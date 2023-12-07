#ifndef CART3D_GRID_OP_H
#define CART3D_GRID_OP_H

#include <Grid/Grid.h>
#include <CartesianGrid/GridUtil.h>
#include <csgmesh/CSGMesh.h>


namespace Cart3D
{
	class GridOp
	{
	public:
		static bool check_param(const GridParam&gparam,std::string& info);
		static bool compute_gird(
			std::shared_ptr<CSGMesh>& background,
			const GridParam&gparam, 
			Grid& start_grid,Grid& end_grid);

	};


}



#endif 