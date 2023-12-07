#ifndef CART3D_BOUNDARY_CONDITION_H
#define CART3D_BOUNDARY_CONDITION_H

#include <corkdef.h>
#include <mesh/cork_mesh.h>
#include <Util/TreeUtil.h>
namespace Cart3D
{
    enum InterType
    {
        FaceIn=0,
        EdgeOne,
        EdgeTwo,
        EdgeThe,
        VertOne,
        VertTwo,
        VertThe,
        FaceOuter,
    };

    struct InfoInter
    {
        std::uint32_t t;
        std::uint32_t e;
        InterType res; //相交类型
        std::uint32_t id;
        cvector3l pt;
    };
}




#endif