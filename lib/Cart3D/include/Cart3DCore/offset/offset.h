#ifndef CART3D_OFFSET_H
#define CART3D_OFFSET_H

#include <Cart3DOffsetDefine.h>
#include <Util/OpenMeshUtil.h>

namespace Cart3D
{
	enum OffsetJtType
	{
		jtSquare, //���ӷ�ʽΪ������
		jtCircle, //���ӷ�ʽΪԲ����
	};
	struct CART3D_OFFSET_CLASS PolygonBooleanRes {
		std::vector<std::pair<bool, std::vector<cvector3d>>> remaining;
		std::vector<std::pair<bool, std::vector<cvector3d>>> subtracted;
	};
	class CART3D_OFFSET_CLASS Offset
	{
	public://wrapper cavc
		struct CART3D_OFFSET_CLASS CPolyLine;
		static std::shared_ptr<CPolyLine> create_polyline(const std::vector<cvector2d>& polys,bool is_closed);
		//ע��z���ڶ�����Ȧ͹��
		static std::shared_ptr<CPolyLine> create_polyline(const std::vector<cvector3d>& polys,bool is_closed);
		//������Ȧ������
		static int compute_winding_number(std::shared_ptr<CPolyLine> ptr, const cvector2d& pt);
		//offset��Ȧ
		static bool parallel_offset_polys(std::shared_ptr<CPolyLine> ptr,cfloat offd,
			std::vector<std::pair<bool, std::vector<cvector2d>>>& polys);
		//ע�������z����Ȧ͹��
		static bool parallel_offset_polys(std::shared_ptr<CPolyLine> ptr, cfloat offd,
			std::vector<std::pair<bool, std::vector<cvector3d>>>& polys);


		////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////PolyLine Boolean Operator////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static bool union_polyline(std::shared_ptr<CPolyLine> ptr_one, std::shared_ptr<CPolyLine> ptr_two,
			PolygonBooleanRes& res);
		static bool exclude_polyline(std::shared_ptr<CPolyLine> ptr_one, std::shared_ptr<CPolyLine> ptr_two,
			PolygonBooleanRes& res);
		static bool intersect_polyline(std::shared_ptr<CPolyLine> ptr_one, std::shared_ptr<CPolyLine> ptr_two,
			PolygonBooleanRes& res);
		static bool xor_polyline(std::shared_ptr<CPolyLine> ptr_one, std::shared_ptr<CPolyLine> ptr_two,
			PolygonBooleanRes& res);
	public:
		
	};

	struct CART3D_OFFSET_CLASS Offset2o5D
	{
		Offset2o5D(const cvector3d& fn);
		
		bool offset(const std::vector<cvector3d>& path,
			bool is_close,
			cfloat iso, std::vector<cvector3d>& pts);


		cvector3d nor;
		cvector3d ori, udir, vdir;
	};


}


#endif