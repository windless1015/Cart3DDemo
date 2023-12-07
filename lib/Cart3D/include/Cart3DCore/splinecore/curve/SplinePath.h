#ifndef CART3D_SPLINECORE_SPLINEPATH_H
#define CART3D_SPLINECORE_SPLINEPATH_H

#include <Cart3DSplineCore.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{

	struct CART3D_SPLINECORE_CLASS CtrlPoint {
		CtrlPoint(const cvector3d& _pt, const cvector3d& _pn);
		cfloat dist(const CtrlPoint& other) const;
		cfloat length() const;
		CtrlPoint summed_point() const;
		cvector3d pt;
		cvector3d pv;
	};

	class CART3D_SPLINECORE_CLASS SplinePath
	{
	public:
		struct PathCache;
	public:
		SplinePath();
		SplinePath(const std::vector<CtrlPoint>& points);
		virtual ~SplinePath();
	public:
		//注意这里需要外部对输入点进行处理
		bool compute_spline(const std::vector<CtrlPoint>& points);
		CtrlPoint pos(cfloat t) const;
		CtrlPoint dir(cfloat t) const;
		cfloat curvature(cfloat t) const;
		cfloat max_curvature(int nseg) const;
	protected:
		std::vector<CtrlPoint>     m_points;
		cfloat                     m_length;  // sum of segment lengths
		std::shared_ptr<PathCache> m_cache;
	};

}


#endif