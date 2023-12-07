#ifndef CART3D_SDF_UTIL_H
#define CART3D_SDF_UTIL_H

#include <Cart3DOffsetDefine.h>
#include <Util/EigenUtil.h>
#include <Grid/Grid.h>


namespace fcpw
{
	template<size_t DIM>
	class Scene;
}

class PQP_Model;
namespace Cart3D
{
	enum DCMark :sbyte
	{
		OFFSET,
		UNDERCUT,
	};
	struct CART3D_OFFSET_CLASS SdfTools
	{
		static cmatrix4d compute_undercut_mat(const cvector3d& dir);
		static cmatrix4d compute_min_volume(const std::vector<cvector3d>& mesh_verts);
		static cmatrix4d scale_points(const std::vector<cvector3d>& mesh_verts, cfloat size);
		static void affine(std::vector<cvector3d>& mesh_verts, const cmatrix4d& mat);
		static void min_max_box(
			const std::vector<cvector3d>& mesh_verts,
			cvector3d& min_box, cvector3d& max_box);
		static cfloat pt_on_tri(
			const cvector3d& x,
			const cvector3d& pa,
			const cvector3d& pb, 
			const cvector3d& pc);

		static int orientation(
			cfloat x1, cfloat y1, 
			cfloat x2, cfloat y2, cfloat& twice_signed_area);
		static bool point_in_triangle_2d(
			cfloat x0, cfloat y0,
			cfloat x1, cfloat y1,
			cfloat x2, cfloat y2,
			cfloat x3, cfloat y3,
			cfloat& a, cfloat& b, cfloat& c);
		static cfloat orient2d(
			cfloat pax, cfloat pay,
			cfloat pbx, cfloat pby,
			cfloat pcx, cfloat pcy);

		static std::shared_ptr<fcpw::Scene<3>> create_scene3d(
			const std::vector<cvector3d>& pts,
			const std::vector<int>& tris);


		static std::shared_ptr<PQP_Model> create_pqp(
			const std::vector<cvector3d>& pts,
			const std::vector<int>& tris);

	};
	struct CART3D_OFFSET_CLASS SdfInfo
	{
		sbyte* sdf_mark;
		int* sdf_close_triangle;
		cfloat far_dist;
		SdfInfo();
	};
}

#endif