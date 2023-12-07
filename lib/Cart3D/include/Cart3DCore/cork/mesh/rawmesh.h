#pragma once

#include "vec.h"
#include "ray.h"
#include <csgmesh/CSGMesh.h>
#include "topofwd.h"
#include "cork/cork.h"
#include <memory>
#include <vector>
#include <functional>
#include <parallel_hashmap/phmap.h>
#include <stdint.h>
#include "traits.h"
#ifdef min
#undef min
#endif
#include  <tbb/tbb.h>
#include <topofwd.h>
struct MiniVertex
{
	Vec3d pos;
	Vec3d ori;
	char flag; //meshid(-1则可能是新增的点也可能是老的点)
	MiniVertex():
		ori(DBL_MAX, DBL_MAX, DBL_MAX),
		pos(0,0,0),
		flag(-1)
	{}
};

struct MiniTriangle
{
	int a, b, c;
};


struct CorkVertex : public MiniVertex
{
	CorkVertex() :MiniVertex(){}
};
struct CorkTriangle : public MiniTriangle, public BoolData
{

};

struct RawMesh
{
	cork_vector<CorkVertex> vertices;
	cork_vector<CorkTriangle> triangles;
};

template<class GeomIdx>
class AABVH;

class CorkMesh
{
public:
	CorkMesh(const BaseTriMesh& btm, int fixpoint, char flag);
public:
	CorkMesh(){ }
	CorkMesh(CorkMesh &&src);
	CorkMesh(CorkMesh &src);
	CorkMesh(const RawMesh &raw);
	
	class  IsctProblem;
	virtual ~CorkMesh(){}

	void operator=(CorkMesh &&src);

	RawMesh raw() const;
	void getBtm(BaseTriMesh& btm) const;
	void getBtm(BaseTriMesh& btm,std::vector<int> &oriVmap) const;
	void getBtmTmap(BaseTriMesh& btm, std::vector<uint> &oriTMap) const;

	inline int numVerts() const { return verts.size(); }
	inline int numTris() const { return tris.size(); }

	 inline void for_verts(std::function<void(CorkVertex &v)> func)
	{
		for (auto &v : verts)
			func(v);
	}

    inline void for_tris(std::function<void(BoolData &, CorkVertex &, CorkVertex &, CorkVertex &)> func)
	{
		tbb::parallel_for(0, (int)tris.size(), [&](int i) {
			auto& tri = tris[i];
		    auto& a = verts[tri.a];
		    auto& b = verts[tri.b];
		    auto& c = verts[tri.c];
		    func(tri.data, a, b, c);
		});
	}

    inline void for_edges(
		std::function<void(CorkVertex &, CorkVertex &)> start,
		std::function<void(BoolData &t,
		CorkVertex &, CorkVertex &, CorkVertex &)> each_tri
		) {
		EGraphCache<BoolData> cache = createEGraphCache<BoolData>();
		for (uint i = 0; i < cache.skeleton.size(); i++) {
			for (auto &entry : cache.skeleton[i]) {
				uint j = entry.vid;
				start(verts[i], verts[j]);
				for (uint tid : entry.tids) {
					Tri &tri = tris[tid];
					each_tri(tri.data, verts[tri.a], verts[tri.b], verts[tri.c]);
				}
			}
		}
	}

	void unify(CorkMesh &cp);
	void mergeVertex();
	void checkDeTri();
	void initOrigIdx();


	struct Isct {
		Ray3d   ray;
		bool    exists;

		uint    tri_id;
		Vec3d   isct;
		Vec3d   bary;
	};

	bool isClosed();

public:
	class  IsctProblem;
	class  IsctWithAnothor;
	class  CoPlanarProblem;
public: 
	bool resolveIntersections(bool doSelf = true);
	void resolveCoplane(double Tolerance);
	bool isSelfIntersecting(); 

public: 
	void boolOp(CorkMesh& rhs, BooleanMesh& resm, bool isSelf = false);
	void boolUnion(CorkMesh& rhs, bool isSelf = false);
	void boolOuterOne(CorkMesh& rhs, bool isSelf = false);
	void boolOuterTwo(CorkMesh& rhs, bool isSelf = false);

	void boolIsct(CorkMesh& rhs, bool isSelf = true);
	void boolInnerOne(CorkMesh& rhs, bool isSelf = false);
	void boolInnerTwo(CorkMesh& rhs, bool isSelf = false);

	void boolDiff(CorkMesh &rhs,bool isSelf = true);
	
	void boolXor(CorkMesh &rhs, bool isSelf = true);

	void resolve(CorkMesh &rhs, DoubleFaceCode classify);
	void glueMesh(double Tolerance);
	bool resolveSelf(DoubleFaceCode classify);


private:    

	inline void subdivide_tri(uint t_piece_ref, uint t_parent_ref)
	{
		tris[t_piece_ref].data.bool_alg_data = tris[t_parent_ref].data.bool_alg_data;
	}



struct Vec3dHasher{
	size_t operator()(const Vec3d& k) const
	{
		size_t h1 = std::hash<double>()(k.x);
		size_t h2 = std::hash<double>()(k.y);
		size_t h3 = std::hash<double>()(k.z);
		return (h1 ^ (h2 << 1)) ^ h3;
	}
};

struct Vec3dEuqal {
	bool operator()(const Vec3d& lhs, const Vec3d& rhs) const {
		return
			(lhs.x == rhs.x) &&
			(lhs.y == rhs.y) &&
			(lhs.z == rhs.z);
	}
};


public: 
	cork_vector<Tri>        tris;
	cork_vector<CorkVertex>   verts;
private:  
	struct TopoCache;

public:
	struct TopoCacheFast;
private:  
	class  EdgeProblem;
	class  TriangleProblem; // support type for IsctProblem
	typedef TriangleProblem* Tprob;
	typedef EdgeProblem*     Eprob;

private:  
	class BoolProblem;
	class CorkMeshToolFunc;

private:
private:    // caches
	template<class Edata>
	struct EGraphEntry {
		uint                vid;
		cork_vector<uint>   tids;
		Edata               data;
		inline EGraphEntry() {}
		inline EGraphEntry(uint vid_) : vid(vid_) {}
	};

	template<class Edata>
	struct EGraphCache {
		std::vector< cork_vector<EGraphEntry<Edata>> > skeleton;
		inline EGraphEntry<Edata> & operator()(uint i, uint j) {
			if (i > j)  std::swap(i, j);
			uint N = (uint)skeleton[i].size();
			for (uint k = 0; k < N; k++) {
				if (skeleton[i][k].vid == j)
					return skeleton[i][k];
			}
			skeleton[i].push_back(EGraphEntry<Edata>(j));
			return skeleton[i][N];
		}
		inline void for_each(std::function<void(
			uint i, uint j, EGraphEntry<Edata> &entry
			)> action
			) {
			for (uint i = 0; i < skeleton.size(); i++) {
				for (auto &entry : skeleton[i]) {
					action(i, entry.vid, entry);
				}
			}
		}
	};

	template<class Edata>
	EGraphCache<Edata> createEGraphCache(){
		EGraphCache<Edata> result;
		result.skeleton.resize(verts.size());
		for (uint tid = 0; tid < tris.size(); tid++) {
			const Tri &tri = tris[tid];

			if (tri.a < tri.b)
				result(tri.a, tri.b).tids.push_back(tid);
			else
				result(tri.b, tri.a).tids.push_back(tid);

			if (tri.a < tri.c)
				result(tri.a, tri.c).tids.push_back(tid);
			else
				result(tri.c, tri.a).tids.push_back(tid);

			if (tri.b < tri.c)
				result(tri.b, tri.c).tids.push_back(tid);
			else
				result(tri.c, tri.b).tids.push_back(tid);
		}
		return result;
	}
};

