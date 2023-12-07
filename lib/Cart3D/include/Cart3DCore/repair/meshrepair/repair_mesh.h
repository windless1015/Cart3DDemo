#ifndef CART3D_REPAIR_REPAIRMESH_H
#define CART3D_REPAIR_REPAIRMESH_H

#include <Cart3DRepairDefine.h>
#include <csgmesh/CSGMesh.h>

namespace Cart3D
{

	class CART3D_REPAIR_CLASS RepairMesh
	{
		///////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////预处理算法////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////
	public:
		/*
		 * @brief mesh定点
		 * @detail
		 * @param[in]    mesh  待修复的mesh
		 * @param[out]  rmesh  粘合后的mesh
		 * @param[in]     bit  小数位数
		 * @return 是否修复成功
		 */
		static bool round_mesh_vertex(const CSGMesh& mesh, CSGMesh& rmesh, int bit);
	public:
		/*
		 * @brief 合并重复点
		 * @detail
		 * @param[in]   mesh 待处理的mesh
		 * @param[out] rmesh 处理后的mesh
		 * @param[in]      r 合并的阈值
		 * return 是否走到程序最后
		 */
		static bool repeat_mesh_vertex(const CSGMesh& mesh, CSGMesh& rmesh, cfloat r);
	public:
		/*
		 * @brief 将basemesh 转换为opentrimesh，注意这里自动将非流行边切割开
		 * @detail
		 * @param[in]  smesh 源mesh
		 * @param[out] dmesh 目mesh
		 * @return 是否转换成功
		 */
		static void swap_to_topo_mesh(CSGMesh& smesh, OpenTriMesh& dmesh);
		/*
		 * @brief 处理细小、狭长三角形
		 * @detail  遇到虚拟边界的则保持不动
		 * @param[in]    mesh
		 * @param[out]  smesh
		 */
		static bool glue_mesh(OpenTriMesh& mesh, cfloat r, bool& need_glue, int iter = 5);

		/*
		 * @brief 填充小孔
		 * @detail 实现原理参考"Filling Holes in Meshes" by Peter Liepa.
		 * @care!! 注意这里不会清理非流行点，因为这是网格修复，可以适当加三角形，但是删除三角形需要慎重
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
		 * @brief 转化为非流行mesh
		 * @detail
		 * @param[in]   smesh
		 * @param[out]  dmesh
		 * @return
		 */
		static bool swap_to_nonmanifold_mesh(OpenTriMesh& smesh, CSGMesh& dmesh);
		///////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////网格修复核心算法///////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////
	public:

	

		static bool remove_self_intersection(CSGMesh& mesh, int iter = 5);

	
	};


}


#endif