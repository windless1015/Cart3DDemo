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
		 * @brief 采用sqrt(3)方法细分mesh
		 * @param[in|out]  mesh 待细分mesh
		 * @param[in]      iter 细分迭代次数
		 */
		static bool subdiv_sqrt3(OpenTriMesh& mesh, int iter);
	
		/*
		 * @brief 添加更多的网格细分算法
		 * @detail 网格细分算法
		 * @param[in|out] pts,tris mesh细分算法输入输出
		 * @param[in] numsub 细分迭代次数
		 * @param[in] type 细分方式
		 */
		static void subdiv_mesh(
			std::vector<cvector3d>& pts,std::vector<int>& tris,
			int numsub, SubdivType type = SUBDIV_LOOP);
	};
}



#endif