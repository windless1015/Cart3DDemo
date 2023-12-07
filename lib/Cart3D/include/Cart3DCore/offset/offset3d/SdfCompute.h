#ifndef CART3D_SDF_COMPUTE_H
#define CART3D_SDF_COMPUTE_H

#include <Cart3DOffsetDefine.h>
#include <Util/EigenUtil.h>
#include <offset3d/SdfUtil.h>

namespace Cart3D
{
	
	class CART3D_OFFSET_CLASS SdfCompute
	{
	public:
		static void compute_sdf(
			//背景网格
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//网格场
			const Grid& sgrid,
			//距离场
			cfloat* sdf,
			std::vector<int>* close_tris = nullptr,
			cfloat far_dist = DBL_MAX);
		static void compute_usdf(
			//背景网格
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//网格场
			const Grid& sgrid,
			//距离场
			cfloat* sdf,
			std::vector<int>* close_tris = nullptr,
			cfloat far_dist = DBL_MAX);
		static void compute_undercut(
			//背景网格
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//网格场
			const Grid& sgrid,
			//距离场
			cfloat* sdf,
			std::vector<int>* close_tris = nullptr,
			cfloat far_dist = DBL_MAX);
		static void compute_undercut(
			//背景网格
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//网格场
			const Grid& sgrid,
			//距离场
			cfloat* sdf,
			SdfInfo& sdfinfo);
		static void update_undercut(const Grid& sgrid, cfloat* sdf, SdfInfo& sdfinfo);
		static void compute_boundary_undercut(
			//背景网格
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//网格场
			const Grid& sgrid,
			//距离场
			cfloat* sdf,
			SdfInfo& sdfinfo);
		static void update_boundary_undercut(const Grid& sgrid, cfloat* sdf, SdfInfo& sdfinfo);
	public:
		//这里可以定义各种滤波器
		static void smooth_sdf(const Grid& sgrid, cfloat* sdf,cfloat far_dist,int iter=3);

	private:
		static void compute_sdf_core(
			//背景网格
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//网格场
			const Grid& sgrid,
			//距离场
			cfloat* sdf,
			std::vector<int>& close_tris,
			//距离场信息
			std::vector<short>* intersection=nullptr,
			cfloat far_dist = DBL_MAX);

		//采用fmm计算远场
		static void geodesic_sdf(
			//背景网格
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//网格场
			const Grid& sgrid,
			//距离场
			cfloat* sdf, std::vector<int>& close_tris,
			cfloat far_dist);
		//计算整个场
		//static void fast_sweeping_sdf(
		//	//背景网格
		//	const std::vector<cvector3d>& mesh_verts,
		//	const std::vector<int>& mesh_face,
		//	//网格场
		//	const Grid& sgrid,
		//	//距离场
		//	cfloat* sdf, std::vector<int>& close_tris,
		//	cfloat far_dist);
	public:

	};



}


#endif