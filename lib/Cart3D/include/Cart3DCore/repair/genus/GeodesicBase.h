#ifndef CART3D_GEODESIC_BASE_IMPL_H
#define CART3D_GEODESIC_BASE_IMPL_H

#include <Cart3DRepairDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D
{
	class CART3D_REPAIR_CLASS GeodesicBasic
	{
	public:
		GeodesicBasic(const OpenTriMesh& mesh);
		~GeodesicBasic();
	protected:
		FH get_fh(const cvector3d& p);
		bool get_handle(const cvector3d& p, int& vtype, int& vindex);
		cfloat rat_on_ab_ac(int hhindex, const cvector2d& imagexy, cfloat ratio) const;
		cfloat rat_on_ab_bc(int hhindex, const cvector2d& imagexy, cfloat ratio) const;
		cfloat rat_on_ab_ic(int hhindex, const cvector2d& imagexy) const;
		cfloat rat_on_ab_ii(int hhindex, const cvector2d& imagexy1, const cvector2d& imagexy2) const;
		cfloat rat_on_ac_ab(int hhindex, const cvector2d& imagexy1, cfloat ratio) const;
		cfloat rat_on_ac_bc(int hhindex, const cvector2d& imagexy1, cfloat ratio) const;
		void get_dxy_ab(int hhindex, cfloat leftLen, cfloat rightLen, cvector2d& newxy) const;
		void get_cxy_ab(int hhindex, cfloat leftLen, cfloat rightLen, cvector2d& newxy) const;
		void get_dxy_ac(int hhindex, const cvector2d& imagexy, cvector2d& newxy) const;
		void get_dxy_bc(int hhindex, const cvector2d& imagexy, cvector2d& newxy) const;
	protected:
		const OpenTriMesh&     m_mesh;
		std::vector<cfloat>    m_he_lengths;
		std::vector<cfloat>    m_he_angles;
		std::vector<int>       m_saddles;          
		std::vector<cvector2d> m_plane_coord;       
		std::vector<cvector2d> m_pseud_xy;          
	private:
		GeodesicBasic(const GeodesicBasic&) = delete;
		GeodesicBasic &operator=(const GeodesicBasic&) = delete;
	};


	struct RayWindow
	{
		int             m_parent;
		cfloat          m_t0;
		cfloat          m_t1;
		cvector2d       m_src;
		int             m_index;
	};
	struct EdgeList
	{
		int             m_index;
		int             m_parent;
		int             m_status;
	};
	struct CART3D_REPAIR_CLASS GeodesicP
	{
		cvector3d          p;
		int            index;
		int             type; 
		GeodesicP();
		bool operator==(const GeodesicP& node) const;
		bool operator!=(const GeodesicP& node) const;
	};
}

#endif //GEODESIC_BASE_IMPL_H