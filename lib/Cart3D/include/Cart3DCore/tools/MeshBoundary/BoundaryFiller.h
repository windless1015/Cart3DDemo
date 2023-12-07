#pragma once
#ifndef CART3D_TOOLS_BOUNDARYFILLER_H
#define CART3D_TOOLS_BOUNDARYFILLER_H

#include <Cart3DToolsDefine.h>
#include "Util/OpenMeshUtil.h"

namespace Cart3D
{
	struct CART3D_TOOLS_CLASS FillerNode
	{
		cfloat weight;
		HH curhh;
		HH nxthh;
		bool operator<(const FillerNode& fnd)const;
	};
	class CART3D_TOOLS_CLASS BoundaryFiller
	{
	public:
		//贪心算法-->凸化最大边界
		static bool filler_max_boundary(OpenTriMesh& mesh,cfloat param=0.886);
		
		static bool smooth_mesh_boundary(OpenTriMesh& mesh, const std::vector<HH>& hole, int step = 2);
		
		static bool generate_mesh_base(OpenTriMesh& mesh, const cvector3d& dir, cfloat height, cfloat offset, int dim = 13);
	private:
		static HH find_plane_point(OpenTriMesh& mesh, std::vector<HH>& hole,int& id);
		static HH find_concave_point(OpenTriMesh& mesh, std::vector<HH>& hole,int& id);
	};
}


#endif
