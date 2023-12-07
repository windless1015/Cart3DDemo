#ifndef CART3D_ITER_REMESH_H
#define CART3D_ITER_REMESH_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>

namespace Cart3D
{

	class CART3D_TOOLS_CLASS IterRemesh
	{
	public:
		/*
		 * @brief 均匀remesh至目标长度
		 * @param[in|out]       mesh 待remesh的牙齿数据
		 * @param[in]     aim_length remesh的目标长度
		 */
		static bool uniform_remesh(OpenTriMesh& mesh, cfloat aim_length);
		/*
		 * @brief 均匀remesh至目标长度
		 * @param[in|out]       mesh 待remesh的牙齿数据
		 * @param[in]     aim_length remesh的目标长度
		 */
		static bool uniform_remesh(OpenTriMesh& mesh, cfloat aim_length,
			OpenMesh::VPropHandleT<int>& propes);

		static bool remesh(OpenTriMesh& mesh, cfloat aim_length);

		static bool remesh(OpenTriMesh& mesh, cfloat aim_length,
			OpenMesh::VPropHandleT<int>& propes);
	public:


	public:
		/*
		 * @brief 将长边进行细分
		 * @param[in|out]        mesh 待细分的mesh
		 * @param[in]  sqr_max_length 待细分mesh的最大边长的平方
		 */
		static bool split_long_edges(
			OpenTriMesh& mesh, cfloat sqr_max_length,
			OpenMesh::VPropHandleT<int>& propes, int iter = 100);
		/*
		 * @brief 将短边进行折叠
		 * @param[in|out]          mesh 待折叠的mesh
		 * @param[in]  sqr_short_length 待折叠mesh的最大变长的平方
		 */
		static bool collapse_short_edges(
			OpenTriMesh& mesh, cfloat sqr_short_length, cfloat sqr_max_length,
			OpenMesh::VPropHandleT<int>& propes, int iter = 100);
		/*
		 * @brief 降低点的度数
		 * @param[in|out]          mesh 待折叠的mesh
		 */
		static bool releax_edges(OpenTriMesh& mesh, int iter = 100);
	public:
		static bool collapse_flips_normal(OpenTriMesh& mesh, const HH& heh);
		static bool is_flip_edge(const OpenTriMesh& mesh, const EH& eh);
	};
}

#endif