#ifndef CART3D_MARK_JAW_H
#define CART3D_MARK_JAW_H

#include <Util/OpenMeshUtil.h>
#include <csgmesh/CSGMesh.h>
namespace Cart3D
{
	struct CutSys
	{
		int id;
		cvector3d pt;
		cvector3d xdir;
		cvector3d ydir;
	};
	class MarkJaw
	{
	public:

		static void mark_jaw(OpenTriMesh& mesh,
			const std::vector<CutSys>& sys,
			CSGMesh& unionmesh,CSGMesh& submesh);

		static void mark_jaw(OpenTriMesh& mesh, CutSys sys, CSGMesh& unionmesh, CSGMesh& submesh);

	private:
		static std::vector<cvector3d> cut_fhs(
			OpenTriMesh& mesh, const std::vector<FH>& fhs, 
			const cvector3d& ori, const cvector3d& dir, const cvector3d& sortdir);

		static void gen_loops(CSGMesh& loop,cvector3d dir, const std::vector<cvector3d>& looppts);
		static void gen_loops_impl(CSGMesh& loop,cvector3d dir, const std::vector<cvector3d>& looppts);
	};

}



#endif