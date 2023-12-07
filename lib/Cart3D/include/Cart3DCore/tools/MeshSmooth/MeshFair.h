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
		 * @brief ���������������㷨
		 * @detial
		 * @param[in+out]  mesh ��������
		 * @param[in]       vhs ������������
		 * @param[in]        fc ��������������
		 * @return �Ƿ������ɹ�
		 */
		static bool fair(
			OpenTriMesh& mesh,
			const std::vector<VH>& vhs,
			unsigned int fc);
	public:
		/*
		 * @brief �������������������㷨
		 * @detial
		 * @param[in+out]  mesh ��������
		 * @param[in]       vhs ������������
		 * @param[in]        fc ��������������
		 * @return �Ƿ������ɹ�
		 */
		static bool fast_fair(
			OpenTriMesh& mesh,
			const std::vector<VH>& vhs,
			unsigned int fc);
	public:
		//ȫ�ֹ⻬
		static bool robust_fair(
			OpenTriMesh& mesh,
			const std::vector<VH>& vhs,
			unsigned int fc,
			cfloat wgt=5);
		//����������������ݷǳ����ʱ�����������
		static bool local_fair(
			OpenTriMesh& mesh,
			const std::vector<VH>& vhs,
			unsigned int fc);
	};

}

#endif