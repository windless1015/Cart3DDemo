#pragma once
#ifndef CART3D_ALGORITHM_OPENMESHUTIL_H
#define CART3D_ALGORITHM_OPENMESHUTIL_H

#pragma warning(push)
#pragma warning(disable:4244)
#pragma warning(disable:26495)
#pragma warning(disable:26451)

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#undef min
#undef max

#include <Util/EigenUtil.h>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Geometry/EigenVectorT.hh>

#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyConnectivity.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/Traits.hh>

namespace Cart3D
{
	struct EigenTraits : OpenMesh::DefaultTraits {
		using Point = cvector3d;
		using Normal = cvector3d;
		using TexCoord2D = cvector2d;
		using TexCoord3D = cvector3d;
		using TexCoord1D = cfloat;
		using TextureIndex = int;
		//using Color = cvetor3uc;
	};

	using OpenTriMesh = OpenMesh::TriMesh_ArrayKernelT<EigenTraits>;
	using OpenPolygonMesh= OpenMesh::PolyMesh_ArrayKernelT<EigenTraits>;
	typedef OpenMesh::BaseHandle BH;
	typedef OpenTriMesh::VertexHandle   VH; 
	typedef OpenTriMesh::EdgeHandle     EH; 
	typedef OpenTriMesh::HalfedgeHandle HH; 
	typedef OpenTriMesh::FaceHandle     FH; 
	typedef OpenTriMesh::VertexIter     VI; 
	typedef OpenTriMesh::HalfedgeIter   HI; 
	typedef OpenTriMesh::EdgeIter       EI; 
	typedef OpenTriMesh::FaceIter       FI; 
	typedef OpenTriMesh::Vertex    Vertex;   
	typedef OpenTriMesh::Halfedge  Halfedge; 
	typedef OpenTriMesh::Edge      Edge;     
	typedef OpenTriMesh::Face      Face;     	
	typedef OpenTriMesh::ConstVertexIter    CVI; 
	typedef OpenTriMesh::ConstHalfedgeIter  CHI; 
	typedef OpenTriMesh::ConstEdgeIter      CEI; 
	typedef OpenTriMesh::ConstFaceIter      CFI; 
	typedef OpenTriMesh::VertexVertexIter    VVI;  
	typedef OpenTriMesh::VertexOHalfedgeIter VOHI; 
	typedef OpenTriMesh::VertexIHalfedgeIter VIHI; 
	typedef OpenTriMesh::VertexEdgeIter      VEI;  
	typedef OpenTriMesh::VertexFaceIter      VFI;  
	typedef OpenTriMesh::FaceVertexIter      FVI;  
	typedef OpenTriMesh::FaceHalfedgeIter    FHI;  
	typedef OpenTriMesh::FaceEdgeIter        FEI;  
	typedef OpenTriMesh::FaceFaceIter        FFI;  	
	typedef OpenTriMesh::ConstVertexVertexIter    CVVI;  
	typedef OpenTriMesh::ConstVertexOHalfedgeIter CVOHI; 
	typedef OpenTriMesh::ConstVertexIHalfedgeIter CVIHI; 
	typedef OpenTriMesh::ConstVertexEdgeIter      CVEI;  
	typedef OpenTriMesh::ConstVertexFaceIter      CVFI;  
	typedef OpenTriMesh::ConstFaceVertexIter      CFVI;  
	typedef OpenTriMesh::ConstFaceHalfedgeIter    CFHI;  
	typedef OpenTriMesh::ConstFaceEdgeIter        CFEI;  
	typedef OpenTriMesh::ConstFaceFaceIter        CFFI;  
}

#pragma warning(pop)


#endif