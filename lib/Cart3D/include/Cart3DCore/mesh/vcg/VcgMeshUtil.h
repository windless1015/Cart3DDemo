#ifndef CART3D_VCGMES_WRAPPER_H
#define CART3D_VCGMES_WRAPPER_H
#include <Cart3DMeshDefine.h>
#include <csgmesh/CSGMesh.h>
#include <vcg/mesh/meshtopo.h>

namespace Cart3D
{  
	class FixVcgVert;
	class FixVcgEdge;
	class FixVcgFace;
	struct CART3D_MESH_CLASS FixVcgType : public vcg::UsedTypes<
		Use<FixVcgVert>::AsVertexType,
		Use<FixVcgEdge>::AsEdgeType,
		Use<FixVcgFace>::AsFaceType>
	{};
	class CART3D_MESH_CLASS FixVcgVert : public vcg::Vertex<FixVcgType,
		vertex::BitFlags,
		vertex::VFAdj,
		vertex::VEAdj,
		vertex::Coord3f>
	{};
	class CART3D_MESH_CLASS FixVcgEdge : public vcg::Edge <FixVcgType,
		edge::EVAdj,
		edge::VEAdj,
		edge::EFAdj,
		edge::VertexRef,
		edge::BitFlags>
	{};
	class CART3D_MESH_CLASS FixVcgFace : public vcg::Face<FixVcgType,
		face::FFAdj,
		face::VFAdj,
		face::VertexRef,
		face::Normal3f,
		face::BitFlags>
	{};
	class CART3D_MESH_CLASS FixVcgMesh : public vcg::tri::TriMesh<
		std::vector<FixVcgVert>,
		std::vector<FixVcgEdge>,
		std::vector<FixVcgFace>>
	{};

	struct CART3D_MESH_CLASS FixTri
	{
		FixTri() {}
		FixTri(const int &a, const int &b, const int &c) { v[0] = a; v[1] = b; v[2] = c; }

		int v[3];
		int otherVert;
		cvector3d n;
		bool operator == (const FixTri &ori)const
		{
			if (v[0] == ori.v[0] && v[1] == ori.v[1] && v[2] == ori.v[2]) return true;
			if (v[0] == ori.v[0] && v[1] == ori.v[2] && v[2] == ori.v[1]) return true;

			if (v[0] == ori.v[1] && v[1] == ori.v[0] && v[2] == ori.v[2]) return true;
			if (v[0] == ori.v[1] && v[1] == ori.v[2] && v[2] == ori.v[0]) return true;

			if (v[0] == ori.v[2] && v[1] == ori.v[0] && v[2] == ori.v[1]) return true;
			if (v[0] == ori.v[2] && v[1] == ori.v[1] && v[2] == ori.v[0]) return true;
			return false;
		}
	};


	CART3D_MESH_API void BaseTriMesh_to_VcgMesh(const CSGMesh &in, FixVcgMesh &out);

	CART3D_MESH_API void VcgMesh_to_BaseTriMesh(const FixVcgMesh &in, CSGMesh &out);
	

}

#endif