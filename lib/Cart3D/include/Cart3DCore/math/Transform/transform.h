#ifndef CART3D_TRANSFORMation_H
#define CART3D_TRANSFORMation_H
#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>
#include <CoordSystem/CoordSystem.h>

namespace Cart3D
{
	class CART3D_MATH_CLASS Transform
	{
	public:
		static cmatrix4d swap_coord_system(const CoordSystem& src, const CoordSystem& dst);
		//
		static cmatrix4d coord_trans(
			const cvector3d& src, const cvector3d& sxdir, const cvector3d& sydir, const cvector3d& szdir,
			const cvector3d& tgt, const cvector3d& txdir, const cvector3d& tydir, const cvector3d& tzdir);
		static cmatrix4d from_to_axis(
			const cvector3d& ori,const cvector3d& ori_axis,
			const cvector3d& dst,const cvector3d& dst_axis);

		//����ori�����ƶ�d
		static cmatrix4d trans_mat(const cvector3d& ori, cfloat d);
		//������ת
		static cmatrix4d rot_mat(const cvector3d& ori, const cvector3d& axis, cfloat ang);
		static cmatrix4d rot_mat(const cvector3d& axis, cfloat ang);
		
		//opengl�Ӿ�������eye���Ӿ���㣬center��Ŀ�����ģ�z������
		static cmatrix4d look_at_matrix(
			const cvector3d& eye,const cvector3d& center,const cvector3d& up);
	};
}

#endif