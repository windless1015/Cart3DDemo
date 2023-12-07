#ifndef CART3D_SLICER_MESHORTHO_H
#define CART3D_SLICER_MESHORTHO_H

#include <Cart3DSlicerDefine.h>
#include <csgmesh/CSGMesh.h>
#include <Util/TreeUtil.h>

namespace Cart3D
{

	struct OptimalBuildDirOptions
	{
		unsigned int  n_dirs = 300;     // # of candidate build directions to test
		unsigned int  buffer_size = 128;     // size of the rasterization buffer (used for shadow area)
		cfloat overhang_threshold = 30.0;    // deg
		cfloat w_height = 0.25;    //
		cfloat w_shadow_area = 0.25;    //
		cfloat w_support_contact = 0.25;    //
		cfloat w_support_volume = 0.25;    //
		cfloat crit_srf_boost = 10.0;    // boost penalty for critical surfaces touched by supports
		cfloat forb_cone_angle = 3.0;     // amplitude of each cone hosting a forbidden build direction
		std::vector<cvector3d>  forb_dirs; // set of forbidden build directions
		fast_set<unsigned int> crit_srf;  // list of triangles that are critical
	};

	class CART3D_SLICER_CLASS MeshOrtho
	{
	public:
		using u_int8_t = std::uint8_t;
	public:

		static cvector3d optimal_build_dir(const CSGMesh & m,
			const OptimalBuildDirOptions   & opt,
			cfloat                    & best_height,
			cfloat                    & best_shadow_area,
			cfloat                    & best_contact_area,
			cfloat                    & best_supp_volume);
	public:
		static void sphere_coverage(const unsigned int n_samples, std::vector<cvector3d> & points);
		static cfloat shadow_on_build_platform(const CSGMesh & m, 
			const cvector3d  & build_dir,const unsigned int img_size,u_int8_t * data);
		;
	};
}




#endif