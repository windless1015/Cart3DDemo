
#pragma once
#include "traits.h"
#include "vec.h"

namespace Empty3d 
{

	struct IsctSwitch
	{
		int data;
		IsctSwitch() { data = -1; }
	};

	enum isctType
	{
		IsctType_TriEdge,
		IsctType_VertTri,
		IsctType_EdgeEdge,
	};

	enum isctTriEdgeCode
	{
		TriEdge_NoIsct = 0,
		TriEdge_CommonIsct = 1,
		TriEdge_CoPlanar = 2,
		TriEdge_Tetrahedron = 3,
		TriEdge_InTriEdge = 4,
		TriEdge_InTriVert = 8,
		TriEdge_InEdgeVert = 16,
		TriEdge_InTriIdx0 = 32,
		TriEdge_InTriIdx1 = 64,
		TriEdge_InTriIdx2 = 128,
		TriEdge_InEdgeIdx0 = 256,
		TriEdge_InEdgeIdx1 = 512
	};

	enum isctTriVertCode
	{
		TriVert_OutSide = 0,
		TriVert_InSide = 1,
		TriVert_InTriEdge0 = 2,
		TriVert_InTriEdge1 = 4,
		TriVert_InTriEdge2 = 8,
		TriVert_InTriVert0 = 16,
		TriVert_InTriVert1 = 32,
		TriVert_InTriVert2 = 64
	};

	enum isctEdgeEdgeCode
	{
		EdgeEdge_NoIsct = 0,
		EdgeEdge_CommonIsct = 1,
		EdgeEdge_InEdge0Vert0 = 4,
		EdgeEdge_InEdge0Vert1 = 8,
		EdgeEdge_InEdge1Vert0 = 16,
		EdgeEdge_InEdge1Vert1 = 32
	};


	enum isctThreeElementCode
	{
		ThreeElement_NoIsct = 0,
		ThreeElement_CommonIsct = 1,
		ThreeElement_Coline = 2
	};

	struct TriIn
	{
		Vec3d p[3];
	};

	struct EdgeIn
	{
		Vec3d p[2];
	};

	struct VertexIn
	{
		Vec3d p;
	};

	struct TriEdgeIn
	{
		TriIn   tri;
		EdgeIn  edge;
	};

	//void  getperturb();
	bool isEmpty(const TriEdgeIn &input);
	Vec3d coords(const TriEdgeIn &input);
	bool emptyExact(const TriEdgeIn &input, IsctSwitch &type);
	Vec3d coordsExact(const TriEdgeIn &input);


	struct TriTriTriIn
	{
		TriIn tri[3];
	};

	bool isEmpty(const TriTriTriIn &input);
	Vec3d coords(const TriTriTriIn &input);
	bool emptyExact(const TriTriTriIn &input, IsctSwitch &type);
	Vec3d coordsExact(const TriTriTriIn &input);


	struct EdgeEdgeIn
	{
		EdgeIn edge0;
		EdgeIn edge1;
	};
	//bool isEmpty(const EdgeEdgeIn &input);
	//Vec3d coords(const EdgeEdgeIn &input);
	bool emptyExact(const EdgeEdgeIn &input, IsctSwitch &type);
	Vec3d coordsExact(const EdgeEdgeIn &input);

	struct VertexTriIn
	{
		VertexIn vert;
		TriIn tri;
	};

	//bool isEmpty(const VertexTriIn &input);
	//Vec3d coords(const VertexTriIn &input);
	bool emptyExact(const VertexTriIn &input, IsctSwitch &type);
	//Vec3d coordsExact(const VertexTriIn &input);

	bool equalExact(const Vec3d &p0, const Vec3d &p1);

	extern int degeneracy_count; // count degeneracies encountered
	extern int exact_count; // count of filter calls failed
	extern int callcount; // total call count

	
	struct TriTriEdgeIn
	{
		TriIn   inT;
		TriIn   isctT;
		EdgeIn  isctE;
	};

	bool emptyExact(const TriTriEdgeIn &input, IsctSwitch &type);


	struct TriEdgeEdgeIn
	{
		TriIn   inT;
		EdgeIn  isctE[2];
	};

	bool emptyExact(const TriEdgeEdgeIn &input, IsctSwitch &type);

	
	CommonIsctClassify decodeIsctClassify(const IsctSwitch &type, const isctType &swichType, int &idx1, int &idx2);


	bool isSwitchOpen(const int &switchCode, const int&key);



	Orientation orient3dExact(const cvector3d &p0, const cvector3d &p1, const cvector3d &p2, const cvector3d &p3);
	Orientation orient3dCoplanarExact(const cvector3d &p0, const cvector3d &p1, const cvector3d &p2, const cvector3d &p3);
	int normlDotExact(const cvector3d &p0, const cvector3d &p1, const cvector3d &p2, const cvector3d &norml);
} // end namespace Empty3d




