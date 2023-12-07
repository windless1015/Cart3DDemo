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
		 * @brief ����mesh ��̵�
		 * @param[in]                 mesh �������mesh
		 * @param[in]  max_gauss_variation �������ֵ
		 * @param[out]              spikes ����������
		 * @return �Ƿ����ɹ�
		 */
		static bool compute_spikes(const OpenTriMesh& mesh, cfloat max_gauss_variation, std::vector<char>& spikes);
		/*
		 * @brief ȥ��mesh���
		 * @param[in]       mesh �������mesh
		 * @param[in]       spikes ����������
		 * @return �Ƿ����ɹ�
		 */
		static bool remove_spikes(OpenTriMesh& mesh, const std::vector<char>& spikes, int adj=3);
	};

}


#endif