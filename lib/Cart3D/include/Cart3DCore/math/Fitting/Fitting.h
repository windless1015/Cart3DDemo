#ifndef CART3D_MATH_FITTING_H
#define CART3D_MATH_FITTING_H

#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{
	class CART3D_MATH_CLASS Fitting
	{
	public:
		//最佳拟合平面
		static bool fit_plane(
			const std::vector<cvector3d>& pts,
			cvector3d& pori, cvector3d& pdir);
		static bool fit_plane(
			const std::vector<cvector3d>& pts, 
			const std::vector<cfloat>& weights,
			cvector3d& pori, cvector3d& pdir);
	public:
		static bool fit_line(
			const std::vector<cvector3d>& pts,
			cvector3d& pori, cvector3d& pdir);
		static bool fit_line(
			const std::vector<cvector3d>& pts,
			const std::vector<cfloat>& weights,
			cvector3d& pori, cvector3d& pdir);
	public:

		static Eigen::VectorX<cfloat> fit_ploy(
			const std::vector<cfloat> &X,
			const std::vector<cfloat> &Y, uint8_t orders);

	public:
		//参考vcglib fitting3实现，尽管很简单
		static bool _compute_covariance_matrix(
			const std::vector<cvector3d > &pointVec, 
			cvector3d &barycenter, cmatrix3d &m);
		static bool _compute_covariance_weight_matrix(
			const std::vector<cvector3d > &pointVec,
			const std::vector<cfloat>& weights,
			cvector3d &barycenter, cmatrix3d &m);
	};

}


#endif