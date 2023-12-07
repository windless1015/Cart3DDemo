#pragma once
#ifndef CART3D_SYM_ICP_H
#define CART3D_SYM_ICP_H
#include "Cart3DSlamDefine.h"
#include <icp/PointCloudUtil.h>
#include <icp/ICPUtil.h>

namespace Cart3D
{
	class CART3D_SLAM_CLASS  SymICP
	{
	public:
		/*
		 * @brief 对称icp配准
		 * @param[in]          src 源点云
		 * @param[in]         smat 源点云矩阵
		 * @param[in]          dst 目标点云
		 * @param[in|out]     dmat 目标点云变换矩阵
		 * @param[in]     do_scale 是否各向同性缩放
		 * @param[in]    do_affine 是否各向异性缩放
		 */
		static cfloat symm_icp(
			const PointField& src, const cmatrix4d& smat,
			const PointField& dst, cmatrix4d& dmat,
			bool do_scale, bool do_affine, const ICPParam& param = ICPParam());
	public:
		/*
		 * @brief 对称icp配准
		 * @param[in]      meshSrc 源点云
		 * @param[in]         smat 源点云矩阵
		 * @param[in]      meshDst 目标点云
		 * @param[in|out]     dmat 目标点云变换矩阵
		 * @param[in]     weights1 源点云权重分配
		 * @param[in]     weights2 目标点云权重分配
		 * @param[in]     do_scale 是否各向同性缩放
		 * @param[in]    do_affine 是否各向异性缩放
		 */
		static cfloat symm_icp(
			const PointField& meshSrc, const cmatrix4d& smat,
			const PointField& meshDst, cmatrix4d& dmat,
			std::vector<cfloat>& weights1, std::vector<cfloat>& weights2,
			bool do_scale, bool do_affine, const ICPParam& param = ICPParam());
	};
}



#endif