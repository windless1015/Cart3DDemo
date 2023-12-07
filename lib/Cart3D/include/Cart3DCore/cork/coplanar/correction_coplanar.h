#ifndef CORK_CORRECTION_COPLANAR_H
#define CORK_CORRECTION_COPLANAR_H

#include <csgmesh/CSGMesh.h>

namespace Cart3D
{
	class CorrectionCop
	{
	public:

		static bool correct_mesh(BaseTriMesh& mesh0, BaseTriMesh& mesh1,
			bool fix0,bool fix1);
	};


}

#endif