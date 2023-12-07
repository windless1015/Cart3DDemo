#ifndef CART3D_PARAMETERIZATION_H
#define CART3D_PARAMETERIZATION_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D
{
	class CART3D_TOOLS_CLASS Parameterzation
	{
	public:
		static void harmonic_parameterization(
			OpenTriMesh& mesh,
			std::vector<cvector2d>& texs,
			bool use_uniform_weights = false);
		static void lscm_parameterization(OpenTriMesh& mesh, std::vector<cvector2d>& texs);
	};

}




#endif


