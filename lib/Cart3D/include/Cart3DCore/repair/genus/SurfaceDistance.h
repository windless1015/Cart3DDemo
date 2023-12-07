#ifndef CART3D_GEODESIC_DISTANCE_IMPL_H
#define CART3D_GEODESIC_DISTANCE_IMPL_H

#include <Cart3DRepairDefine.h>
#include <Util/OpenMeshUtil.h>

namespace Cart3D
{
	class CART3D_REPAIR_CLASS SurfaceDistance
	{
	public:
		SurfaceDistance(const OpenTriMesh& mesh);
	public:
		void run(
			const std::vector<VH>& start,
			const std::vector<cfloat>& dist,
			std::vector<cfloat>& geo,
			std::vector<short>& geotime);
	private:
		bool add_start_region(
			const std::vector<VH>& start,
			const std::vector<cfloat>& dist);
	private:
		static bool get_field_at_c(
			const cvector3d & b, 
			const cvector3d & c,
			cfloat vb, cfloat & vc);
	private:
		const OpenTriMesh& mesh;
	};
}

#endif