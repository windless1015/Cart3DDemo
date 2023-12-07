#pragma once
#ifndef CART3D_MESH_BOUNDARY_EXTRACTOR_H
#define CART3D_MESH_BOUNDARY_EXTRACTOR_H

#include <Cart3DToolsDefine.h>
#include "Util/OpenMeshUtil.h"

namespace Cart3D
{
	class CART3D_TOOLS_CLASS MeshBoundaryExtractor
	{
	public:
		/*
		 * @brief    ���ݰ����ȡ�߽�Ȧ
		 * @detail
		 * @param[in]      mesh ����ȡ��mesh
		 * @param[in]        hh ���
		 * @param[out] boundary �߽�
		 */
		static bool extra_bounary(const OpenTriMesh& mesh, const HH& hh, std::vector<VH>& boundary);
		/*
		 * @brief    ���ݰ����ȡ�߽�Ȧ
		 * @detail
		 * @param[in]      mesh ����ȡ��mesh
		 * @param[in]        hh ���
		 * @param[out] boundary �߽�
		 */
		static bool extra_bounary(const OpenTriMesh& mesh, const HH& hh, std::vector<HH>& boundary);
		/*
		 * @brief    ��ȡ���б߽�Ȧ
		 * @detail
		 * @param[in]      mesh ����ȡ��mesh
		 * @param[out] boundary �߽�
		 */
		static bool extra_all_bounary(const OpenTriMesh& mesh, std::vector<HH>& bounary);
		static bool extra_all_bounary(const OpenTriMesh& mesh, std::vector<std::vector<VH>>& bounary);

		/*
		 * @brief    ��ȡ���߽�Ȧ
		 * @detail
		 * @param[in]      mesh ����ȡ��mesh
		 * @param[out]       hh ���߽�Ȧ
		 */
		static bool extra_max_bounary(const OpenTriMesh& mesh, HH& hh);

		static HH get_next_boundary(const OpenTriMesh& mesh, const HH& hh);
	public:
		static bool extra_all_holes(const OpenTriMesh& omesh, std::vector<std::vector<HH>>& hhs);

	};
}



#endif