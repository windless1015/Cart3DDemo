#ifndef CART3D_ICPUTIL_H
#define CART3D_ICPUTIL_H
#include "Cart3DSlamDefine.h"
#include "PointCloudUtil.h"

namespace Cart3D
{

	enum class ICPMethod
	{
		Combined = 0, // 前两次进行点对点的icp，接下来点到面以及对称icp交替进行
		PointToPoint = 1, // 点对点icp
		PointToPlane = 2, // 点对面icp
		SymmetrixIcp = 3, // 对称icp配准
	};

	enum class ICPMode
	{
		AnyXf, // 6自由度icp
		OrthogonalAxis, // 5自由度icp，固定一个轴
		FixedAxis, // 4自由度icp,固定绕轴旋转以及延轴进行运动
		TranslationOnly // 3自由度icp,只进行平移运动
	};

	enum class ICPDefromation
	{
		Rigid,  //刚体变形
		cfloat, //非刚体变形
		Affine, //各向异性变形
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

		cvector3f fixed_rotation_axis; //固定旋转轴
		cvector3f fixed_rotation_center; //固定旋转中心

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
		bool is_fix_center; //暂时不支持
		cvector3d fix_center;
		ICPTransformStyle();
	};
}

#endif