#pragma once
#include "isctToolFunc.h"
#include "triangleProblem.h"
#include <parallel_hashmap/phmap.h>
#include <vector>
class CorkMesh::EdgeProblem
{
public:
	EdgeProblem(){};
	~EdgeProblem(){};

	std::vector<Eptr>       otherEdges;//边相交问题，如果边相交了则记录和哪条边相交
	std::vector<GluePt>     otherGluePt;
	std::vector<Vec3d>      ipnts;
};

class CorkMesh::IsctProblem : public TopoCache
{
public:
	IsctProblem(CorkMesh *owner);
	virtual ~IsctProblem() {}
public://共用函数
	// access auxiliary quantized coordinates
	Tprob getTprob(Tptr t);
	Eprob getEprob(Eptr e);
	GluePt newGluePt();
	
	IVptr newIsctVert(const Vec3d &coord, GluePt glue, Vptr concrete);
	IVptr newIsctVert(const Vec3d &coord, GluePt glue);
	IVptr newSplitIsctVert(const Vec3d &coord, GluePt glue);

	IVptr copyIsctVert(IVptr orig);
	IEptr newIsctEdge(IVptr endpoint, Tptr tri_key);
	IEptr newIsctEdge(OVptr endpoint, Tptr tri_key);
	OVptr newOrigVert(Vptr v);
	OEptr newOrigEdge(Eptr e, OVptr v0, OVptr v1);
	SEptr newSplitEdge(GVptr v0, GVptr v1, bool boundary);
	GTptr newGenericTri(GVptr v0, GVptr v1, GVptr v2);

	void releaseEdge(GEptr ge);
	void killIsctVert(IVptr iv);
	void killIsctEdge(IEptr ie);
	void killOrigVert(OVptr ov);
	void killOrigEdge(OEptr oe);

	bool hasIntersections(); // test for iscts, exit if one is found
	bool resolveAllIntersections();
	void findIntersections(bool doSelf = true);
	bool classifyIscts(TEIsctPtr &teInter, const Tptr t, const Eptr e, const Empty3d:: IsctSwitch &interType);
	void findWrongEdges();

	//
	void addEdgeCouple(Eptr e0, Eptr e1, const Vec3d &coord);
	void getIvOvMissTopo(Tptr t, IVptr &iv, OVptr &ov, const Vec3d &coord, const int &type);
	void getIvOvMissTopo(Tptr t, IVptr &iv, OVptr &ov, GluePt glue, const Vec3d &coord, const int &type);

	GluePt gluePntwithTolerance(Vec3d coord);
private:
	void findThreeTriIsct(bool doSelf = true);
	// if we encounter ambiguous degeneracies, then this
	// routine returns false, indicating that the computation aborted.
	bool tryToFindIntersections(bool doSelf = true);
	// In that case, we can perturb the positions of points
	void perturbPositions();
	// in order to give things another try, discard partial work
	void reset();
	// some thing sample
	bool isDeTri(Tptr t);
	bool findTwoEdge(Eptr &e0, Eptr &e1, Vec3d &Pnt,GluePt& glue);
protected: // DATA
	//std::set<Vec3d>             set_gluePnt;
	phmap::flat_hash_map<Vec3d, GluePt, Vec3dHasher, Vec3dEuqal>     gluePt_map;
	IterPool<GluePointMarker>						   glue_pts;
	IterPool<TriangleProblem>						   tprobs;
	IterPool<EdgeProblem>						       eprobs;
	IterPool<IsctVertType>							   ivpool;
	IterPool<OrigVertType>							   ovpool;
	IterPool<IsctEdgeType>							   iepool;
	IterPool<OrigEdgeType>							   oepool;
	IterPool<SplitEdgeType>							   sepool;
	IterPool<GenericTriType>						   gtpool;
private:
	std::vector<Vec3d>          quantized_coords;

private:
	//	inline void for_edge_tri(std::function<bool(Eptr e, Tptr t)>);
	void bvh_edge_tri(std::function<bool(Eptr e, Tptr t)>);
	void detectIscts_csg(std::vector<TEIsctPtr>& allIscts);
	void detectIscts(std::vector<TEIsctPtr> &allIscts, bool doSelf = true);
	void detectIscts_buildConfineEdge(bool doSelf = true);
	void findTetrahedronIsct(const Tptr t, std::vector<TEIsctPtr> &allIscts, bool doSelf = true);
	void findTetrahedronIsct(const Tptr t, cork_vector<TEIsctPtr> &allIscts, bool doSelf = true);
	void findTetrahedronIsct_border(const Tptr t, std::vector<TEIsctPtr> &allIscts, bool doSelf = true);
	void findTetrahedronIsct_border(const Tptr t, cork_vector<TEIsctPtr> &allIscts, bool doSelf = true);
	void detectIscts_coplane(TEIsctCoPlanarPtr teInter);
	//建立限制边
	void buildConfineEdge(const TEIsctPtr &allIsct);
	void buildConfineEdge_coplane(TEIsctCoPlanarPtr teInter);
	void buildConfineEdge_tetrahedron(TEIsctCommonPtr teInter);
	void buildConfineEdge_coplane_point_in(Tptr tisct, Eptr eisct, const int &inIdx,const Vec3d &coord, const int &typeVert, IVptr &iv, OVptr &ov);
	void buildConfineEdge_coplane_point_out(Tptr tisct, Eptr eisct, const Vec3d &coord, const int &typeEdge, IVptr &iv, OVptr &ov);
	void buildConfineEdge_coplane_has_common_vert(Tptr the_tri, Eptr the_edge, int idx, const Vec3d &coord,const CommonIsctClassify &classify);//idx 如果是交于边就给三角形的边id 如果是内部点就给相交边上点的id
	void buildConfineEdge_coplane_has_common_vert(Eptr the_edge, Eptr find_edge, const Vec3d &coord);
	//交点位置建立限制边
	void  edgeMeetTri_inTri(Eptr eisct, Tptr tisct, const Vec3d &coord);
	IVptr edgeMeetTri_inTriEdge(Eptr eisct, Tptr tisct, int oeindex, const Vec3d &coord);
	OVptr edgeMeetTri_inTriVertex(Eptr eisct, Tptr tisct, int  ovindex,const Vec3d &coord);
	IVptr edgeMeetTri_inEdgeEnd(Eptr eisct, Tptr tisct, int ovindex, const Vec3d &coord);
	IVptr edgeMeetTri_inEdgeEndAndTriEdge(Eptr eisct, Tptr tisct, int oeindex, int ovindex, const Vec3d &coord);
	OVptr edgeMeetTri_inTriVertexAndEdgeEnd(Eptr eisct, Tptr tisct, int  evindex,int tvidnd,const Vec3d &coord);// in this situation,we can get evindex or ovindex ,but evindex is easy to get
	//三角形中三条边相交问题
	void threeTriInter_no_coplane(Tprob tprob, Tptr t0, Tptr t1, Tptr t2, IEptr ie1, IEptr ie2, const Vec3d &coord);//正常相交
	void threeTriInter_one_coplane(Tprob tprob, Tptr t0, Tptr t1, Tptr t2, IEptr ie1, IEptr ie2, const Vec3d &coord, const int &idx);//一个限制边是共面边
	void threeTriInter_two_coplane(Tprob tprob, Tptr t0, Tptr t1, Tptr t2, IEptr ie1, IEptr ie2, const Vec3d &coord);//两条限制边是共面边
	bool threeTriInter_two_ie_coline(IEptr ie0, IEptr ie1);//两条限制边是共线
	//处理gluepoint重复的问题
	bool findGlue(Vec3d coord, Tptr tKey = nullptr, Eptr eKey = nullptr); // 修改查找gluePoint 的条件 
	void removeDuplicateGluePnts();//去除共同的相同的gluepoint，并更新每个iv和triangleProblem
	void dealDuplicateGluePnts();//处理重复gluepoint
	void updateIVGluePnts(Tprob tprob, std::vector<GVptr> &tmpPoints);
	void updateIEGluePnts(Tprob tprob, const std::vector<GVptr> &tmpPoints);
	//查找原始数据
	void fillOutVertData(GluePt glue, CorkVertex &data);
	void fillOutTriData(Tptr tri, Tptr parent);

private:
	class EdgeCache;

private: // functions here to get around a GCC bug...
	void createRealPtFromGluePt(GluePt glue);
	void createRealTriangles(Tprob tprob, EdgeCache &ecache);

friend class  CorkMesh::IsctWithAnothor;
friend class  CorkMesh::CoPlanarProblem;
};

class CorkMesh::IsctProblem::EdgeCache
{
public:
	EdgeCache(IsctProblem *ip) : iprob(ip), edges(ip->mesh->verts.size()) {}

	Eptr operator()(Vptr v0, Vptr v1);
	// k = 0, 1, or 2
	Eptr getTriangleEdge(GTptr gt, uint k, Tptr big_tri);
	Eptr maybeEdge(GEptr ge);

private:
	struct EdgeEntry {
		EdgeEntry(uint id) : vid(id) {}
		EdgeEntry() {}
		uint vid;
		// things
		Eptr e;
	};

	IsctProblem *iprob;
	std::vector< std::vector<EdgeEntry>>   edges;
};


//处理共面的类
class CorkMesh::CoPlanarProblem:public CorkMesh::IsctProblem
{
public:
	CoPlanarProblem(CorkMesh *owner) :IsctProblem(owner){}
	virtual ~CoPlanarProblem() {}

	void findCoplanes(double Tolerance);
private:	

	void tryToFindCoplanar(double Tolerance);

	void detectCoplaneIscts_tolerance(std::vector<TEIsct> &allIscts, double Tolerance);
	void buildConfineEdge_tolerances(const std::vector<TEIsct> &allIscts, double Tolerance);

	void edgeTri_GlueMesh(
		const double &tolerance, Eptr eisct, Tptr tisct, const Vec3d &pTa, const Vec3d &pTb, const Vec3d &pTc, const Vec3d &pEa, const Vec3d &pEb);
	void edgeTri_GlueMesh_point_in(
		const double &tolerance, Eptr eisct, Tptr tisct, \
		const Vec3d &pTa, const Vec3d &pTb, const Vec3d &pTc, const Vec3d &pEa, const Vec3d &pEb, \
		const int&inIdx, const Empty3d::IsctSwitch &vertSwtich, IVptr &iv, OVptr &ov);
	void edgeTri_GlueMesh_point_out(
		const double &tolerance, Eptr eisct, Tptr tisct, \
		const Vec3d &pTa, const Vec3d &pTb, const Vec3d &pTc, const Vec3d &pEa, const Vec3d &pEb, \
		const int &edgeSwtich, Vec3d &coord, IVptr &iv, OVptr &ov);

	IVptr edgeMeetTri_inTriEdge_glueMesh(Eptr eisct, Tptr tisct, int oeindex, const Vec3d &coord);

	OVptr edgeMeetTri_inTriVertex_glueMesh(Eptr eisct, Tptr tisct, int  ovindex, const Vec3d &coord);

	IVptr edgeMeetTri_inEdgeEnd_glueMesh(Eptr eisct, Tptr tisct, int ovindex, const Vec3d &coord);

	IVptr edgeMeetTri_inEdgeEndAndTriEdge_glueMesh(Eptr eisct, Tptr tisct, int oeindex, int ovindex, const Vec3d &coord);
};