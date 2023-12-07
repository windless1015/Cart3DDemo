#ifndef CART3D_TOOLS_MESH_LOOP_H
#define CART3D_TOOLS_MESH_LOOP_H

#include <Cart3DToolsDefine.h>
#include <MeshCSG/MeshCSGUtil.h>

namespace Cart3D
{
	
	class CART3D_TOOLS_CLASS MeshLoop
	{
	public:


		static bool fast_mesh_plane_intersect(
			const std::vector<cvector3d>& pts, const std::vector<int>& tris,
			const cvector3d& plane_pt, const cvector3d& plane_dir,
			std::vector<InterLoop>& paths);


		static bool mesh_plane_intersect(
			const std::vector<cvector3d>& pts,const std::vector<int>& tris,
			const cvector3d& plane_pt,const cvector3d& plane_dir,
			std::vector<InterLoop>& paths);
	public:

		static void decomp_path(const InterLoop&loop, std::vector<Path3DId>& path);

	};


}





#endif