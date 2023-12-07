#ifndef CART3D_SMOOTH_GEODESIC_LOOPS_IMPL_H
#define CART3D_SMOOTH_GEODESIC_LOOPS_IMPL_H

#include <Cart3DRepairDefine.h>
#include <genus/GeodesicBase.h>
#include <Util/TreeUtil.h>
#include <stack>

namespace Cart3D
{
	class CART3D_REPAIR_CLASS SmoothGeodesicLoops :public GeodesicBasic
	{
	public:
		SmoothGeodesicLoops(const OpenTriMesh& mesh);
		~SmoothGeodesicLoops();
	public:
		bool shortest_loop(int index, const std::vector<VH>& vhs, std::vector<VH>& loopvhs);
	private:
		bool init_cross_edge(
			const std::vector<GeodesicP>& geodesicloop,
			const int                      currentid,
			std::vector<int>&              estatus,
			std::vector<int>&              vstatus,
			VH&                  startvh,
			VH&                  sandlevh);
		int find_face_loops(
			const GeodesicP&              pp,
			const GeodesicP&              pre,
			const GeodesicP&              next,
			const int                      currentid,
			std::vector<int>&              estatus,
			std::vector<HH>&   innerhh);
		int find_next_hh(
			const VH&            vh,
			const int                      index,
			const std::vector<EdgeList>&   raylist);
		int find_next_hh(
			const HH&          hh,
			const int                      index,
			const std::vector<EdgeList>&   raylist);
		bool find_ray0(
			std::vector<EdgeList>&         raylist,
			std::stack<RayWindow>&         raystack);
		bool find_edge(
			const VH&            startvh,
			const int                      currentid,
			const std::vector<int>&        estatus,
			const std::vector<int>&        vstatus,
			std::vector<int>&              fstatus,
			std::vector<EdgeList>&         raylist);
		bool find_edge0(
			VH&                  startvh,
			const int                      currentid,
			const std::vector<int>&        estatus,
			const std::vector<int>&        vstatus,
			std::vector<EdgeList>&         raylist);
		int vv_nn(
			const VH&            vh,
			const int                      currentid,
			const std::vector<int>&        estatus,
			const std::vector<int>&        vstatus,
			fast_map<VH, size_t>&vhmap,
			fast_map<EH, size_t>&  ehmap);
		int he_nn(
			const HH&          hh,
			const int                      currentid,
			const std::vector<int>&        estatus,
			const std::vector<int>&        vstatus,
			fast_map<VH, size_t>&vhmap,
			fast_map<EH, size_t>&  ehmap);
		bool is_tunnels(
			const std::vector<GeodesicP>& geodesicloop);
	private:
		cfloat    mEpsilonRad;
	};
}


#endif //SMOOTH_GEODESIC_LOOPS_IMPL_H