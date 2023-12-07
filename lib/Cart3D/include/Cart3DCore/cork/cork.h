
#pragma once

#include "Cart3DCorkDefine.h"
#include <csgmesh/CSGMesh.h>
//这里设置是否启用调试模式
#define debug_io 1
//这里设置debug文件名
#define debug_io_filename "d:/cart3d_cork.ply"
namespace Cart3D
{

	//这里对输入的网格没有做过多限制，目前支持非流形、流行等网格
	enum DoubleFaceCode { DOUBLEFACE_KEEP_ALL = 0, DOUBLEFACE_KEEP_ONE = 1, DOUBLEFACE_DELETE_ALL = 2, DOUBLEFACE_AUTO_DELETE = 3 };

	struct CART3D_CORK_CLASS BooleConstanct
	{
	public:
		//设置浮点数有效位数，一般float为5位，double为10位，但是考虑输入输出的影响，这里建议值为5--8
		static void set_numpoint(int fix_num = 6);
		static void set_cop(int fix_num = 4);
		static int cur_number();
		static int cop_number();
	private:
		static int fix_number;
		static int scop_number;

	};
	CART3D_CORK_API bool is_solid(const BaseTriMesh &in0);

	struct CART3D_CORK_CLASS BooleanMesh
	{
		std::pair<bool,BaseTriMesh> union_mesh;
		std::pair<bool,BaseTriMesh> differ_mesh;
		std::pair<bool,BaseTriMesh> inter_mesh;
		std::pair<bool,BaseTriMesh> outer_one_mesh;
		std::pair<bool,BaseTriMesh> inner_one_mesh;
		std::pair<bool,BaseTriMesh> outer_two_mesh;
		std::pair<bool,BaseTriMesh> inner_two_mesh;

		BooleanMesh();
		void set_op(bool un, bool dif, bool inter, 
			bool outerone=false, bool innnerone=false,
			bool outertwo=false, bool innertwo=false);
		void set_all(bool res);
	};
	//浮点数共面纠正
	CART3D_CORK_API void coplanar_correction(
		BaseTriMesh& in0, BaseTriMesh& in1,
		bool fix0 = false, bool fix1 = false);
	
	CART3D_CORK_API void compute_op(
		const BaseTriMesh &in0, const BaseTriMesh &in1, BooleanMesh& resm, bool isSelf = false);
	CART3D_CORK_API void compute_union(const BaseTriMesh &in0, const BaseTriMesh &in1, BaseTriMesh &out, bool isSelf = false);
	CART3D_CORK_API void compute_outer_one(const BaseTriMesh &in0, const BaseTriMesh &in1, BaseTriMesh &out, bool isSelf = false);
	CART3D_CORK_API void compute_outer_two(const BaseTriMesh &in0, const BaseTriMesh &in1, BaseTriMesh &out, bool isSelf = false);
	CART3D_CORK_API void compute_intersection(const BaseTriMesh& in0, const BaseTriMesh& in1, BaseTriMesh& out, bool isSelf = false);
	CART3D_CORK_API void compute_inner_one(const BaseTriMesh& in0, const BaseTriMesh& in1, BaseTriMesh& out, bool isSelf = false);
	CART3D_CORK_API void compute_inner_two(const BaseTriMesh& in0, const BaseTriMesh& in1, BaseTriMesh& out, bool isSelf = false);
	CART3D_CORK_API void compute_difference(const BaseTriMesh &in0, const BaseTriMesh &in1, BaseTriMesh &out, bool isSelf = false);
	CART3D_CORK_API void compute_xor(const BaseTriMesh &in0, const BaseTriMesh &in1, BaseTriMesh &out, bool isSelf = false);
	CART3D_CORK_API void resolve_intersections(const BaseTriMesh &in0, const BaseTriMesh &in1, BaseTriMesh &out);
	CART3D_CORK_API bool resolve_self_intersection(const BaseTriMesh &in, BaseTriMesh &out, DoubleFaceCode classify);
	CART3D_CORK_API bool resolve_self_intersection(const BaseTriMesh &in, BaseTriMesh &out, std::vector<int> &oriVmap, DoubleFaceCode classify);
	CART3D_CORK_API void glue_mesh(const BaseTriMesh &in, const double &clearance, BaseTriMesh &out);
}