#ifndef CART3D_DUAL_MARCHINGCUBE_H
#define CART3D_DUAL_MARCHINGCUBE_H

#include <Cart3DGPUDefine.h>
#include <Grid/Grid.h>

namespace Cart3D
{
	
	class CART3D_GPU_CLASS DualMarchingCube
	{
	public:

		static void dc(const Grid& sgrid, const cfloat* const sdf,cfloat iso,
			std::vector<cvector3d>& pts, std::vector<int>& quads);

		static void dc(
			const Grid& sgrid,
			const cfloat* const sdf,
			const sbyte* const mark,
			cfloat iso,
			std::vector<cvector3d>& pts,
			std::vector<sbyte>& markvert,
			std::vector<int>& quads);
	};
}


#endif