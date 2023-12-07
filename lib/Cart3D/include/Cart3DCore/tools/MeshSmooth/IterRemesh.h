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
		 * @brief ����remesh��Ŀ�곤��
		 * @param[in|out]       mesh ��remesh����������
		 * @param[in]     aim_length remesh��Ŀ�곤��
		 */
		static bool uniform_remesh(OpenTriMesh& mesh, cfloat aim_length);
		/*
		 * @brief ����remesh��Ŀ�곤��
		 * @param[in|out]       mesh ��remesh����������
		 * @param[in]     aim_length remesh��Ŀ�곤��
		 */
		static bool uniform_remesh(OpenTriMesh& mesh, cfloat aim_length,
			OpenMesh::VPropHandleT<int>& propes);

		static bool remesh(OpenTriMesh& mesh, cfloat aim_length);

		static bool remesh(OpenTriMesh& mesh, cfloat aim_length,
			OpenMesh::VPropHandleT<int>& propes);
	public:


	public:
		/*
		 * @brief �����߽���ϸ��
		 * @param[in|out]        mesh ��ϸ�ֵ�mesh
		 * @param[in]  sqr_max_length ��ϸ��mesh�����߳���ƽ��
		 */
		static bool split_long_edges(
			OpenTriMesh& mesh, cfloat sqr_max_length,
			OpenMesh::VPropHandleT<int>& propes, int iter = 100);
		/*
		 * @brief ���̱߽����۵�
		 * @param[in|out]          mesh ���۵���mesh
		 * @param[in]  sqr_short_length ���۵�mesh�����䳤��ƽ��
		 */
		static bool collapse_short_edges(
			OpenTriMesh& mesh, cfloat sqr_short_length, cfloat sqr_max_length,
			OpenMesh::VPropHandleT<int>& propes, int iter = 100);
		/*
		 * @brief ���͵�Ķ���
		 * @param[in|out]          mesh ���۵���mesh
		 */
		static bool releax_edges(OpenTriMesh& mesh, int iter = 100);
	public:
		static bool collapse_flips_normal(OpenTriMesh& mesh, const HH& heh);
		static bool is_flip_edge(const OpenTriMesh& mesh, const EH& eh);
	};
}

#endif