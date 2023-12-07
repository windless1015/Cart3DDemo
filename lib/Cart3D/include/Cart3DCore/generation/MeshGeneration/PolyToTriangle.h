#ifndef CART3D_GENREATION_POLYTOTRIANGLE_H
#define CART3D_GENREATION_POLYTOTRIANGLE_H
#include <Cart3DGenerationDefine.h>
#include <Util/EigenUtil.h>


namespace Cart3D
{
	//这里提取了cork的三角化部分
	class CART3D_GENERATION_CLASS  PolyToTriangle
	{
	public:
		void clear();
	public:
		/*
		 * @brief 添加需要参与三角化的点  
		 * @param[in] x,y 点坐标
		 */
		size_t add_coord(cfloat x, cfloat y);
		size_t add_coord(const cvector2d& p);
		size_t add_coord(const cvector2d& p,int mark);

		/*
		 * @brief 添加需要参与三角化的约束线段
		 * @param[in] start、end 线段端点
		 * @param[in]    markers 线段类型
		 *   --0--内部线段
		 *   --1--外部线段
		 */
		void add_segment(int start, int end, int markers);
	public:
		//限定三角剖分
		bool cdt();
		bool cdt(const char* style);
	public:
		std::vector<cvector2d>       m_coords;
		std::vector<int>             m_pointmarkes;
		std::vector<int>             m_segments;
		std::vector<int>             m_segmarkers;
		std::vector<int>             m_index;
	public:
		std::vector<cvector2d>       m_outcoords;
		std::vector<int>             m_triangle;
	};




}

#endif  
