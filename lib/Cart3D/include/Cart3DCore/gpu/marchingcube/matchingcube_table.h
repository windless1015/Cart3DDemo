#ifndef CART3D_MATCNGCUBE_TABLE_H
#define CART3D_MATCNGCUBE_TABLE_H


#include <Cart3DGPUDefine.h>
#include <inttypes.h>

namespace Cart3D
{
    struct CART3D_GPU_CLASS Table {
        const int triTable[256][16];
        const unsigned int numVertsTable[256];
        const int cubeCases[256];
        Table();
    };
}


#endif