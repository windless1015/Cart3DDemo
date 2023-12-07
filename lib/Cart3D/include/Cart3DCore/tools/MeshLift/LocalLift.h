#ifndef CART3D_TOOLS_LOCAL_LIFT_H
#define CART3D_TOOLS_LOCAL_LIFT_H

#include <Cart3DToolsDefine.h>
#include <csgmesh/CSGMesh.h>


namespace Cart3D
{
    class CART3D_TOOLS_CLASS LocalLift
    {
    public:

        static bool fast_local_lift(
            CSGMesh& mesh, const std::vector<int>& tris,
            const cmatrix4d& rt);
    };

}


#endif