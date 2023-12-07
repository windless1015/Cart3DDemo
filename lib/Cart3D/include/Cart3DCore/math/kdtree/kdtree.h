#ifndef CART3D_ALGORITHM_KDTREE_H
#define CART3D_ALGORITHM_KDTREE_H

#include <memory>
#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>
namespace Cart3D
{
	class CART3D_MATH_CLASS kdtree
	{
	public:
		struct Cache;
	public:
		kdtree(const std::vector<cvector3d>& pts);
		kdtree(const cvector3d* pts,int nvert);
	public:
		void update_tree();
	public:
		size_t kdtree_get_point_count() const;
		cfloat kdtree_get_pt(const size_t idx, const size_t dim) const;
		template <class BBOX>
		bool kdtree_get_bbox(BBOX&) const{
			return false;
		}
	public:
		size_t knn_search(
			const cvector3d& point, size_t num_closest, 
			std::vector<size_t>& k_indices,
			std::vector<cfloat>& k_squared_distances,bool sort=true)const;
		size_t sqr_radius_search(const cvector3d& point, cfloat radius,
			std::vector<size_t>& k_indices,bool sort=true)const;
	public:
		std::pair<size_t,cfloat> knn_search(const cvector3d& point)const;
	protected:
		const cvector3d* pts;
		int nverts;
		std::shared_ptr<Cache> pTree;
	};


	class CART3D_MATH_CLASS kdtree2d
	{
	public:
		struct Cache;
	public:
		kdtree2d(const std::vector<cvector2d>& pts);
	public:
		void update_tree();
	public:
		size_t kdtree_get_point_count() const;
		cfloat kdtree_get_pt(const size_t idx, const size_t dim) const;
		template <class BBOX>
		bool kdtree_get_bbox(BBOX&) const {
			return false;
		}
	public:
		size_t knn_search(
			const cvector2d& point, size_t num_closest,
			std::vector<size_t>& k_indices,
			std::vector<cfloat>& k_squared_distances, bool sort = true)const;
		size_t sqr_radius_search(const cvector2d& point, cfloat radius,
			std::vector<size_t>& k_indices, bool sort = true)const;
	public:
		std::pair<size_t, cfloat> knn_search(const cvector2d& point)const;
	protected:
		const std::vector<cvector2d>& pts;
		std::shared_ptr<Cache> pTree;
	};
	
}



#endif
