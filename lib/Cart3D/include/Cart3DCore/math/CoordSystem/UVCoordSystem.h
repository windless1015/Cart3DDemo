#ifndef CART3D_UVCOORD_SYSTEM_H
#define CART3D_UVCOORD_SYSTEM_H
#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{
	class CART3D_MATH_CLASS UVCoordSystem
	{
	public:
		static void generate_complement_basis(cvector3d& rkU, cvector3d& rkV, const cvector3d& rkW);
	};
}



#endif