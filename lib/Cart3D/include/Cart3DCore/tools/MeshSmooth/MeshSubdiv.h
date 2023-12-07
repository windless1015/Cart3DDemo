#ifndef CART3D_MESHSUBDIV_H
#define CART3D_MESHSUBDIV_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D
{
	enum  SubdivType {
		SUBDIV_PLANAR,
		SUBDIV_LOOP,
		SUBDIV_LOOP_ORIG,
		SUBDIV_LOOP_NEW,
		SUBDIV_BUTTERFLY,
		SUBDIV_BUTTERFLY_MODIFIED
	};
	class CART3D_TOOLS_CLASS MeshSubdiv
	{
	public:
		/*
		 * @brief ����sqrt(3)����ϸ��mesh
		 * @param[in|out]  mesh ��ϸ��mesh
		 * @param[in]      iter ϸ�ֵ�������
		 */
		static bool subdiv_sqrt3(OpenTriMesh& mesh, int iter);
	
		/*
		 * @brief ��Ӹ��������ϸ���㷨
		 * @detail ����ϸ���㷨
		 * @param[in|out] pts,tris meshϸ���㷨�������
		 * @param[in] numsub ϸ�ֵ�������
		 * @param[in] type ϸ�ַ�ʽ
		 */
		static void subdiv_mesh(
			std::vector<cvector3d>& pts,std::vector<int>& tris,
			int numsub, SubdivType type = SUBDIV_LOOP);
	};
}



#endif