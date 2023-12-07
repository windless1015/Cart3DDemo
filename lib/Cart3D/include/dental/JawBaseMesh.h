#ifndef CART3D_DENTAL_JAWBASEMESH_H
#define CART3D_DENTAL_JAWBASEMESH_H

#include <Util/OpenMeshUtil.h>
#include <CoordSystem/CoordSystem.h>

namespace Cart3D
{

	class JawBaseMesh
	{
	public:

		static bool generation_base(const OpenTriMesh& mesh, const CoordSystem& sys, OpenTriMesh& jmesh,cfloat h, cfloat offset);

	private:
		static bool generate_gingval_mesh(
			std::vector<cvector3d> &convex_h, 
			std::vector<cvector3d> &boundary, 
			const CoordSystem & sys, OpenTriMesh & jmesh,
			std::vector<VH> &mxs, bool &retflag);
		static bool generate_body_mesh(
			const CoordSystem & sys,
			const cvector3d& lowpts,
			OpenTriMesh & jmesh,
			bool reverse);

	private:
		static bool delaunay_mesh(
			const std::vector<cvector3d>& pts,
			const CoordSystem& sys,
			std::vector<cvector3d>& tripts,
			std::vector<int>& trisIndex);

		static bool delaunay_mesh(
			const std::vector<cvector3d>& pts,
			const std::vector<cvector3d>& holes,
			const CoordSystem& sys,
			std::vector<cvector3d>& tripts,
			std::vector<int>& trisIndex);
	};

}


#endif