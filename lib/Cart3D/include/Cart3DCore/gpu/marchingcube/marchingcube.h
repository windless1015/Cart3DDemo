#ifndef CART3D_GEN_MC_H
#define CART3D_GEN_MC_H

#include <Cart3DGPUDefine.h>
#include <Util/EigenUtil.h>
#include <Util/BoostUtil.h>
namespace Cart3D
{
	struct MCGPUCache;
    class CART3D_GPU_CLASS MarchingCube
    {
    public:
		static void parallel_marching_cube(
			const cvector3d& ori, const cvector3d& dscale, const cfloat* sdf,
			unsigned nx, unsigned ny, unsigned nz, cfloat iso,
			std::vector<cvector3d>& tripts, std::vector<int>& triindex);

		static void parallel_marching_cube(
			const ct_vector<cvector3d>& pts,
			const ct_vector<cfloat>& sdf,
			const ct_vector<cvectort<int, 8>>& cell,
			cfloat iso,
			std::vector<cvector3d>& tripts, 
			std::vector<int>& triindex);

        static void parallel_marching_cube_norep(
            const cvector3d& ori, const cvector3d& dscale, const cfloat* sdf,
            unsigned nx, unsigned ny, unsigned nz, cfloat iso,
            std::vector<cvector3d>& pts, std::vector<int>& tris);

		static void repeat(std::vector<cvector3d>& pts, std::vector<int>& tris);

	public:

        static void cpu_marching_cube(
            const cvector3d& ori, const cvector3d& dscale, const cfloat* sdf,
            unsigned nx, unsigned ny, unsigned nz, cfloat iso,
            std::vector<cvector3d>& pts, std::vector<int>& tris);
	public:


		static void gpu_marching_cube(
			const cvector3d& ori, const cvector3d& dscale, const cfloat* sdf,
			unsigned nx, unsigned ny, unsigned nz, cfloat iso,
			std::vector<cvector3d>& pts, std::vector<int>& tris);

	public:

		static std::shared_ptr<MCGPUCache> init_cache(unsigned nx, unsigned ny, unsigned nz);
		static void gpu_marching_cube(std::shared_ptr<MCGPUCache>& cache,
			const cvector3d& ori, const cvector3d& dscale, const cfloat* sdf,
			unsigned nx, unsigned ny, unsigned nz, cfloat iso,
			std::vector<cvector3d>& pts, std::vector<int>& tris);
		static void free_cache(std::shared_ptr<MCGPUCache>& ptr);
	private:
		static cvector3d find_feature_point(
			const std::vector<cvector3d>& points,
			const std::vector<cvector3d>& normals);
    };

}

#endif