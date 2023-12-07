#ifndef CART3D_TOOLS_SMOOTH_REGION_H
#define CART3D_TOOLS_SMOOTH_REGION_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>

namespace Cart3D
{
	class CART3D_TOOLS_CLASS SmoothRegion
	{
	public:
		static bool smooth_surf_cx(OpenTriMesh& trimesh, const std::vector<VH>& smooth, int cx);


	};
}




#endif