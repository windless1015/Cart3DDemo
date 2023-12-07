#pragma once
#ifndef CART3D_MESHFAIR_H
#define CART3D_MESHFAIR_H

#include <Cart3DToolsDefine.h>
#include "Util/OpenMeshUtil.h"

namespace Cart3D
{
	class CART3D_TOOLS_CLASS MeshFair
	{
	public:
		/*
		 * @brief 网格曲率整流罩算法
		 * @detial
		 * @param[in+out]  mesh 三角网格
		 * @param[in]       vhs 待整流的区域
		 * @param[in]        fc 整流曲率连续性
		 * @return 是否整流成功
		 */
		static bool fair(
			OpenTriMesh& mesh,
			const std::vector<VH>& vhs,
			unsigned int fc);
	public:
		/*
		 * @brief 快速网格曲率整流罩算法
		 * @detial
		 * @param[in+out]  mesh 三角网格
		 * @param[in]       vhs 待整流的区域
		 * @param[in]        fc 整流曲率连续性
		 * @return 是否整流成功
		 */
		static bool fast_fair(
			OpenTriMesh& mesh,
			const std::vector<VH>& vhs,
			unsigned int fc);
	public:
		//全局光滑
		static bool robust_fair(
			OpenTriMesh& mesh,
			const std::vector<VH>& vhs,
			unsigned int fc,
			cfloat wgt=5);
		//如果遇到网格量数据非常大的时候，这样会更快
		static bool local_fair(
			OpenTriMesh& mesh,
			const std::vector<VH>& vhs,
			unsigned int fc);
	};

}

#endif