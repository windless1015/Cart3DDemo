#ifndef CART3D_AUTO_GEN_CLYINDER_SHELL_H
#define CART3D_AUTO_GEN_CLYINDER_SHELL_H
#include <csgmesh/CSGMesh.h>
#include <CoordSystem/CoordSystem.h>
namespace Cart3D
{
	class FastClyinder
	{
	public:
		static bool fast_clyinder(const CSGMesh& btm,CoordSystem sys,CSGMesh& convex);
	};
}



#endif