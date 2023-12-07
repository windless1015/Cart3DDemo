#ifndef CART3D_TOOLS_REFINE_H
#define CART3D_TOOLS_REFINE_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>

namespace Cart3D
{
	class CART3D_TOOLS_CLASS Refine
	{
	public:
		static void fairing(OpenTriMesh& mesh, OpenMesh::VPropHandleT< cfloat >& scale_, std::vector< FH >& _faceHandles);
	
		
	};
}




#endif