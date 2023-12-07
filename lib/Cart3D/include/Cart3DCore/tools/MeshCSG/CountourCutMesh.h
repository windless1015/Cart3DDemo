#ifndef CART3D_TOOLS_COUNTOUR_CUTMESH_H
#define CART3D_TOOLS_COUNTOUR_CUTMESH_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>
#include <MeshCurve/CurveFwd.h>
namespace Cart3D
{
	class CART3D_TOOLS_CLASS CountourCutMesh
	{
	public:
		static bool countour_cut_mesh(OpenTriMesh& mesh,
			const std::vector<cvector3d>& surfPtsIn,
			OpenTriMesh& left_mesh, OpenTriMesh& right_mesh,bool smooth);

		static bool countour_cut_mesh(
			OpenTriMesh& mesh, std::shared_ptr<fcpw::Scene<3>>& _tree,
			const std::vector<cvector3d>& surfPtsIn,
			OpenTriMesh& left_mesh, OpenTriMesh& right_mesh, bool smooth);

		static bool countour_cut_mesh(OpenTriMesh& mesh,
			const ct_vector<cvector3d>& surfPtsIn,
			OpenTriMesh& left_mesh, OpenTriMesh& right_mesh, bool smooth);
	public:

	private:
		CountourCutMesh(OpenTriMesh& mesh) : m_mesh(mesh),tree(nullptr), m_gloabal_smooth(false){}
		CountourCutMesh(OpenTriMesh& mesh,std::shared_ptr<fcpw::Scene<3>>& _tree) : 
			m_mesh(mesh),tree(_tree), m_gloabal_smooth(false) {}
		void set_smooth(bool sm) { m_gloabal_smooth = sm; }
		bool calc_loops(const ct_vector<cvector3d>& surfPtsIn, ct_vector<SurfPt>& surfPtsOut);
		bool calc_loops(const ct_vector<SurfPt>& surfPtsIn, ct_vector<SurfPt>& surfPtsOut);
		bool zone_parts(const ct_vector<SurfPt>& surfPtsOut);
		bool cut_mesh_core(OpenTriMesh& left_mesh, OpenTriMesh& right_mesh)const;
	private:
		void denoise(const ct_vector<SurfPt>& surfPtsIn, ct_vector<SurfPt>& surfPts) const;
		bool div_mesh_vhs(ct_vector<SurfPt>& surfPtsIn, ct_vector<VH>& vhs);
		bool div_mesh_ehs(const ct_vector<SurfPt>& surfPtsIn, ct_vector<SurfPt>& surfPtsOut, ct_vector<VH>& vhs);
		bool solve_selfintersection(const ct_vector<SurfPt>& surfPtsIn, ct_vector<SurfPt>& surfPtsOut, ct_vector<VH>& vhsOut);
		void smooth_path(ct_vector<SurfPt>& geodesic,bool loop) const;
		void smooth_path(const ct_vector<VH>& sPath, ct_vector<SurfPt>& geodesic) const;
		bool smooth_epts(const SurfPt& prev, const SurfPt& cur, const SurfPt& next, SurfPt& result) const;
		bool smooth_vpts(const SurfPt& prev, const SurfPt& cur, const SurfPt& next, ct_vector<SurfPt>& results) const;
		bool is_link_ee(int v1, int v2, int& commonE);
		bool is_on_edge(int v, int e);
	private:
		OpenTriMesh& m_mesh;
		std::shared_ptr<fcpw::Scene<3>> tree;
		ct_vector<int> m_face_patch;
		ct_vector<EH> m_ehs;
		bool m_gloabal_smooth;
	};

}


#endif