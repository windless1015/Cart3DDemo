#ifndef CART3D_CDT_TOOLS_H
#define CART3D_CDT_TOOLS_H

#include <Cart3DGenerationDefine.h>
#include <Util/EigenUtil.h>

namespace Cart3D
{
	//封装三角化库CDT
	class CART3D_GENERATION_CLASS CDTTools
	{
	public:
		void clear();
	public:
		//添加边界坐标
		size_t add_coord(const cvector2d& p);
		//添加边约束
		void add_segment(int start, int end);
	public:
		bool cdt();
	public:

	public:
		std::vector<cvector2d> m_in_coords;
		std::vector<int> m_in_segments;
	public:
		std::vector<cvector2d> m_out_pts;
		std::vector<int> m_out_tris;
	};
}



#endif