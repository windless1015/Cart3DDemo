#ifndef CART3D_SLICER_SLICER_H
#define CART3D_SLICER_SLICER_H

#include <Cart3DSlicerDefine.h>
#include <csgmesh/CSGMesh.h>
#include <Util/TreeUtil.h>
#include <Util/BoostUtil.h>
namespace Cart3D
{
	struct CART3D_SLICER_CLASS SlicerLayer
	{
		cfloat ios;
		ct_vector<cvector3d> pts;
		ct_vector<cvector2i> segs;

		SlicerLayer();

		void shift_to_fit();
	};


	class CART3D_SLICER_CLASS Slicer
	{
	public:
		static bool slicer_mesh(const CSGMesh& mesh,
			const cvector3d& plane_pt, const cvector3d& plane_dir, int nlayer,
			std::vector<SlicerLayer>& layers);


	};
}


#endif