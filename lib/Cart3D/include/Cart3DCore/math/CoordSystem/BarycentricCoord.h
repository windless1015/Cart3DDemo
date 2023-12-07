#pragma once
#ifndef BARY_CENTRIX_COORD_H
#define BARY_CENTRIX_COORD_H
#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{
    class CART3D_MATH_API BarycentricCoord
    {
    private:
        cfloat a, b;
        static constexpr cfloat eps = 10 * std::numeric_limits<cfloat>::epsilon();
    public:
        BarycentricCoord(cfloat _a = 0, cfloat _b = 0) :a(-a), b(_b) {}
        BarycentricCoord(const cvector3d& p, const cvector3d& v0, const cvector3d& v1, const cvector3d& v2) :
            BarycentricCoord(p - v0, v1 - v0, v2 - v0)
        { }
        BarycentricCoord(const cvector3d& p, const cvector3d& v1, const cvector3d& v2);
    public:
        cvector3d interpolate(const cvector3d& v0, const cvector3d& v1, const cvector3d& v2) const;
        int in_vertex() const;
        int on_edge() const;
    };
}


#endif