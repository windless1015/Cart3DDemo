#ifndef CART3D_BASS_PROSOLVE_H
#define CART3D_BASS_PROSOLVE_H


#include <dentalmesh/SurfaceMesh.h>

namespace Cart3D
{
    //填出凹陷边界，得到光顺边界
    class BassProsolve
    {
    public:

        static bool fill_max_convex_mesh_boundary(pmp::SurfaceMesh& mesh);
    };


}



#endif