#ifndef CART3D_MESH_CURVE_H
#define CART3D_MESH_CURVE_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>
#include <MeshCurve/CurveFwd.h>
namespace Cart3D
{
	

	class CART3D_TOOLS_CLASS MeshSmoothCurve
	{
	public:
		/*
		 * @brief 光顺测地线
		 * @detail 该接口支持多种模式，原理是寻找到初始的测地线，然后进行迭代光顺
		 * @param[in]        mesh 背景网格
		 * @param[in]      vhPath 初始采样点
		 * @param[out]   geodesic 处理后的测地线
		 * @param[in]    locknode 是否锁住输入的节点
		 * @param[in]     isclose 是否对测地线进行首尾连接
		 * @param[in] smooth_iter 曲线迭代光顺最大步数
		 */
		static bool smooth_geodesic(const OpenTriMesh& mesh,
			const std::vector<VH>& vhs,
			std::vector<SurfPt>& geodesic,
			bool locknode = false, 
			bool isclose = false, 
			int smooth_iter = 5);

		static bool smooth_geodesic(
			const OpenTriMesh& mesh,
			std::vector<SurfPt>& geodesic,
			int smooth_iter = 5,
			bool is_close=false);
	public:

		static bool smooth_geodeisc(
			const OpenTriMesh& mesh,
			std::shared_ptr<fcpw::Scene<3>>& ptree,
			const cvector3d& start,
			const cvector3d& end,
			std::vector<SurfPt>& geodesic, int smooth_iter = 5);
	private:
		static bool dijk_path(const OpenTriMesh& mesh,
			const VH& vs,
			const VH& ve,
			std::vector<VH>& path);

		static bool dijk_path(const OpenTriMesh& mesh,
			const SurfPt& vs,
			const SurfPt& ve,
			std::vector<SurfPt>& path);
	private:
		static bool update_edge_point(const OpenTriMesh& mesh,
			const SurfPt& prev, const SurfPt& cur,
			const SurfPt& next, SurfPt& result);
		static bool update_vertex_point(
			const OpenTriMesh& mesh,
			const SurfPt& prev,
			const SurfPt& cur,
			const SurfPt& next,
			std::vector<SurfPt>& results);
	};


}




#endif