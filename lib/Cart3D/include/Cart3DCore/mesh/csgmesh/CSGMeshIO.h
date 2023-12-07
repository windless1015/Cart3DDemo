#ifndef CART3D_CSGMESH_IO_H
#define CART3D_CSGMESH_IO_H

#include <Cart3dMeshDefine.h>
#include <csgmesh/CSGMesh.h>

namespace Cart3D
{
	class CART3D_MESH_CLASS CSGMeshIO
	{
	public:
		static bool load_stl(CSGMesh& mesh,const std::string& filename);
		static bool load_obj(CSGMesh& mesh,const std::string& filename);
		static bool load_ply(CSGMesh& mesh,const std::string& filename);
	public:
		static bool write_stl(const CSGMesh& mesh, const std::string& filename);
		static bool write_ply(const CSGMesh& mesh, const std::string& filename);
	};				  
}


#endif