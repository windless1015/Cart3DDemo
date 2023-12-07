#pragma once
#ifndef CART3D_OPTIMICP_SOLVER_H
#define CART3D_OPTIMICP_SOLVER_H
#include "Cart3DSlamDefine.h"
#include "icp/PointCloudUtil.h"
#include "icp/ICPUtil.h"
namespace Cart3D
{

	struct CART3D_SLAM_CLASS OptimICP {
	public:
		/*
		 * @brief 对称ICP配准算法(固定轴)
		 * @see paper A Symmetrix Objective Functin for ICP
		 * @see paper Efficient Varirants of the ICP Algorithm
		 * @param[in]     mesh1 mesh1
		 * @param[in]     mesh2 mesh2
		 * @param[in]       xf1 mesh1初始矩阵
		 * @parma[out]      xf2 mesh2初始矩阵
		 * @param[in]  do_scale 是否缩放变换
		 * @param[in] do_affine 是否剪切变换缩放
		 */
		static cfloat optim_rt(
			PointField& mesh1, PointField& mesh2,
			const cmatrix4d& xf1, cmatrix4d& xf2,
			const ICPTransformStyle& style,
			bool do_scale, bool do_affine = false);

		static cfloat optim_rt(
			PointField& mesh1, PointField& mesh2,
			std::vector<cfloat>& weight1, std::vector<cfloat>& weight2,
			const cmatrix4d& xf1, cmatrix4d& xf2,
			const ICPTransformStyle& style,
			bool do_scale, bool do_affine = false);
	};
}
#endif
