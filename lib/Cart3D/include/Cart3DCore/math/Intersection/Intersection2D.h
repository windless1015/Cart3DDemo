#ifndef CART3D_INTERSECTION_2D_UTIL_H
#define CART3D_INTERSECTION_2D_UTIL_H

#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>
#include <array>
namespace Cart3D
{
	struct CART3D_MATH_CLASS PreciseVertCoords2
	{
		int id;   
		cvector2l pt; 
	};


	struct CART3D_MATH_CLASS SegmentSegmentIntersectResult
	{
		bool doIntersect;   
		bool cIsLeftFromAB; 
		SegmentSegmentIntersectResult();
		explicit operator bool() const;
	};


	class CART3D_MATH_CLASS  ConvertVector2D {
	public:
		ConvertVector2D(
			const cvector2d& minp,
			const cvector2d& maxp);
	public:
		cvector2l to_int64(const cvector2d& vec)const;
		cvector2d to_cfloat(const cvector2l& vec)const;
	private:
		cvector2d m_minp, m_maxp;
	private:
		cvector2d m_cent;
		cfloat m_invr;
		cfloat m_range;
	};

	class CART3D_MATH_CLASS Intersection2D
	{
	public:
		static bool ccw(const cvector2l & a, const cvector2l & b);
		static bool ccw(const cvector2l & a, const cvector2l & b, const cvector2l & c);
		static bool ccw(const std::array<PreciseVertCoords2, 3> & vs);
		static bool ccw(const PreciseVertCoords2* vs);
		static SegmentSegmentIntersectResult do_seg_seg_isct(
			const std::array<PreciseVertCoords2, 4> & vs);
		static cvector2l find_seg_seg_interserction(
			const cvector2l& a, const cvector2l& b, 
			const cvector2l& c, const cvector2l& d);

		static cvector2d find_seg_seg_interserction(
			const cvector2d& a, const cvector2d& b,
			const cvector2d& c, const cvector2d& d,
			const ConvertVector2D& convert);
	};
}

#endif