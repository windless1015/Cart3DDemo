#ifndef CART3D_CONVEX_HULL_2D_H
#define CART3D_CONVEX_HULL_2D_H

#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>
namespace Cart3D
{
	class CART3D_MATH_CLASS ConvexHull2D
	{
	public:
		enum TypeConvex
		{
			QUICK_HULL,
			MONOTONE_CHAIN_HULL,
			GIFT_WRAPPING_HULL,
			GRAHAM_SCAN_HULL,
		};

	public:

		static bool compute_convex_2d(
			const std::vector<cvector2d>& pts,
			std::vector<int>& convex2d, TypeConvex tc= QUICK_HULL);

	};
}

#endif