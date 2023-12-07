#ifndef CART3D_SALM_ALIGN_TRANSFORM_H
#define CART3D_SALM_ALIGN_TRANSFORM_H

#include <Cart3DSlamDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{
    class PTPAlignTransform
    {
    public:
        PTPAlignTransform();
    public:
         void add(const cvector3d& p1, const cvector3d& p2, cfloat w = 1.0);
         void add(const PTPAlignTransform& other);
         void clear();
         cvector3d centroid1() const;
         cvector3d centroid2() const;
         cfloat total_weight() const;
    public:
        /// Compute transformation as the solution to a least squares formulation of the problem:
        /// xf( p1_i ) = p2_i
         cmatrix4d calc_rt() const;
        /// this version searches for best transformation where rotation is allowed only around given axis and with arbitrary translation
         cmatrix4d clac_fixed_axis_rotation(const cvector3d& axis) const;
        /// this version searches for best transformation where rotation is allowed only around axes orthogonal to given one
         cmatrix4d clac_orthogonal_axis_rotation(const cvector3d& ort) const;
        /// Simplified solution for translational part only
         cvector3d calc_translation() const;
    private:
        cmatrix4d summary;
    };


}



#endif