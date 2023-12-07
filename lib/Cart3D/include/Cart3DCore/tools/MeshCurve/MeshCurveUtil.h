#ifndef CART3D_MESHCURVE_UTIL_H
#define CART3D_MESHCURVE_UTIL_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>
#include <MeshCurve/CurveFwd.h>


namespace Cart3D
{
	class CART3D_TOOLS_CLASS MeshCurveUtil
	{
	public:
		static cvector2d project_to_plane(
			const cvector3d& pO,
			const cvector3d& xAxis,
			const cvector3d& yAxis,
			const cvector3d& p3d);

		static void get_barycenter_coord(
			const cvector3d& p,
			const cvector3d& A,
			const cvector3d& B,
			const cvector3d& C,
			cfloat& u, cfloat& v, cfloat& w);

		static bool segments_intersection(
			const cvector2d& A, const cvector2d& B,
			const cvector2d& C, const cvector2d& D,
			cvector2d& interPt,cfloat eps=1e-5);

		static bool is_segments_intersection(
			const cvector2d& A, const cvector2d& B,
			const cvector2d& C, const cvector2d& D, cfloat eps,bool check_box);

		static cvector2d rotate(const cvector2d dir, cfloat radCCW);

		static cvector3d compute_face_nor(const OpenTriMesh& mesh, const FH& fh);
	public:
		static bool create_scene3d(const OpenTriMesh& mesh, std::shared_ptr<fcpw::Scene<3>>& ptree);
	public:
		static GeodesicPt process_pt(
			const OpenTriMesh& mesh, 
			std::shared_ptr<fcpw::Scene<3>>& ptree, 
			const cvector3d& point);

		static SurfPt process_sp(
			const OpenTriMesh& _mesh,
			std::shared_ptr<fcpw::Scene<3>>& ptree,
			const cvector3d& point);
		static bool isin_vertex(
			cvector3d& p,
			cvector3d tri3[3],
			VH vhs[3],
			VH& currentvh,cfloat eps=1e-5);
		static bool isin_edge(
			cvector3d& p,
			cvector3d tri3[3],
			HH hhs[3],
			HH& currenthh,cfloat eps=1e-5);
	public:
		static cfloat compute_angle(const cvector3d& v0, const cvector3d& v00, const cvector3d& v01);
		static cvector2d compute_spfrompq(
			const cfloat& b0,
			const cfloat& b1,
			const cfloat& d0,
			const cfloat& d1);
		static cvector2d parameterize_pt3topt2(const cvector3d& v3Origin,
			const cvector3d& v3OnePositivePt,const cvector3d& v3Pt);
	};


}



#endif // !CART3D_MESHCURVE_UTIL_H
