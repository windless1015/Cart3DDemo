#ifndef CART3D_EIGEN_SPLINE_H
#define CART3D_EIGEN_SPLINE_H

#include <Cart3DSplineCore.h>
#include <Util/EigenUtil.h>


namespace Cart3D
{
	class CART3D_SPLINECORE_CLASS EigenSpline
	{
	public:
		struct CART3D_SPLINECORE_CLASS Cache;
	public:
		EigenSpline();
	public:
		bool interplate_curve(const std::vector<cvector3d>& pts,int deg);
	public:
		cvector3d eval(cfloat param)const;
	private:
		std::shared_ptr<Cache> m_spline;
	};
}

#endif