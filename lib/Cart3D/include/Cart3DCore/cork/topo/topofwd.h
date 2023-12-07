#pragma once
#include  <vector>
#include  <mimalloc/include/mimalloc.h>
struct TopoVert;
struct TopoEdge;
struct TopoTri;

typedef TopoVert* Vptr;
typedef TopoEdge* Eptr;
typedef TopoTri*  Tptr;


template<class T>
using cork_vector=std::vector<T, mi_stl_allocator<T>>;

template<class T>
void erase(cork_vector<T>& vec, const T& t) {
	for (auto iter = vec.begin(); iter != vec.end();) {
		if (*iter == t) {
			iter = vec.erase(iter);
		}
		else {
			++iter;
		}
	}
}