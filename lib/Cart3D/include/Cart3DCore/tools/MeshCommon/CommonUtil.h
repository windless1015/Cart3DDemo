#ifndef CART3D_COMMON_UTIL_H
#define CART3D_COMMON_UTIL_H

#include <Cart3DToolsDefine.h>
#include "Util/OpenMeshUtil.h"
#include <csgmesh/CSGMesh.h>
#include <csgmesh/CSGMesh.h>
namespace Cart3D
{
	class CART3D_TOOLS_CLASS CommonUtil
	{
	public:
		static bool swap_to_fast_mesh(
			const OpenTriMesh& mesh,
			std::vector<cvector3d>& pts,
			std::vector<int>& tris, bool reverse = false);
		static bool swap_to_fast_mesh(
			const std::vector<cvector3d>& pts,
			const std::vector<int>& tris,
			OpenTriMesh& mesh, bool reverse = false);

		static bool swap_to_fast_mesh(
			const CSGMesh& mesh,
			std::vector<cvector3d>& pts,
			std::vector<int>& tris, bool reverse = false);
		static bool swap_to_fast_mesh(
			const std::vector<cvector3d>& pts,
			const std::vector<int>& tris,
			CSGMesh& mesh,bool reverse=false);



		static cfloat compute_mesh_avg_edgelength(const OpenTriMesh& mesh);
		static cfloat compute_mesh_max_edgelength(const OpenTriMesh& mesh);
		static cfloat compute_mesh_min_edgelength(const OpenTriMesh& mesh);
		static cvector3d compute_egdeinfo(const OpenTriMesh& mesh);
		static cvector3d compute_mesh_cent(const OpenTriMesh& mesh);
		static cvector3d compute_area_direction(const OpenTriMesh& mesh);
		static cvector3d iteration_main_direction(const OpenTriMesh& mesh);
	public:
		static bool add_mesh(OpenTriMesh& mesh, const OpenTriMesh& submesh);
		static bool copy_mesh(OpenTriMesh& dest, const OpenTriMesh& src);
	public:
	

	};


}


#endif