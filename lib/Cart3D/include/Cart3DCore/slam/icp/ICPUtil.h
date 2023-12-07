#ifndef CART3D_ICPUTIL_H
#define CART3D_ICPUTIL_H
#include "Cart3DSlamDefine.h"
#include "PointCloudUtil.h"

namespace Cart3D
{

	enum class ICPMethod
	{
		Combined = 0, // ǰ���ν��е�Ե��icp���������㵽���Լ��Գ�icp�������
		PointToPoint = 1, // ��Ե�icp
		PointToPlane = 2, // �����icp
		SymmetrixIcp = 3, // �Գ�icp��׼
	};

	enum class ICPMode
	{
		AnyXf, // 6���ɶ�icp
		OrthogonalAxis, // 5���ɶ�icp���̶�һ����
		FixedAxis, // 4���ɶ�icp,�̶�������ת�Լ���������˶�
		TranslationOnly // 3���ɶ�icp,ֻ����ƽ���˶�
	};

	enum class ICPDefromation
	{
		Rigid,  //�������
		cfloat, //�Ǹ������
		Affine, //�������Ա���
	};

	struct CART3D_SLAM_CLASS PtPair {
		cvector3d p1, n1, p2, n2;
		PtPair(const cvector3d &p1_, const cvector3d &n1_,
			const cvector3d &p2_, const cvector3d &n2_) :
			p1(p1_), n1(n1_), p2(p2_), n2(n2_)
		{}
	};

	struct CART3D_SLAM_CLASS ICPParam
	{
		ICPMethod method;
		ICPMode   mode;
		ICPDefromation deform;

		cvector3f fixed_rotation_axis; //�̶���ת��
		cvector3f fixed_rotation_center; //�̶���ת����

		int max_iters;
		cfloat termination_iter_thresh;
		cfloat final_iter;
		int min_pairs;
		int desired_pairs;
		int desired_final_pairs;
		int cdf_update_interval;
		cfloat approx_eps;
		bool use_norm_compate;
		cfloat huber_thresh_mult;
		cfloat regularization;
		cfloat dist_thresh_mult;
		cfloat dist_thresh_mult_final;
		cfloat angle_thresh_mult;
		cfloat angle_thresh_min;
		cfloat angle_threah_max;

		ICPParam();
	};


	struct CART3D_SLAM_CLASS Affine
	{
		cmatrix3d rot;
		cvector3d trans;
		Affine(const cmatrix3d& _rot, const cvector3d& _trans);
		Affine(const cmatrix4d& mat);
		Affine();
		cvector3d operator() (const cvector3d & x) const;
		cvector3d rot_only(const cvector3d & x) const;
		cvector3d trans_only(const cvector3d & x) const;
		cmatrix4d to4d()const;
	};

	struct CART3D_SLAM_CLASS ICPTransformStyle
	{
		bool is_fix_axis;
		cvector3d fix_axis;
		bool is_fix_center; //��ʱ��֧��
		cvector3d fix_center;
		ICPTransformStyle();
	};
}

#endif