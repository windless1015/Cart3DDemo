#ifndef CART3D_BOOST_UTIL_H
#define CART3D_BOOST_UTIL_H

#include <Cart3DCommonDefine.h>
#include <vector>
#include <mimalloc/include/mimalloc.h>

namespace Cart3D
{
	template<class T>
	using ct_vector = std::vector<T, mi_stl_allocator<T>>;



}

#endif