#pragma once
#ifndef CART3D_POINT_CLOUT_UTIL_H
#define CART3D_POINT_CLOUT_UTIL_H
#include "Cart3DSlamDefine.h"
#include "Util/OpenMeshUtil.h"
namespace Cart3D
{
	struct CART3D_SLAM_CLASS PointField
	{
		std::vector<cvector3d> pts;
		std::vector<cvector3d> pns;
		cvector3d rcenter;
		cfloat radius;

		inline size_t kdtree_get_point_count() const { return pts.size(); }
		inline cfloat kdtree_get_pt(const size_t idx, const size_t dim) const {
			return pts[idx][dim];
		}
		template <class BBOX> bool kdtree_get_bbox(BBOX& /* bb */) const {
			return false;
		}

	};

	class CART3D_SLAM_CLASS PointCloudUtil
	{
	public:
	    /*
		 * @brief 预处理原始mesh,
		 * @param[in]    mesh 原始mesh
		 * @param[out] pfield 配准场
		 * return 是否预处理成功
		 */
		static void swap_mesh(const OpenTriMesh& mesh, PointField& tmesh);
		static void check_mesh(const OpenTriMesh& mesh, OpenTriMesh& out_mesh);
	};
}


#endif