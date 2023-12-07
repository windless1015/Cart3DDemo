#ifndef CART3D_REPAIR_REMOVE_TOPO_NOISE_H
#define CART3D_REPAIR_REMOVE_TOPO_NOISE_H

#include <Cart3DRepairDefine.h>
#include <vcg/VcgMeshUtil.h>

namespace Cart3D
{
    class CART3D_REPAIR_CLASS RemoveTopoNoise
    {
    public:
        static bool delete_double_faces(FixVcgMesh& vcgmesh);
    };

}


#endif