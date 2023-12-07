#pragma once
#ifndef CART3D_TOOLS_MESH_REMOVE_SPIKES_H
#define CART3D_TOOLS_MESH_REMOVE_SPIKES_H

#include <Cart3DToolsDefine.h>
#include "Util/OpenMeshUtil.h"

namespace Cart3D
{

	class CART3D_TOOLS_CLASS MeshRemoveSpikes
	{
	public:
		/*
		 * @brief 计算mesh 尖刺点
		 * @param[in]                 mesh 待计算的mesh
		 * @param[in]  max_gauss_variation 最大尖刺阈值
		 * @param[out]              spikes 尖刺区域情况
		 * @return 是否计算成功
		 */
		static bool compute_spikes(const OpenTriMesh& mesh, cfloat max_gauss_variation, std::vector<char>& spikes);
		/*
		 * @brief 去除mesh尖刺
		 * @param[in]       mesh 待处理的mesh
		 * @param[in]       spikes 尖刺区域情况
		 * @return 是否计算成功
		 */
		static bool remove_spikes(OpenTriMesh& mesh, const std::vector<char>& spikes, int adj=3);
	};

}


#endif