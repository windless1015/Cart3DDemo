#ifndef CART3D_MATH_AXISANGLE_H
#define CART3D_MATH_AXISANGLE_H

#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{
	class CART3D_MATH_CLASS AxisAngle
	{
	public:
		static void rotation_matrix_to_axis_angle(
			const cmatrix3d &rotmat,
			cvector3d &axis,cfloat &angle);

		static void rotation_matrix_to_quaternion(
			const cmatrix3d &rotmat, cquaternion &quaternion);
	};

}


#endif