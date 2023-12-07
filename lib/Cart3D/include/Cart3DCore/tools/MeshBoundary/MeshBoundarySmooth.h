#ifndef CART3D_MESH_BOUNDARY_SMOOTH_H
#define CART3D_MESH_BOUNDARY_SMOOTH_H

#include <Cart3DToolsDefine.h>
#include "Util/OpenMeshUtil.h"

namespace Cart3D
{
	class CART3D_TOOLS_CLASS MeshBoundaryConvex
	{
	public:
		struct GeoCompare
		{
			VH  vh;
			cfloat         dist;
			bool operator<(const GeoCompare& v1) const
			{
				return dist > v1.dist;
			}
		};
	public:
		MeshBoundaryConvex(OpenTriMesh& mesh);
		~MeshBoundaryConvex();
	public:
		bool convex_bounary(int precess_circle=3,int iter=3,int nex_node=5);
	private:
		cfloat calfacearea(const FH& fh);
		bool  caleigenvalue(cfloat covariance[], cfloat& maxeigenval);
		bool  candelface(OpenTriMesh& mesh, const HH& hh);
		bool  canmovepoint(OpenTriMesh& mesh, const cvector3d& newp, const VH& vh);
		void  lockboundaryvertex(OpenTriMesh& mesh, int rings = 2);
		void  subedge(cfloat elens = 0.2);
		void  calfeature(std::vector<cfloat>& features);
		bool  findfeature(std::vector<int>& vstatus,const VH& vh,VH& nextvh, int rings = 2);
		bool  findgeodesic(std::vector<int>& gvstatus,std::vector<int>& estatus,const VH& start,const VH& end);
		void  laplacesmooth(OpenTriMesh& mesh);
		void  delboundary(std::vector<int>& estatus,int rings);
		void  delboundary(std::vector<VH>& featurevh, std::vector<int>& estatus);
	private:
		OpenTriMesh& mesh;
	};
}


#endif