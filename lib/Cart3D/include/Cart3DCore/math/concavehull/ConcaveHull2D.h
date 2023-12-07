#ifndef CART3D_CONCAVE_HULL_2D_H
#define CART3D_CONCAVE_HULL_2D_H

#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>
namespace Cart3D
{

	class CART3D_MATH_CLASS ConcaveHull2D
	{
	public:
		/*
		 * @brief 计算凹包
		 * @detail 
		 * @param[in]         pts 点集合
		 * @param[in]        hull 凸包
		 * @param[out]    concave 凹包
		 * @param[in]   concavity 凹包度量
		 * @param[in] lengththres 
		 */
		static bool concaveman_hull(
			const std::vector<cvector2d>& pts,
			const std::vector<int>& hull,
			std::vector<int>& concave,
			cfloat concavity,cfloat lengththres);

		/*
		 * @brief 计算凹包
		 * @detail
		 * @param[in]         pts 点集合
		 * @param[out]    concave 凹包
		 * @param[in]   concavity 凹包度量
		 * @param[in] lengththres
		 */
		static bool concaveman_hull(
			const std::vector<cvector2d>& pts,
			std::vector<int>& concave,
			cfloat concavity, cfloat lengththres);
	};


}

#endif