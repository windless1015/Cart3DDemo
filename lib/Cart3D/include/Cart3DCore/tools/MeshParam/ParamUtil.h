#ifndef CART3D_TOOLS_PARAMUTIL_H
#define CART3D_TOOLS_PARAMUTIL_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D {

	class CART3D_TOOLS_CLASS ParamUtil
	{
	public:
		static bool denoise(OpenTriMesh& mesh);
		static cfloat compute_angle_rad(const cvector3d& P, const cvector3d& Q, const cvector3d& R);
		static cfloat compute_weight(const OpenTriMesh& mesh, const VH& vert, const VH& around);
		static cfloat compute_weight(const OpenTriMesh& mesh,const HH& hh);
		static void compute_gradients(const OpenTriMesh& mesh, const FH& fh,
			std::vector<std::pair<HH, cvector2d>>& hweights);
	};


}
#endif