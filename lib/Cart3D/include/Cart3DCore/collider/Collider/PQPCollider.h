#ifndef CART3D_PQPCOLLIDER_COLLIDER_H
#define CART3D_PQPCOLLIDER_COLLIDER_H

#include <Cart3dColliderDefine.h>
#include <Util/EigenUtil.h>
#include <Util/TreeUtil.h>


namespace Cart3D
{
	struct CART3D_COLLIDER_CLASS PQPDistTool
	{
		cvector3d closet_p;
		cvector2d tex;
		int findex;
		cfloat dist;
		PQPDistTool():
			dist(DBL_MAX),
			findex(0),
			tex(0,0),
			closet_p(0,0,0)
		{}
	};

	enum PQPCollisionType
	{
		ON_TWO,
		INNER_TWO,
		OUTER_TWO,

		ON_ONE,
		INNER_ONE,
		OUTER_ONE
	};
	//对于水密网格，可以采用射线法计算符号，对于非水密网格，这里采用法向量的方式计算符号
	class CART3D_COLLIDER_CLASS PQPCollider
	{
	public:
		struct CART3D_COLLIDER_CLASS Cache;
		struct CART3D_COLLIDER_CLASS BV_box;
	public: //注意这里仅仅是判断碰撞，不检测符号
		bool release_model(int idmodel);
		bool start_build_model(int idmodel,int numtris=8);
		std::shared_ptr<Cache> start_build_return(int idmodel, int numtris = 8);

		//----------------------------------------------//
		//------------不支持符号计算--------------------//
		//----------------------------------------------//
		bool add_tris(int idmodel,int idtris,
			const cvector3d& v0, 
			const cvector3d& v1,
			const cvector3d& v2);
		bool add_tris(std::shared_ptr<Cache>& ptr, int idt,
			const cvector3d& v0,
			const cvector3d& v1,
			const cvector3d& v2);
		//-------------------------------------------------------------------------------------//
		//------------支持符号计算，注意这里会引用mesh数据，因此pts,tris要控制生命周期---------//
		//-------------------------------------------------------------------------------------//

		bool add_mesh(std::shared_ptr<Cache>& ptr,
			const std::vector<cvector3d>& pts,
			const std::vector<cvector3i>& tris);
		//-----------------------------------------------//
		bool end_build_model(int idmodel);
		bool end_build_return(std::shared_ptr<Cache>& ptr);

	public:
		bool is_collider(int id0,const cmatrix4d& rt0,int id1,const cmatrix4d& rt1)const;
		bool query_collider_pairs(
			int id0, const cmatrix4d& rt0,
			int id1, const cmatrix4d& rt1,
			std::vector<std::pair<int, int>>& int_pairs)const;
	public:
	

	public:
		bool query_bv_intersecion(
			std::shared_ptr<BV_box> bv, const cmatrix4d& rt0, 
			int id,const cmatrix4d& rt1,std::vector<int>& res);
	public:
		bool query_undist_model(const cvector3d& pt, int id, PQPDistTool& dtl)const;

	public:
		bool query_tolerence(
			int id0, const cmatrix4d& rt0,
			int id1, const cmatrix4d& rt1,
			cfloat tolerence,
			std::vector<std::pair<int, int>>& int_pairs);
	public:
		bool query_unsigned_dist_model(
			int id0, const cmatrix4d& rt0,
			int id1, const cmatrix4d& rt1,
			std::tuple<cfloat,cvector3d,cvector3d>& res)const;
	public:
		bool query_ray_intersect_model(const cvector3d& ray_ori,const cvector3d& ray_dir,int idmodel,
			std::vector<int>& fids,bool repeat);

		bool query_ray_intersect_model(
			const cvector3d& ray_ori,
			const cvector3d& ray_dir,
			int idmodel,std::vector<std::pair<int,cvector3d>>& result);
	private:
		fast_map<int, std::shared_ptr<Cache>> collider;
	};



}

#endif