#ifndef CART3D_TOOLS_OPTIM_REMESH_H
#define CART3D_TOOLS_OPTIM_REMESH_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>
#include <csgmesh/CSGMesh.h>

namespace Cart3D
{
	class CART3D_TOOLS_CLASS OptimRemesh
	{
	public:
		static bool remesh(CSGMesh& mesh);
		static bool remesh(CSGMesh& mesh,cfloat mineg,cfloat maxeg);
	};

}

#endif