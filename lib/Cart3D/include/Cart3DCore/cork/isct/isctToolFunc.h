#pragma once
#include "topo.h"
#include "bbox.h"
#include "quantization.h"
#include "empty3d.h"
#include "aabvh.h"
#include "rawmesh.h"
#include <set>
#include <vector>
#include <topofwd.h>
struct GenericVertType;
struct IsctVertType;
struct OrigVertType;
struct GenericEdgeType;
struct IsctEdgeType;
struct OrigEdgeType;
struct SplitEdgeType;
struct GenericTriType;
struct GluePointMarker;

typedef GenericVertType*        GVptr;
typedef IsctVertType*           IVptr;
typedef OrigVertType*	        OVptr;
typedef GenericEdgeType*        GEptr;
typedef IsctEdgeType*           IEptr;
typedef OrigEdgeType*	        OEptr;
typedef SplitEdgeType*	        SEptr;
typedef GenericTriType*         GTptr;
typedef GluePointMarker*        GluePt;



enum isctCoPlanarCode
{
	CoPlanar_VertIn = 0,
	CoPlanar_VertOut = 1,
	CoPlanar_IsctInTriVert = 2,
	CoPlanar_IsctInTriEdge = 4,
	CoPlanar_TriIdx0 = 8,
	CoPlanar_TriIdx1 = 16,
	CoPlanar_TriIdx2 = 32
};


inline int getCoPlanarIdx(const int &code)
{
	if (Empty3d::isSwitchOpen(code, CoPlanar_TriIdx0))
		return 0;
	if (Empty3d::isSwitchOpen(code, CoPlanar_TriIdx1))
		return 1;
	if (Empty3d::isSwitchOpen(code, CoPlanar_TriIdx2))
		return 2;
	return -1;
}


//相交存储数据结构
struct TEIsct
{
	Tptr  t;
	Eptr  e;
	Empty3d::IsctSwitch intertype;
	TEIsct()
	{
		t = nullptr;
		e = nullptr;
		intertype.data = -1;
	}
	virtual ~TEIsct() {}
};

struct TEIsctCommon :public TEIsct
{
	Vec3d  coord;
	TEIsctCommon() :TEIsct()
	{
		coord = Vec3d(-10000, -10000, -10000);
	}
};

struct TEIsctCoPlanar :public TEIsct
{
	int vertSwitch0;
	int vertSwitch1;
	Vec3d  coord0;
	Vec3d  coord1;
	TEIsctCoPlanar() :TEIsct()
	{
		coord0 = Vec3d(-10000, -10000, -10000);
		coord1 = Vec3d(-10000, -10000, -10000);
		int vertSwitch0 = -1;
		int vertSwitch1 = -1;
	}
};

typedef TEIsct*	TEIsctPtr;
typedef TEIsctCommon*	TEIsctCommonPtr;
typedef TEIsctCoPlanar*	TEIsctCoPlanarPtr;


struct GenericVertType
{
	GenericVertType()          { idx = -1; isBad = true; }
	virtual ~GenericVertType() {}
	Vptr                    concrete;
	Vec3d                   coord;

	bool                    boundary;
	int                     idx; // temporary for triangulation marshalling
	bool                    isBad;

	cork_vector<GEptr>     edges;
	
};

struct IsctVertType : public GenericVertType
{
	GluePt                  glue_marker;
};

struct OrigVertType : public GenericVertType {};

struct GenericEdgeType
{
	virtual ~GenericEdgeType() {}
	Eptr                    concrete;

	bool                    boundary;
	uint                    idx; // temporary for triangulation marshalling

	GVptr                   ends[2];
	cork_vector<IVptr>     interior;
	
};
struct IsctEdgeType : public GenericEdgeType
{
	IsctEdgeType(){ the_edge_key = nullptr; }//给初值，非共面的情况下为nullptr 
public:
	// use to detect duplicate instances within a triangle
	Eptr                    the_edge_key;
	Tptr                    other_tri_key;
	bool                    bwrong;
};
struct OrigEdgeType : public GenericEdgeType {};
struct SplitEdgeType : public GenericEdgeType {};

struct GenericTriType
{
	Tptr                    concrete;
	GVptr                   verts[3];
};

struct pairTptr  //新的三角形对数据结构，为了判断是否继续查找 
{
	pairTptr(Tptr _t0, Tptr _t1)
	{
		t0 = _t0;
		t1 = _t1;
	}
	~pairTptr(){};
	bool equal(Tptr _t0, Tptr _t1){ return ((t0 == _t0&&t1 == _t1) || (t0 == _t1&&t1 == _t0)); }

	Tptr t0;
	Tptr t1;
};

struct GluePointMarker
{
	// list of all the vertices to be glued...
	cork_vector<IVptr>     copies;

	bool                    split_type; // splits are introduced
	// manually, not via intersection
	// and therefore use only e pointer
	bool                    edge_tri_type; // true if edge-tri intersection, false if tri-tri-tri
	Eptr                    e;
	Tptr                    t[3];
	std::vector<pairTptr>   ts;
	bool                    isbad;
	bool operator == (const struct GluePointMarker  &rhs) const {
		return copies[0]->coord == rhs.copies[0]->coord;
	}

};


inline IEptr find_edge(cork_vector<IEptr> &vec, Tptr key)
{
	for (IEptr ie : vec) {
		if (ie->other_tri_key == key)
			return ie;
	}
	return nullptr;
}

Vptr commonVert(Tptr t0, Tptr t1);

Vptr commonVert(Eptr e0, Eptr e1);

int  commonVertCount(Eptr e, Tptr t, int &idx);

bool hasCommonVert(const Tptr t0, const Tptr t1);

bool hasCommonVert(const Eptr e, const Tptr t);

bool hasCommonVert(const IEptr ie1, const IEptr ie2);

bool hasCommonVert(const IEptr ie1, const IEptr ie2, GVptr &gv);

bool hasCommonVert(const Eptr e0, const Eptr e1);

bool hasCommonVert(const Eptr e, const Vptr v);

void getCommonVert(const Tptr t0, const Tptr t1, std::vector<int>& commonVerts);

void getCommonVert(const Tptr t0, const Eptr e0, std::vector<int>& commonVerts);

void disconnectGE(GEptr ge);


template<class T, uint LEN>
inline void for_pairs(
	cork_vector<T> &vec,
	std::function<void(T&, T&)> func
	) {
	for (uint i = 0; i < vec.size(); i++)
		for (uint j = i + 1; j < vec.size(); j++)
			func(vec[i], vec[j]);
}

static Vec3d vPos(const Vptr v) {
	return *(reinterpret_cast<Vec3d*>(v->data));
}

//产生几何元素
::GeomBlob<Eptr>  edge_blob(Eptr e);
::GeomBlob<Tptr>  tri_blob(Tptr t);

//建立box
BBox3d buildBox(const Eptr e);
BBox3d buildBox(const IEptr e);
BBox3d buildBox(const Tptr t);
BBox3d buildBox(const Vec3d  &coord1, const Vec3d &coord2);

//转换为gmp可用的数据结构
void marshallArithmeticInput(Empty3d::TriIn &input, const Tptr t);
void marshallArithmeticInput(Empty3d::EdgeIn &input, const Eptr e);
void marshallArithmeticInput(Empty3d::TriEdgeIn &input, const Eptr e, const Tptr t);
void marshallArithmeticInput(Empty3d::TriTriTriIn &input, const Tptr t0, const Tptr t1, const Tptr t2);
void marshallArithmeticInput(Empty3d::EdgeEdgeIn &input, const Eptr e0, const Eptr e1);
void marshallArithmeticInput(Empty3d::EdgeEdgeIn &input, const Vec3d &e0a, const Vec3d &e0b, const Vec3d &e1a, const Vec3d &e1b);

//判断各种相交
bool checkIsct(const Eptr e, const Tptr t, Empty3d::IsctSwitch &type,bool checkbox=true);
bool checkIsct(const Tptr t0, const Tptr t1, const Tptr t2, Empty3d::IsctSwitch &type);
bool checkIsct(const Eptr e, const Eptr t, Empty3d::IsctSwitch &type);
bool checkIsct(const Vptr v, const Tptr t, Empty3d::IsctSwitch &type);
bool checkIsct(const Tptr inT, const Tptr isctT, const Eptr isctE, Empty3d::IsctSwitch &type);
bool checkIsct(const Tptr inT, const Eptr isctE0, const Eptr isctE1, Empty3d::IsctSwitch &type);
//坐标判断两条直线是否相交
bool checkTwoEdge(const Vec3d &e1, const Vec3d &e2, const Vec3d &t1, const Vec3d &t2, Empty3d::IsctSwitch &type);
//判断两个三角形是否共面
bool checkCoPlanar(const Tptr t0, const Tptr t1);
//点和三角形的关系，直接用坐标
bool checkInTri(const Vec3d &Pnt, const Vec3d& Tv0, const Vec3d& Tv1, const Vec3d& Tv2);
bool checkInTri(const Vec3d &Pnt, const Vec3d& Tv0, const Vec3d& Tv1, const Vec3d& Tv2, Empty3d::IsctSwitch &type);

//计算各种相交坐标
Vec3d computeCoords(const Eptr e, const Tptr t);
Vec3d computeCoords(const Tptr t0, const Tptr t1, const Tptr t2);
Vec3d computeCoords(const Eptr e0, const Eptr e1);
//计算共面情况下一条边和三角形的交点（交点可能在三角形的边上，和顶点上）
Vec3d computeCoords_coplanar(Eptr eisct, Tptr tisct, Empty3d::IsctSwitch &type);
//计算共面情况下一条边和三角形的交点（交点可能在三角形的边上，和顶点上），共面容差，在一定范围内认为共面
Vec3d computeCoords_coplanar(
	const double &tolerance, const Vec3d &pEa, const Vec3d &pEb, const Vec3d &pTa, const Vec3d &pTb, const Vec3d &pTc, Empty3d::IsctSwitch &type);

bool EdgeEdgeCoords(const Vec3d &e1, const Vec3d &e2, const Vec3d &t1, const Vec3d &t2, Vec3d &coord);
//查找函数
void  findIsctVert(const cork_vector<IVptr> &_iverts, IVptr &iv, const Vec3d &coord); //查找是否存在iv
//2维坐标变为3维坐标
bool toPnt3d_get_a_b(
	const double &x, const double &y, const double &x0, const double &y0, \
	const double &x1, const double &y1, const double &x2, const double &y2,
	double &a,double &b);


// 
double distancePntToPlanar(Vptr thePnt, Tptr tri);
