#ifndef CART3D_REPAIR_REPAIRMESH_H
#define CART3D_REPAIR_REPAIRMESH_H

#include <Cart3DRepairDefine.h>
#include <csgmesh/CSGMesh.h>

namespace Cart3D
{

	class CART3D_REPAIR_CLASS RepairMesh
	{
		///////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////Ԥ�����㷨////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////
	public:
		/*
		 * @brief mesh����
		 * @detail
		 * @param[in]    mesh  ���޸���mesh
		 * @param[out]  rmesh  ճ�Ϻ��mesh
		 * @param[in]     bit  С��λ��
		 * @return �Ƿ��޸��ɹ�
		 */
		static bool round_mesh_vertex(const CSGMesh& mesh, CSGMesh& rmesh, int bit);
	public:
		/*
		 * @brief �ϲ��ظ���
		 * @detail
		 * @param[in]   mesh �������mesh
		 * @param[out] rmesh ������mesh
		 * @param[in]      r �ϲ�����ֵ
		 * return �Ƿ��ߵ��������
		 */
		static bool repeat_mesh_vertex(const CSGMesh& mesh, CSGMesh& rmesh, cfloat r);
	public:
		/*
		 * @brief ��basemesh ת��Ϊopentrimesh��ע�������Զ��������б��и
		 * @detail
		 * @param[in]  smesh Դmesh
		 * @param[out] dmesh Ŀmesh
		 * @return �Ƿ�ת���ɹ�
		 */
		static void swap_to_topo_mesh(CSGMesh& smesh, OpenTriMesh& dmesh);
		/*
		 * @brief ����ϸС������������
		 * @detail  ��������߽���򱣳ֲ���
		 * @param[in]    mesh
		 * @param[out]  smesh
		 */
		static bool glue_mesh(OpenTriMesh& mesh, cfloat r, bool& need_glue, int iter = 5);

		/*
		 * @brief ���С��
		 * @detail ʵ��ԭ��ο�"Filling Holes in Meshes" by Peter Liepa.
		 * @care!! ע�����ﲻ����������е㣬��Ϊ���������޸��������ʵ��������Σ�����ɾ����������Ҫ����
		 * @param[in]   mesh
		 * @param[out]  dmesh
		 * @return
		 */
		enum  FillHoleStyle
		{
			MinArea, MaxAngleMinArea, MaxAngle
		};
		static int fill_hole_mesh(OpenTriMesh& mesh, FillHoleStyle fhs = MaxAngleMinArea,
			bool smooth = false, int max_hole_vhs = 850, bool jamp_nonmanifold = false);

		/*
		 * @brief ת��Ϊ������mesh
		 * @detail
		 * @param[in]   smesh
		 * @param[out]  dmesh
		 * @return
		 */
		static bool swap_to_nonmanifold_mesh(OpenTriMesh& smesh, CSGMesh& dmesh);
		///////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////�����޸������㷨///////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////
	public:

	

		static bool remove_self_intersection(CSGMesh& mesh, int iter = 5);

	
	};


}


#endif