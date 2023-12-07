#ifndef CART3D_SELF_INTERSECTION_TREE_H
#define CART3D_SELF_INTERSECTION_TREE_H

#include <Cart3DRepairDefine.h>
#include <csgmesh/CSGMesh.h>
#include <Util/TreeUtil.h>
#include <Util/BoostUtil.h>
namespace Cart3D
{

	class CART3D_REPAIR_CLASS SelfIntersectionTree
	{
	public:
		SelfIntersectionTree(CSGMesh& mesh);
	public:
		void set_debug(bool enabledeb, std::string spath);
	public:
		void run_repair();
	private:
		void _create_topo_enfs(fast_map<std::uint64_t,fast_set<int>>& enfs);
		void _split_componts(const fast_map<std::uint64_t, fast_set<int>>&enfs,ct_vector<ct_vector<int>>& components);
		void _extract_mesh(const ct_vector<ct_vector<int>>& components, std::vector<std::shared_ptr<CSGMesh>>& pmesh);
		void _fill_small_hole(std::vector<std::shared_ptr<CSGMesh>>& pmesh,
			std::vector<int>& numholes);
		void _repair_face_normal(std::vector<std::shared_ptr<CSGMesh>>& pmesh);
		void _tree_collision(const std::vector<std::shared_ptr<CSGMesh>>& pmesh,
			ct_vector<ct_vector<int>>& split);
		void _union_splits(const std::vector<std::shared_ptr<CSGMesh>>& pmesh,
			const ct_vector<ct_vector<int>>& split, std::vector<std::shared_ptr<CSGMesh>>& smeshes);
	private:
		CSGMesh& m_mesh;
	private:
		bool enable_debug;
		std::string debug_path;
	};


}



#endif