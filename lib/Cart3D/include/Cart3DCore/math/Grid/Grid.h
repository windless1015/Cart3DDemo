#ifndef CART3D_MATH_GIRD_H
#define CART3D_MATH_GIRD_H


#include <Cart3dMathDefine.h>
#include <Util/EigenUtil.h>


namespace Cart3D
{

	struct CART3D_MATH_CLASS Grid
	{
		cvector3d m_minp;
		cvector3d m_scale;
		union {
			struct { int udim, vdim, wdim; };
			struct { int dims[3]; };
		};

		void init_grid(const cvector3d& minp, const cvector3d& maxp, const cvector3d&scale);
		void init_grid(const cvector3d& minp, const cvector3d& maxp, int dim);

		int cache_uv, cache_uvw,cache_vw;
		cvector3d point_at(int u, int v, int w)const;
		int index_at(int u, int v, int w)const;
		int index_vw_at(int v, int w)const;
		void update_cache();
		void print_info(const std::string& str);
	};

}

#endif