#pragma once
#ifndef CART_SEGMENT_H
#define CART_SEGMENT_H

#include <Cart3DToolsDefine.h>
#include "Util/OpenMeshUtil.h"
#include "Util/TreeUtil.h"

namespace Cart3D
{
	struct CART3D_TOOLS_CLASS SegParam
	{
		int init_diffusion = 3;
		cfloat min_path_ratio=0.5;
	};

	class CART3D_TOOLS_CLASS MeshSegment
	{
	public:
		/*
		 * @brief 优化最大分割流种子点 
		 * @param[in]    mesh 待处理的网格
		 * @param[in] weights 分割场
		 * @param[in]  vhseed 分割种子点
		 * @param[out]   seed 优化后的种子点
		 * return 是否优化成功
		 */
		static bool optim_max_flow_seed(
			const OpenTriMesh& mesh,
			const std::vector<cfloat>& weights,
			const VH& vhseed,
			VH& seed);
		/* 
		 * @brief 最大流分割算法，这里采用的一般是曲率或者测地距离等等
		 * @param[in]     mesh 待分割的mesh
		 * @param[in]    seeds 分割的种子点
		 * @param[in]  weights 分割场权重
		 * @param[out]  labels 分割结果
		 * @return 是否分割成功
		 */
		static bool max_flow_graph_cut(
			const OpenTriMesh& mesh,
			const fast_map<int,tree_set<VH>>& seeds,
			const std::vector<cfloat>& weights,
			std::vector<int>& labels,
			const SegParam& param=SegParam());
	public:
		/*
		 * @brief 优化最小分割流种子点
		 * @param[in]    mesh 待处理的网格
		 * @param[in] weights 分割场
		 * @param[in]  vhseed 分割种子点
		 * @param[out]   seed 优化后的种子点
		 * return 是否优化成功
		 */
		static bool optim_min_flow_seed(
			const OpenTriMesh& mesh,
			const std::vector<cfloat>& weights,
			const VH& vhseed,
			VH& seed);

		/*
		 * @brief 最小流分割算法，这里采用的一般是曲率或者测地距离等等
		 * @param[in]     mesh 待分割的mesh
		 * @param[in]    seeds 分割的种子点
		 * @param[in]  weights 分割场权重
		 * @param[out]  labels 分割结果
		 * @return 是否分割成功
		 */
		static bool min_flow_graph_cut(
			const OpenTriMesh& mesh,
			const fast_map<int, tree_set<VH>>& seeds,
			const std::vector<cfloat>& weights,
			std::vector<int>& labels,
			const SegParam& param=SegParam());

		

	};

}



#endif