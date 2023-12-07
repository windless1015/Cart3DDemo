#ifndef CART3D_REPAIR_SMOOTH_SECTION_H
#define CART3D_REPAIR_SMOOTH_SECTION_H

#include <Cart3DRepairDefine.h>
#include <csgmesh/CSGMesh.h>

namespace Cart3D
{
	enum Continuity
	{
		C0,C1,C2
	};

	class CART3D_REPAIR_CLASS SmoothSection
	{
	public:
		static bool bilaplaec_smooth_sections(OpenTriMesh& mesh, Continuity fc);
		static bool bilaplaec_smooth_sections(OpenTriMesh& mesh, const std::vector<VH>& vhs, Continuity fc);
		static bool ortho_mesh(OpenTriMesh& mesh, cvector3d& minp, cvector3d& maxp, cvector3d& scalep);
		static bool reverse_ortho_mesh(OpenTriMesh& mesh, const cvector3d& minp, const cvector3d& maxp, const cvector3d& scalep);
	};



}

#endif