#ifndef CART3D_HOLE_FINDER_H
#define CART3D_HOLE_FINDER_H

#include <Cart3DRepairDefine.h>
#include <Util/OpenMeshUtil.h>

namespace Cart3D
{
    class CART3D_REPAIR_CLASS HoleQuery
    {
    public:

        static bool extra_all_holes(const OpenTriMesh& omesh, std::vector<std::vector<HH>>& hhs);

    };


}



#endif