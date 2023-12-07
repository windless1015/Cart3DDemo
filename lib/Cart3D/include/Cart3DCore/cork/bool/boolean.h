#pragma once

#include "topo.h"
#include <queue>
#include <tree/Bvh.h>
#include <topofwd.h>


class CorkMesh::BoolProblem
{
public:
	//判断点在三角形的哪里
	enum Orientation{
		POSITIVE = 0,
		NEGATIVE = 1,
		COPLANAR = 2,
		COLLINEAR =3
	};

	// choose what to remove
	enum TriCode { KEEP_TRI, DELETE_TRI, FLIP_TRI };

	enum EntryCode { NOJUMP = 0, JUMP = 1, HASCOPLANR = 2, ISCTNOMANIFOLD = 3 };

public:
	BoolProblem(CorkMesh *owner) : mesh(owner)
	{}
	virtual ~BoolProblem() {}
	void setMesh(CorkMesh *owner) {
		mesh = owner;
	}
	
	// do things
	void doResolve(CorkMesh &rhs, DoubleFaceCode classify);
	bool doResolveSelf(DoubleFaceCode classify);
	void doGlueMeshs(double Tolerance);
	void doSetup(CorkMesh& rhs, bool isSelf = true);
	void ray_way_inout();
	void doDeleteAndFlip(std::function<TriCode(byte bool_alg_data)> classify);
	void doDeleteAndFlipFast(std::function<TriCode(byte bool_alg_data)> classify);


private: // methods
	struct BoolEdata {
		EntryCode classify;
	};

	inline byte& boolData(uint tri_id);
	void findComponents(cork_vector< cork_vector<uint> > &components);


	void removeDoubleFace(DoubleFaceCode classify = DOUBLEFACE_AUTO_DELETE);
	void populateECache();
	inline void for_ecache(
		std::function<void(uint i, uint j,
		bool isisct,
		const cork_vector<uint> &tids)> action
		);
	bool isInside(uint tid, byte operand);
	bool isInside(uint tid, byte operand, Cart3D::Cart3DBvh& bvh);
	bool isInside(uint tid, byte operand, Vec3d& dir);
private: // data
	CorkMesh                     *mesh;
	EGraphCache<BoolEdata>      ecache;
public:
//	EGraphCache<BoolEdata>      ecache;
public:
	friend class CorkMesh::CorkMeshToolFunc;
};

