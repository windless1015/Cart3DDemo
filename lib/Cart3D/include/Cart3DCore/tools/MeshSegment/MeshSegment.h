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
		 * @brief �Ż����ָ������ӵ� 
		 * @param[in]    mesh �����������
		 * @param[in] weights �ָ
		 * @param[in]  vhseed �ָ����ӵ�
		 * @param[out]   seed �Ż�������ӵ�
		 * return �Ƿ��Ż��ɹ�
		 */
		static bool optim_max_flow_seed(
			const OpenTriMesh& mesh,
			const std::vector<cfloat>& weights,
			const VH& vhseed,
			VH& seed);
		/* 
		 * @brief ������ָ��㷨��������õ�һ�������ʻ��߲�ؾ���ȵ�
		 * @param[in]     mesh ���ָ��mesh
		 * @param[in]    seeds �ָ�����ӵ�
		 * @param[in]  weights �ָȨ��
		 * @param[out]  labels �ָ���
		 * @return �Ƿ�ָ�ɹ�
		 */
		static bool max_flow_graph_cut(
			const OpenTriMesh& mesh,
			const fast_map<int,tree_set<VH>>& seeds,
			const std::vector<cfloat>& weights,
			std::vector<int>& labels,
			const SegParam& param=SegParam());
	public:
		/*
		 * @brief �Ż���С�ָ������ӵ�
		 * @param[in]    mesh �����������
		 * @param[in] weights �ָ
		 * @param[in]  vhseed �ָ����ӵ�
		 * @param[out]   seed �Ż�������ӵ�
		 * return �Ƿ��Ż��ɹ�
		 */
		static bool optim_min_flow_seed(
			const OpenTriMesh& mesh,
			const std::vector<cfloat>& weights,
			const VH& vhseed,
			VH& seed);

		/*
		 * @brief ��С���ָ��㷨��������õ�һ�������ʻ��߲�ؾ���ȵ�
		 * @param[in]     mesh ���ָ��mesh
		 * @param[in]    seeds �ָ�����ӵ�
		 * @param[in]  weights �ָȨ��
		 * @param[out]  labels �ָ���
		 * @return �Ƿ�ָ�ɹ�
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