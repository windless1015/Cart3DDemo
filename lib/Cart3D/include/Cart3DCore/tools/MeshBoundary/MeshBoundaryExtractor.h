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
		 * @brief    根据半边提取边界圈
		 * @detail
		 * @param[in]      mesh 待提取的mesh
		 * @param[in]        hh 半边
		 * @param[out] boundary 边界
		 */
		static bool extra_bounary(const OpenTriMesh& mesh, const HH& hh, std::vector<VH>& boundary);
		/*
		 * @brief    根据半边提取边界圈
		 * @detail
		 * @param[in]      mesh 待提取的mesh
		 * @param[in]        hh 半边
		 * @param[out] boundary 边界
		 */
		static bool extra_bounary(const OpenTriMesh& mesh, const HH& hh, std::vector<HH>& boundary);
		/*
		 * @brief    提取所有边界圈
		 * @detail
		 * @param[in]      mesh 待提取的mesh
		 * @param[out] boundary 边界
		 */
		static bool extra_all_bounary(const OpenTriMesh& mesh, std::vector<HH>& bounary);
		static bool extra_all_bounary(const OpenTriMesh& mesh, std::vector<std::vector<VH>>& bounary);

		/*
		 * @brief    提取最大边界圈
		 * @detail
		 * @param[in]      mesh 待提取的mesh
		 * @param[out]       hh 最大边界圈
		 */
		static bool extra_max_bounary(const OpenTriMesh& mesh, HH& hh);

		static HH get_next_boundary(const OpenTriMesh& mesh, const HH& hh);
	public:
		static bool extra_all_holes(const OpenTriMesh& omesh, std::vector<std::vector<HH>>& hhs);

	};
}



#endif