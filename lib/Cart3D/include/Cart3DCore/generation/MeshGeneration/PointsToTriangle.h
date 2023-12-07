#ifndef CART3D_GENREATION_POINTS_TO_TRIANGLE_H
#define CART3D_GENREATION_POINTS_TO_TRIANGLE_H
#include <Cart3DGenerationDefine.h>
#include <Util/EigenUtil.h>


namespace Cart3D
{
    class CART3D_GENERATION_CLASS PtsToTriangle
    {
    public:
        static bool triangle(const std::vector<cvector2d>& pts, std::vector<int>& tris);
    };
}


#endif