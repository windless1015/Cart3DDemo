#ifndef CART3DALGORITHM_BVH_H
#define CART3DALGORITHM_BVH_H
#include <Cart3dMathDefine.h>
#include <Box/BBox.h>
#include <Util/BoostUtil.h>
namespace Cart3D
{

	struct CART3D_MATH_CLASS GeomBlob
	{
		int id;
		cvector3d   point;
		BoundingBox  bbox;
		GeomBlob() :id(-1), point(0, 0, 0), bbox(){}
		GeomBlob(const GeomBlob& blob) :id(blob.id), point(blob.point), bbox(blob.bbox){}
		GeomBlob(const GeomBlob&& blob)noexcept :id(blob.id), point(blob.point), bbox(blob.bbox){}
		GeomBlob& operator=(GeomBlob& blob)
		{
			if (this != &blob)
			{
				std::memcpy(this, &blob, sizeof(GeomBlob));
			}
			return *this;
		}
	};


	class CART3D_MATH_CLASS  Cart3DBvh
	{
	public:
		struct AABVHNode
		{
			AABVHNode() :left(nullptr), right(nullptr) {}
			BoundingBox bbox;
			std::shared_ptr<AABVHNode> left;
			std::shared_ptr <AABVHNode> right;
			std::vector<int>  blobids;
			inline bool is_leaf() const { return left == nullptr; }
		};
	public:
		Cart3DBvh(std::vector<GeomBlob>& geoms, bool need_keep_data = true);
		Cart3DBvh(ct_vector<GeomBlob>& geoms, bool need_keep_data = true);
		virtual ~Cart3DBvh();
	public: //相交器
		void for_each_in_box(
			const BoundingBox& bbox,
			std::function<void(int idx)>action);
		void for_each_in_box_safe(
			const BoundingBox& bbox,
			std::function<void(int idx)>action,
			const cvector3d& deps);
		void for_each_in_box_first(
			const BoundingBox& bbox,
			std::function<bool(int idx)>action);
		void for_each_in_box_safe_first(
			const BoundingBox& bbox,
			std::function<bool(int idx)>action,
			const cvector3d& deps);
	public://射线相交
		void for_each_ray_overlap_box(
			const cvector3d& ray_ori,
			const cvector3d& ray_dir,
			std::function<void(int idx)>action);
		void for_each_ray_overlap_box_safe(
			const cvector3d& ray_ori,
			const cvector3d& ray_dir,
			std::function<void(int idx)>action, const cfloat& deps);
		void for_each_ray_overlap_box_first(
			const cvector3d& ray_ori,
			const cvector3d& ray_dir,
			std::function<bool(int idx)>action, const cfloat& deps = 0);
	public://相交查询，树与树相交查询
		void do_query(const Cart3DBvh& bvh, std::function<void(int ida, int idb)>action)const;
		bool do_query_fisrt(const Cart3DBvh& bvh, std::function<bool(int ida, int idb)>action)const;
	public:
		//std::function<bool(int fid)> 去索引面片的三个坐标
		bool point_isin_model(const cvector3d& point, std::function<bool(int fid)> trizcast)const;
	public:
		// returns true if the ray cast from p along positive z axis hits triangle in
		// exactly one spot, with edge cases handled appropriately
		static bool tri_zcast(
			const cvector3d& p,
			const cvector3d& q,
			const cvector3d& r,
			const cvector3d& s);
	public:
		int n_blobs()const;
	private:
		std::shared_ptr<AABVHNode> construct_tree(int begin, int end, int last_dim);
		void quick_select(int select, int begin, int end, int dim);
	private:
		std::shared_ptr<AABVHNode> root;
		std::vector<GeomBlob> blobs;
		std::vector<int> tmpids;
	};


}


#endif