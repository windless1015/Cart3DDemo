#ifndef CART3D_TOOLS_TEXTMESH_H
#define CART3D_TOOLS_TEXTMESH_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>
#include <string>

namespace Cart3D {

	class CART3D_TOOLS_CLASS TextMesh
	{
		struct Cache;
		using Polygon2d = std::vector<cvector2d>;
	public:
		TextMesh();
		~TextMesh();
	public:
		bool set_font(const std::string &font_file);
		bool set_font_dims(int dims);
		bool set_font_gap(cfloat gap);
		bool set_refine(cfloat refine);
	public:
		/**
		 * @brief ����3D���ֱ�������
		 * @param[in]      text ���������������
		 * @param[in]xpos��ypos �����ļ��ĳ�ʼλ��
		 * @param[in] font_size �������ֵĴ�С
		 * @param[in]   extrude �������ֵĺ��
		 * @return ���ֱ�������.
		 */
		std::shared_ptr<OpenTriMesh>  generate(const std::string &text,
			cfloat xpos,cfloat ypos,cfloat font_size, cfloat extrude);
		std::shared_ptr<OpenTriMesh>  generate(const std::wstring &text,
			cfloat xpos, cfloat ypos, cfloat font_size, cfloat extrude);
		std::vector<std::shared_ptr<OpenTriMesh>> generates(
			const std::string &text,
			cfloat xpos, cfloat ypos, cfloat font_size, cfloat extrude);
		std::vector<std::shared_ptr<OpenTriMesh>> generates(
			const std::wstring &text,
			cfloat xpos, cfloat ypos, cfloat font_size, cfloat extrude);
	private:
		bool generate_contours(const std::wstring &text,
			cfloat xpos, cfloat ypos,
			cfloat font_size,
			std::vector<std::pair<cvector3d, std::vector<Polygon2d>>>&contours);
		bool generate_contours(
			int codepoint, cfloat& xpos, cfloat& ypos, cfloat font_size,
			cfloat& scale,
			std::vector<Polygon2d> &contours);
		std::shared_ptr<OpenTriMesh> merge_mesh(std::vector<std::shared_ptr<OpenTriMesh>>& meshes);
	public:
		void resolve_intersection(const std::vector<Polygon2d>& contours, std::vector<Polygon2d>& solver,int type);
		void resolve_intersection(const Polygon2d& contours, std::vector<Polygon2d>& solver,int type);
		void resample_ring(Polygon2d& cring);
		std::shared_ptr<OpenTriMesh> contours_to_mesh(const std::vector<Polygon2d>& contours, cfloat extrude);
	private:
		std::shared_ptr<Cache> m_cache;

	};
}


#endif