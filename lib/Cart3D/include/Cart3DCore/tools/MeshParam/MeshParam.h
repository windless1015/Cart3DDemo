#ifndef CART3D_TOOLS_MESHPARAM_H
#define CART3D_TOOLS_MESHPARAM_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D {

	class CART3D_TOOLS_CLASS MeshParam
	{
	public:
		
		//static bool harmonic_parameterization(const OpenTriMesh& mesh);
	public:

		/*
		 * @brief 圆盘参数化网格
		 * @detail 圆盘参数化，其中要求输入的网格是单连通的，有边界
		 * @param[in]   mesh 待参数化的网格
		 * @param[out] loops 固定边界
		 * @param[out]  texs 参数化结果
		 */
		static bool mesh_to_disk(const OpenTriMesh& mesh,
			std::vector<VH>& loops,
			std::vector<cvector2d>& texs);
		/*
		 * @brief 圆盘参数化网格
		 * @detail 圆盘参数化，其中要求输入的网格是单连通的，有边界
		 * @param[in]     mesh 待参数化的网格
		 * @param[out]   loops 固定边界
		 * @param[out] rangles 角度
		 * @param[out]    texs 参数化结果
		 */
		static bool mesh_to_disk(const OpenTriMesh& mesh,
			std::vector<VH>& loops,
			std::vector<cfloat>& rangles,
			std::vector<cvector2d>& texs);
		/*
		 * @brief 圆盘参数化网格
		 * @detail 圆盘参数化，其中要求输入的网格是单连通的，有边界
		 * @param[in]     mesh 待参数化的网格
		 * @param[in]     cent 参数化圆盘中心
		 * @param[in]        r 参数化圆盘半径
		 * @param[out]   loops 固定边界
		 * @param[out] rangles 角度
		 * @param[out]    texs 参数化结果
		 */
		static bool mesh_to_disk(const OpenTriMesh& mesh,
			const cvector2d& cent, cfloat r,
			std::vector<VH>& loops,
			std::vector<cfloat>& rangles,
			std::vector<cvector2d>& texs);

		

		/*
		 * @brief 限定圆盘参数化，这里是为了解决分割对其问题
		 * @detail 圆盘参数化，其中要求输入的网格是单连通的，有边界
		 * @param[in]   mesh 待参数化的网格
		 * @param[in]  loops 固定边界
		 * @param[in]   ctex 边界参数化结果
		 * @param[out]  texs 参数化结果
		 */
		static bool constrin_mesh_to_disk(
			const OpenTriMesh& mesh,
			const std::vector<VH>& loops,
			const std::vector<cvector2d>& ctex,
			std::vector<cvector2d>& texs);

	public:
		//将亏格为0 的mesh进行切割成两个圆盘
		static bool cut_mesh(const OpenTriMesh& mesh, const cvector3d& zdir,
			std::vector<int>& fids);
		//寻找切割路劲,注意外部不要轻易调用此接口
		static bool cut_mesh(
			const OpenTriMesh& mesh,
			const std::vector<int>& fids,
			OpenTriMesh& mesh0, std::vector<VH>& vhs0,
			OpenTriMesh& mesh1, std::vector<VH>& vhs1,
			std::vector<VH>& path);
	public:
		/*
		 * @brief 将亏格为0的网格映射为一个球
		 * @detail 这将严重受到分割线干扰，很容易产生严重畸变
		 * @param[in]  mesh 亏格为0的球，注意这里需要外部判断，内部不做检测
		 * @param[in]  zdir 参数化方向，这里定义了球的极坐标系方向
		 * @param[out] texs 球面参数化坐标
		 * @return 是否参数化成功
		 */
		static bool mesh_to_sphere(
			const OpenTriMesh& mesh,
			const cvector3d& zdir,
			std::vector<cvector3d>& texs);
	public:
		//注意这里为了防止映射发生过渡畸变，采用弧长的方式进行映射
		static bool disk_to_halfsphere(cfloat zdir,
			const cvector2d&ccent, cfloat r0,
			const cvector3d&scent, cfloat r,
			const std::vector<cvector2d>&circle,
			std::vector<cvector3d>& sphere);

	};

}

#endif