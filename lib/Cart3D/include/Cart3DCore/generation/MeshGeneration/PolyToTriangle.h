#ifndef CART3D_GENREATION_POLYTOTRIANGLE_H
#define CART3D_GENREATION_POLYTOTRIANGLE_H
#include <Cart3DGenerationDefine.h>
#include <Util/EigenUtil.h>


namespace Cart3D
{
	//������ȡ��cork�����ǻ�����
	class CART3D_GENERATION_CLASS  PolyToTriangle
	{
	public:
		void clear();
	public:
		/*
		 * @brief �����Ҫ�������ǻ��ĵ�  
		 * @param[in] x,y ������
		 */
		size_t add_coord(cfloat x, cfloat y);
		size_t add_coord(const cvector2d& p);
		size_t add_coord(const cvector2d& p,int mark);

		/*
		 * @brief �����Ҫ�������ǻ���Լ���߶�
		 * @param[in] start��end �߶ζ˵�
		 * @param[in]    markers �߶�����
		 *   --0--�ڲ��߶�
		 *   --1--�ⲿ�߶�
		 */
		void add_segment(int start, int end, int markers);
	public:
		//�޶������ʷ�
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
