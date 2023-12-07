#ifndef CART3D_CDT2_5D_H
#define CART3D_CDT2_5D_H

#include <Cart3DGenerationDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{
	class CART3D_GENERATION_CLASS CDT2o5D
	{
	public:
		CDT2o5D(const cvector3d& fn);
	public:
		void clear();
	public:
		//添加边界坐标
		size_t add_coord(const cvector3d& p);
		//添加边约束
		void add_segment(int start, int end);
	public:
		bool cdt();
	public:
		cvector3d nor;
		cvector3d ori, udir, vdir;
		std::vector<cvector3d> m_in_coords;
		std::vector<int> m_in_segments;
	public:
		std::vector<cvector3d> m_out_pts;
		std::vector<int> m_out_tris;
	};
}



#endif