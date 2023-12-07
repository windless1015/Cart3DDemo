#pragma once
#include <Cart3DGPUDefine.h>
#include <Util/EigenUtil.h>
namespace Cart3D
{
	class CART3D_GPU_CLASS MarchCubeCPU
	{
	public:
		using muint = unsigned int;
	public:
		
		MarchCubeCPU();
	public:
	
	public:
		void mc(const cvector3d& ori, const cvector3d& dscale, const cfloat* mapval, cfloat surface,
			unsigned int udim, unsigned int vdim, unsigned int wdim,
			std::vector<cvector3d>& ctriangle, std::vector<int>& index);
	protected:
		struct GridCell{
			cvector3d point[8];
			cfloat value[8];
		};
		typedef struct mcVec3i
		{
		public:
			union {
				struct { unsigned int v[3]; };
				struct {unsigned int x, y, z;};
			};
			inline unsigned int& operator[](unsigned int i) { return v[i]; }
		} mcVec3i;

		void mc_internalComputeEdge(
			mcVec3i*& slab_inds, std::vector<cvector3d> & outputMesh, GridCell &grid,
			unsigned int s, unsigned int e, unsigned int axis, unsigned int u, unsigned int v, unsigned int w);
		unsigned int mc_internalToIndex1D(unsigned int i, unsigned int j, unsigned int k, const mcVec3i& size);
		static unsigned int mc_internalToIndex1DSlab(unsigned int i, unsigned int j, unsigned int k, const mcVec3i& size);
		cvector3d interpolate(cvector3d &aPoint, cvector3d &bPoint, const cfloat aValue, const cfloat bValue, const cfloat iso);
	protected:
		cfloat isosurface;
		unsigned int uDim;
		unsigned int vDim;
		unsigned int wDim;
	protected:
		unsigned long long mc_internalMarching_cube_tris[256];

	};




}