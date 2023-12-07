
#pragma once

#include "Cart3DCorkDefine.h"
#include <csgmesh/CSGMesh.h>
//���������Ƿ����õ���ģʽ
#define debug_io 1
//��������debug�ļ���
#define debug_io_filename "d:/cart3d_cork.ply"
namespace Cart3D
{

	//��������������û�����������ƣ�Ŀǰ֧�ַ����Ρ����е�����
	enum DoubleFaceCode { DOUBLEFACE_KEEP_ALL = 0, DOUBLEFACE_KEEP_ONE = 1, DOUBLEFACE_DELETE_ALL = 2, DOUBLEFACE_AUTO_DELETE = 3 };

	struct CART3D_CORK_CLASS BooleConstanct
	{
	public:
		//���ø�������Чλ����һ��floatΪ5λ��doubleΪ10λ�����ǿ������������Ӱ�죬���ｨ��ֵΪ5--8
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
	//�������������
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