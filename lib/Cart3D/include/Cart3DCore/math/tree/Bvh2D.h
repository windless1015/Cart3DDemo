#ifndef CART3D_MATH_BVH2D_H
#define CART3D_MATH_BVH2D_H

#include <memory>
#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{
	struct CART3D_MATH_CLASS GeomBolb2D
	{
		int id;
		cvector2d point;
		cvector2d minp;
		cvector2d maxp;

		void expends(const cvector2d& p) {
			minp = minp.cwiseMin(p);
			maxp = maxp.cwiseMax(p);
		}
		bool overlap(const GeomBolb2D& that)const {
			return (that.maxp.array() >= minp.array()).all() && (that.minp.array() <= maxp.array()).all();
		}
		void update() {
			point = (minp + maxp)*0.5f;
		}
		GeomBolb2D();
	};
	class CART3D_MATH_CLASS Bvh2D
	{
	public:
		struct CART3D_MATH_CLASS AABVHNode2D
		{
			AABVHNode2D() :
				minp(cvector2d::Constant(DBL_MAX)),
				maxp(cvector2d::Constant(-DBL_MAX)),
				left(nullptr),
				right(nullptr),
				blobids()
			{}
			cvector2d minp;
			cvector2d maxp;
			std::shared_ptr<AABVHNode2D> left;
			std::shared_ptr <AABVHNode2D> right;
			std::vector<int>  blobids;

			void expends(const cvector2d& p) {
				minp = minp.cwiseMin(p);
				maxp = maxp.cwiseMax(p);
			}

			bool overlap(const AABVHNode2D& that)const {
				return (that.maxp.array() >= minp.array()).all() && (that.minp.array() <= maxp.array()).all();
			}
			
			inline bool is_leaf() const { return left == nullptr; }
		};
	public:
		Bvh2D(std::vector<GeomBolb2D>& geoms);
	public:
		void for_each_ray_overlap_box(
			const cvector2d& ray_ori,
			const cvector2d& ray_dir,
			std::function<void(int idx)>action);
		void do_query(const Bvh2D& bvh, std::function<void(int ida, int idb)>action)const;
	private:
		std::shared_ptr<AABVHNode2D> construct_tree(int begin, int end, int last_dim);
		void quick_select(int select, int begin, int end, int dim);
	public:
		std::shared_ptr<AABVHNode2D> root;
	private:
		std::vector<GeomBolb2D> blobs;
		std::vector<int> tmpids;
	};


}



#endif