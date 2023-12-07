#ifndef CART3D_PARAPPEL_CORK_H
#define CART3D_PARAPPEL_CORK_H

#include <Cart3DParallelCorkDefine.h>
#include <Util/EigenUtil.h>
#include <Util/BoostUtil.h>
namespace Cart3D {

	//默认的最大组件
#define INVALID_COMP 0xffffui16 


	struct CART3D_PARALLEL_CORK_CLASS CorkConstant
	{
		static int quantization_bits;
		static int perturation_buffer_bits;
		static int fixed_integer_bits;
	};

	enum OpCode
	{
		undefine=0, //未定义任何属性
	};

	union HelperEdge {
		struct { std::uint32_t va, vb; };
		struct { std::uint64_t ab; };
	};
	CART3D_PARALLEL_CORK_API std::uint64_t make_edge(std::uint32_t a, std::uint32_t b);
	CART3D_PARALLEL_CORK_API std::uint64_t make_edge_sort(std::uint32_t a, std::uint32_t b);

	template<class T,int dim=6>
	class short_vector :public ct_vector<T>
	{
	public:
		short_vector() {
			reserve(dim);
		}
		std::uint32_t a;
	};

	struct CART3D_PARALLEL_CORK_CLASS TopoEdgePrototype
	{
		std::uint32_t vid;
		ct_vector<std::uint32_t> tris;
		TopoEdgePrototype();
		TopoEdgePrototype(std::uint32_t v);

		static TopoEdgePrototype& get_topo_ep(
			std::uint32_t a, std::uint32_t b,
			ct_vector< ct_vector<TopoEdgePrototype>>& prototypes);
	};
}


#endif