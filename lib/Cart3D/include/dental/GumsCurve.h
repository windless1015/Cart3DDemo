#ifndef CART3D_GUMS_GUMSCURVE_H
#define CART3D_GUMS_GUMSCURVE_H
#include <unsupported/Eigen/Splines>
#include <dentalmesh/SurfaceMesh.h>

namespace Cart3D
{
	struct Spline
	{
		using Spline3d = Eigen::Spline<pmp::Scalar, 3>;
		using CtrlPt = Spline3d::ControlPointVectorType;
		using KnotVec = Spline3d::KnotVectorType;
		KnotVec chordlength;
		Spline3d spline;

		std::vector<pmp::Point> _pts;
		std::vector<float> param;
		int is_spline;


		bool interplate_curve(const std::vector<pmp::Point>& pts, int deg);

		pmp::Point eval(pmp::Scalar param)const;
	};

	class CubeicSpline
	{
	public:
		void interpolation(const pmp::Point& ps, const pmp::Point& pe, const pmp::Point& psd, const pmp::Point& ped);
		pmp::Point eval(float u)const;
	protected:
		pmp::Point t0, t1, t2, t3;
	};


	struct CubicCloseSpline
	{
		void interplate_curve(const std::vector<pmp::Point>& dataPoints);
		pmp::Point eval(float t) const;
		std::vector<pmp::Point> ctrl;
		int nseg;
	};

}
#endif