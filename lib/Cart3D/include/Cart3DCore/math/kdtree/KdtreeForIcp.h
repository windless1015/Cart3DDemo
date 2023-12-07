#pragma once
#ifndef CART3D_ICP_KDTREE_H
#define CART3D_ICP_KDTREE_H

#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{
	class CART3D_MATH_CLASS KdtreeForIcp
	{
	public:
		struct CompatFunc
		{
			virtual bool operator () (const cfloat* p) const = 0;
			virtual ~CompatFunc() {}
		};
	public:
		KdtreeForIcp(const cfloat* ptlist, size_t n);
		KdtreeForIcp(const cfloat** pts, size_t n);
		~KdtreeForIcp();
	public:
		template <class T> 
		KdtreeForIcp(const std::vector<T>& v) : 
			p_root(nullptr), p_storage(nullptr)
		{
			build((const cfloat*)&v[0], v.size());
		}
		template <class T> 
		KdtreeForIcp(std::vector<T*>& pts) : 
			p_root(nullptr), p_storage(nullptr)
		{
			build((const cfloat**)&pts[0], pts.size());
		}
	public:
		const cfloat* closest_to_pt(
			const cfloat* p,
			cfloat maxdist2 = 0.0,
			const CompatFunc* iscompat = nullptr,
			cfloat approx_eps = 0.0) const;
		const cfloat* closest_to_pt(
			const cfloat* p,
			cfloat maxdist2,
			cfloat approx_eps) const;
		const cfloat* closest_to_ray(const cfloat* p, const cfloat* dir,
			cfloat maxdist2 = 0.0,
			const CompatFunc* iscompat = nullptr,
			cfloat approx_eps = 0.0) const;
		const cfloat* closest_to_ray(
			const cfloat* p, const cfloat* dir,
			cfloat maxdist2,
			cfloat approx_eps) const;
		void find_k_closest_to_pt(::std::vector<const cfloat*>& knn,
			int k,const cfloat* p,
			cfloat maxdist2 = 0.0,
			const CompatFunc* iscompat = nullptr,
			cfloat approx_eps = 0.0) const;
		void find_k_closest_to_pt(::std::vector<const cfloat*>& knn,
			int k,const cfloat* p,
			cfloat maxdist2,cfloat approx_eps) const;
		bool exists_pt_within(const cfloat* p, cfloat maxdist) const;
	private:
		struct Node;
		struct NodeStorageBlock;
		void build(const cfloat* ptlist, size_t n);
		void build(const cfloat** pts, size_t n);
	private:
		Node* p_root;
		NodeStorageBlock* p_storage;
	};


}

#endif