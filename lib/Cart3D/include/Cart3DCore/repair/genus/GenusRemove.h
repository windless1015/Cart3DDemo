#ifndef CART3D_GENUS_REMOVE_H
#define CART3D_GENUS_REMOVE_H

#include <Cart3DRepairDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D
{

	struct CART3D_REPAIR_CLASS GenusParam
	{
		bool is_del_face;
		int del_ring;
		int seach_ring;
		bool is_fill_holes;
		GenusParam();
	};
	//线程不安全
	class CART3D_REPAIR_CLASS GenusRemove
	{
	public:
		struct Cache;
	public:
		GenusRemove(OpenTriMesh& mesh);
		~GenusRemove();
	public:
		void set_enable_debug(bool debug, std::string str);
		bool remove_small_tunnels(const GenusParam& param);
	private:
		void remove_nonmanifold();
		int split_small_comp();
	private:
		static int cut_mesh(
			std::shared_ptr<Cache>& m_pcache, int ic,
			int meshgenus,
			std::vector<VH>& seedvhs,
			OpenMesh::VPropHandleT<int>&rmark);
		static void compute_geodesic(std::shared_ptr<Cache>& m_pcache, int ic);
		static void compute_critical(
			std::shared_ptr<Cache>& m_pcache, int ic,
			std::vector<VH>& seedvhs);
		static bool find_min_tunnels(
			std::shared_ptr<Cache>& m_pcache, int ic,
			const VH&  vh, int radius);
		static int compte_genus(std::shared_ptr<OpenTriMesh>& m_mesh);
		static void selct_nn_vhs(
			const OpenTriMesh& mesh,
			const std::vector<VH>& seeds,
			int nn,
			std::vector<VH>& vhs, bool addseed);
	private:
		OpenTriMesh& m_mesh;
		bool enable_debug;
		std::string debug_path;
		std::shared_ptr<Cache> m_pcache;
	};
}



#endif