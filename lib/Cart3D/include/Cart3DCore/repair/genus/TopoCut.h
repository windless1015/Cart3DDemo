#ifndef CART3D_REPAIR_TOPOCUT_H
#define CART3D_REPAIR_TOPOCUT_H

#include <Cart3DRepairDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D
{
	class CART3D_REPAIR_CLASS TopoCut
	{
	public:

		static bool cut_topology(const OpenTriMesh& mesh, std::vector<bool>& cutEdgeFlags);

	private:
		static bool build_topology(const OpenTriMesh& mesh,
			std::vector<std::vector<int>>& evs,
			std::vector<std::vector<int>>& efs);
	};
}



#endif