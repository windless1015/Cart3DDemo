#ifndef CART3D_BASS_PROSOLVE_H
#define CART3D_BASS_PROSOLVE_H


#include <dentalmesh/SurfaceMesh.h>

namespace Cart3D
{
    //������ݱ߽磬�õ���˳�߽�
    class BassProsolve
    {
    public:

        static bool fill_max_convex_mesh_boundary(pmp::SurfaceMesh& mesh);
    };


}



#endif