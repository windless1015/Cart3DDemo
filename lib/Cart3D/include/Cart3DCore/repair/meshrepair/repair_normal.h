#ifndef CART3D_REPAIR_REPAIR_NORMAL_H
#define CART3D_REPAIR_REPAIR_NORMAL_H

#include <Cart3DRepairDefine.h>
#include <csgmesh/CSGMesh.h>
#include <vcg/VcgMeshUtil.h>
namespace Cart3D
{
	class CART3D_REPAIR_CLASS RepairNormal
	{
	public:
		static bool build_query_tree(
			CSGMesh& mesh,
			bool jump_nonmanifold,
			std::vector<int>& faceshell,
			std::vector<std::vector<int>>& shells,
			std::vector<bool>& mark_shells);

		static  void check_shell_bad_normal(
			FixVcgMesh                         &vcgmesh,
			std::vector<int>                   &tids);

		static void orientable_shells(
			FixVcgMesh                             &vcgmesh,
			const std::vector<std::vector<int>> &shells,
			const std::vector<int>              &F2S,
			std::vector<int>                    &needReOrient,
			std::vector<int>                    &tids);

		static void check_kernel(
			FixVcgMesh                         &vcgmesh,
			const std::vector<std::vector<int>>&shells,
			const std::vector<std::vector<int>>&comps,
			std::vector<int>                   &tids);
		static void fix_shell_bad_normal(
			FixVcgMesh                         &vcgmesh,
			const std::vector<int>             &tids);
	};
}


#endif