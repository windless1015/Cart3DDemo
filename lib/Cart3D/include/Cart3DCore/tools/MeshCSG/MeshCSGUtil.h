#ifndef CART3D_TOOLS_CSG_UTIL_H
#define CART3D_TOOLS_CSG_UTIL_H

#include <Cart3DToolsDefine.h>
#include <Util/EigenUtil.h>
#include <csgmesh/CSGMesh.h>
#include <Util/OpenMeshUtil.h>
namespace Cart3D
{
	struct Planer
	{
		cvector3d plane_ori, plane_dir;
	};

	struct Segmenter
	{
		cvector3d start, end;
	};

	struct InterLoop
	{
		std::vector<cvector3d> pts;
		std::vector<int> segs;
	};

	struct Path3D {
		std::vector<cvector3d> points;
		bool isClosed = false;
	};

	struct Path3DId {
		std::vector<int> points;
		bool isClosed = false;
	};
}


#endif