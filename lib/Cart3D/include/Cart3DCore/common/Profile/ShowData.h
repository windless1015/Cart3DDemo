#ifndef CART3D_SHOW_DATA_H
#define CART3D_SHOW_DATA_H
#include <Cart3DCommonDefine.h>
#include <Util/EigenUtil.h>
#include <Util/BoostUtil.h>
#include <fstream>
namespace Cart3D
{
	class CART3D_COMMON_CLASS ShowData
	{
	public:

		static bool asc_debug(std::ofstream& fcout, const std::vector<cvector3d>& pts, cfloat r=255, cfloat g=0, cfloat b=0);
		static bool asc_debug(std::ofstream& fcout, const ct_vector<cvector3d>& pts, cfloat r=255, cfloat g=0, cfloat b=0);
		static bool asc_coordsys(std::ofstream& fcout,
			const cvector3d& ori,const cvector3d& xdir,
			const cvector3d& ydir,const cvector3d& zdir,
			int dim,cfloat size,bool symmetry=true);

		static bool asc_axis(std::ofstream& fcout,
			const cvector3d& ori, const cvector3d& dir,
			int dim, cfloat size);
	};


	template<class T>
	static bool asc_debug_template(
		std::ofstream& fcout,
		const std::vector<T>& tpts,
		std::function<cvector3d(const T&t)>func,
		cfloat r = 255, cfloat g = 0, cfloat b = 0, int model = 0)
	{
		if (!fcout.is_open())
			return false;
		std::vector<cvector3d> pts;
		pts.reserve(tpts.size());
		for (auto& tp : tpts) {
			pts.push_back(func(tp));
		}
		return ShowData::asc_debug(fcout, pts, r, g, b);
	}


	template<class T>
	static bool asc_debug_template(
		std::ofstream& fcout,
		const ct_vector<T>& tpts,
		std::function<cvector3d(const T&t)>func,
		cfloat r = 255, cfloat g = 0, cfloat b = 0, int model = 0)
	{
		if (!fcout.is_open())
			return false;
		ct_vector<cvector3d> pts;
		pts.reserve(tpts.size());
		for (auto& tp : tpts) {
			pts.push_back(func(tp));
		}
		return ShowData::asc_debug(fcout, pts, r, g, b);
	}
}



#endif // !CART3D_SHOW_DATA_H
