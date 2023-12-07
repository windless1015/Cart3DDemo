#ifndef CART3D_GEN_GRID_GEN_H
#define CART3D_GEN_GRID_GEN_H

#include <Cart3DGenerationDefine.h>
#include <CartesianGrid/GridUtil.h>
namespace Cart3D
{
	class CART3D_GENERATION_CLASS GridGen
	{
	public:
		static bool gen_cartersian_grid(std::shared_ptr<CSGMesh>& background,
			ct_vector<cvector3d>& pts,
			ct_vector<cell>& cells,
			const GridParam& gparam);
		
		static bool gen_cartersian_grid(std::shared_ptr<CSGMesh>& background,
			ct_vector<cvector3d>& pts,
			ct_vector<PosType>& ptstype,
			ct_vector<cell>& cells,
			ct_vector<PosType>& cellstype,
			const GridParam& gparam);
	private:

	};
}




#endif