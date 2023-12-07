#ifndef CART3D_INTERSECTION_3D_UTIL_H
#define CART3D_INTERSECTION_3D_UTIL_H

#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>
#include <array>
namespace Cart3D
{
	struct CART3D_MATH_CLASS PreciseVertCoords
	{
		int id;   
		cvector3l pt;
	};
	struct CART3D_MATH_CLASS TriangleSegmentIntersectResult
	{
		bool doIntersect;   
		bool dIsLeftFromABC;
		TriangleSegmentIntersectResult();
		operator bool()const;
	};

	class CART3D_MATH_CLASS  ConvertVector3D{
	public:
		ConvertVector3D(
			const cvector3d& minp,
			const cvector3d& maxp);
		ConvertVector3D(const ConvertVector3D& that);
	public:
		cvector3l to_int64(const cvector3d& vec)const;
		cvector3d to_cfloat(const cvector3l& vec)const;
	private:
		cvector3d m_minp, m_maxp;
	private:
		cvector3d m_cent;
		cfloat m_invr;
		cfloat m_range;
	};
	
	class CART3D_MATH_CLASS Intersection3D
	{
	public:
		static bool orient3d(const cvector3l& a, const cvector3l& b, const cvector3l& c);
		static bool orient3d(const cvector3l& a, const cvector3l& b, const cvector3l& c, const cvector3l& d);
		static bool orient3d(const std::array<PreciseVertCoords, 4>& vs);
		static bool orient3d(const PreciseVertCoords* vs);
		static TriangleSegmentIntersectResult do_tri_seg_isct(
			const std::array<PreciseVertCoords, 5>& vs);
		static cvector3d find_tri_seg_interserction(
			const cvector3d& a, const cvector3d& b, const cvector3d& c,
			const cvector3d& d, const cvector3d& e,
			const ConvertVector3D& convert);
		static cvector3l find_tri_seg_interserction(
			const cvector3l& a, const cvector3l& b, const cvector3l& c,
			const cvector3l& d, const cvector3l& e);
	public:

	};



}



#endif