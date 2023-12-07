#pragma once
#ifndef CART3D_OOBB_H
#define CART3D_OOBB_H
#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{
	class CART3D_MATH_CLASS OBB
	{
	public:
		OBB() {}
		OBB(const std::vector<cvector3d>& pts) {
			initOBB(pts.data(), static_cast<int>(pts.size()));
		}
		OBB(const cvector3d* pts, int nvert) {
			initOBB(pts, nvert);
		}
	public:
		cvector3d get_cent()const { return m_cent; }
		cvector3d get_uaxes()const { return m_uaxes; }
		cvector3d get_vaxes()const { return m_vaxes; }
		cvector3d get_waxes()const {
			return m_waxes;
		}
		cvector3d getPt(int index)const;
	public:
		void initOBB(const cvector3d* pts, int nvert);
	protected:
		cvector3d m_cent;
		cvector3d m_uaxes;
		cvector3d m_vaxes;
		cvector3d m_waxes;
		cvector3d m_max;
		cvector3d m_min;
	protected:
		int mc_index[8][3];
	};

}

#endif // !CART3D_OOBB_H