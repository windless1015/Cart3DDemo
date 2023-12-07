#ifndef CART3D_MESH_SMOOTH_H
#define CART3D_MESH_SMOOTH_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>

namespace Cart3D
{

	class CART3D_TOOLS_CLASS MeshSmooth
	{
	public:
		static bool smooth_vhs(OpenTriMesh& mesh, const std::vector<VH>& vhs,int iter);
		static bool smooth_vh(OpenTriMesh& mesh, const VH& vh);
	public:
		static bool jacobi_laplace_smoother(OpenTriMesh& mesh, const std::vector<VH>& vhs,int cont, int iter);
	public:
		static bool implict_smooth_vhs(OpenTriMesh& mesh, const std::vector<VH>& vhs,const std::vector<cfloat>& weights);
	private:
		static bool is_smooth_ok(OpenTriMesh& mesh,const VH& vh, const cvector3d&newp);
		static bool can_move_point(OpenTriMesh& mesh, const cvector3d& newp, const VH& vh);
	};

}



#endif