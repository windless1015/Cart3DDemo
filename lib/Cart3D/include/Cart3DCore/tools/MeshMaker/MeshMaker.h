#ifndef CART3D_TOOLS_MESHMAKER_H
#define CART3D_TOOLS_MESHMAKER_H


#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>
#include <csgmesh/CSGMesh.h>
namespace Cart3D
{
	class CART3D_TOOLS_CLASS MeshMaker
	{
	public:
		//Èç¹ûtess_y==-1£¬Ôòtess_y==tess_x
		static void make_plane(OpenTriMesh& mesh,int tess_x, int tess_y = -1);
		static void make_plane(OpenTriMesh& mesh,
			cfloat min_x,cfloat max_x,
			cfloat min_y,cfloat max_y,
			int tess_x, int tess_y = -1);
		static void make_bump(OpenTriMesh& mesh, int tess, cfloat sigma = 1.0);
		static void make_wave(OpenTriMesh& mesh, int tess, cfloat omega);
		static void make_frac(OpenTriMesh& mesh, int tess);
		static void make_frac(OpenTriMesh& mesh, 
			cfloat min_x, cfloat max_x,
			cfloat min_y, cfloat max_y,
			int tess);
		static void make_cube(OpenTriMesh& mesh, int tess_x,int tess_y=-1,int test_z=-1);
		static void make_disc(OpenTriMesh& mesh, int tess_th, int tess_r);
		static void make_cyl(OpenTriMesh& mesh, int tess_th, int tess_h, cfloat r = 1.0);
		static void make_ccyl(OpenTriMesh& mesh, int tess_th, int tess_h, cfloat r = 1.0);
		static void make_scyl(OpenTriMesh& mesh, int tess_th, int tess_h, cfloat r = 1.0);
		static void make_cone(OpenTriMesh& mesh, int tess_th, int tess_r, cfloat r = 1.0);
		static void make_ccone(OpenTriMesh& mesh, int tess_th, int tess_r, cfloat r = 1.0);
		static void make_torus(OpenTriMesh& mesh, int tess_th, int tess_ph, cfloat r = 0.25);
		static void make_knot(OpenTriMesh& mesh, int tess_th, int tess_ph, cfloat r = 0.2);
		static void make_klein(OpenTriMesh& mesh, int tess_th, int tess_ph);
		static void make_tree(OpenTriMesh& mesh, int max_recursion=3);
		static void make_klein_bot(OpenTriMesh& mesh, int tess_th, int tess_ph);
		static void make_teapot(OpenTriMesh& mesh, int tess, bool omit_bottom = false, bool taller = false);
	public:
		static void make_box(const cvector3d& p0,
			const cvector3d& xdir, const cvector3d& ydir,
			const cvector3d& zdir, cfloat xlen, cfloat ylen, cfloat zlen,
			CSGMesh& btm);
	public:
		static void make_arrow(CSGMesh& mesh,
			const cvector3d& base, const cvector3d& vert,
			const cfloat& thickness = 0.05f, 
			const cfloat& coneRadius = 0.1f, 
			const cfloat coneSize = 0.2f, 
			const int qual = 32);
	};
}




#endif