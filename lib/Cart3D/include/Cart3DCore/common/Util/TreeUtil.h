#ifndef CART3D_TREE_UTIL_H
#define CART3D_TREE_UTIL_H

#include <mimalloc/include/mimalloc.h>


#if defined(_MSC_FULL_VER) && _MSC_FULL_VER < 190023918 && !defined(__clang__)
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
namespace Cart3D
{
	template<class key, class T>
	using fast_map = std::unordered_map<key, T, std::hash<key>, std::equal_to<key>, mi_stl_allocator<std::pair<const key, T>>>;

	template<class key, class T, class Hash, class Eq>
	using myfast_map = std::unordered_map<key, T, Hash,Eq, mi_stl_allocator<std::pair<const key, T>>>;

	template<class key>
	using fast_set = std::unordered_set<key>;

	template<class T, class Hash>
	using myfast_set = std::unordered_set<T, Hash>;

	template<class key, class T>
	using tree_map = std::map<key, T>;

	template<class key, class T>
	using tree_mmap = std::muiltmap<key, T>;

	template<class key>
	using tree_set = std::set<key>;

	template<class key>
	using tree_mset = std::muiltset<key>;
}
#else
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:26495)
#endif
#include "parallel_hashmap/phmap.h"
#include "parallel_hashmap/btree.h"
#include "parallel_hashmap/phmap_config.h"

namespace Cart3D
{

	template<class key>
	using fast_set = phmap::flat_hash_set<key, std::hash<key>, std::equal_to<key>, mi_stl_allocator<key>>;
	template<class T, class Hash, class Eq>
	using myfast_set = phmap::flat_hash_set<T, Hash, Eq, mi_stl_allocator<T> >;

	template<class key, class T>
	using fast_map = phmap::flat_hash_map<key, T,std::hash<key>,std::equal_to<key>, mi_stl_allocator<std::pair<const key, T>>>;
	template<class key, class T, class Hash, class Eq>
	using myfast_map = phmap::flat_hash_map<key, T, Hash,Eq, mi_stl_allocator<std::pair<const key, T>>>;

	template<class key>
	using tree_set = phmap::btree_set<key, std::less<key>, mi_stl_allocator<key>>;
	template<class key, class T>
	using tree_map = phmap::btree_map<key, T, std::less<key>, mi_stl_allocator<std::pair<const key, T>>>;

	template<class key, class T>
	using tree_mmap = phmap::btree_multimap<key, T>;


	template<class key>
	using tree_mset = phmap::btree_multiset<key>;



	

}
#endif

#if defined(_MSC_VER)
#pragma warning(pop)
#endif



#endif // CART3D_TREE_UTIL_H
