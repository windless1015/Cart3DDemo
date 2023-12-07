#ifndef CART3D_EXACT_SDF_COMPUTE_H
#define CART3D_EXACT_SDF_COMPUTE_H

#include <Cart3DOffsetDefine.h>
#include <Util/EigenUtil.h>
#include <offset3d/SdfUtil.h>
#include <Util/BoostUtil.h>
namespace Cart3D
{
	struct CART3D_OFFSET_CLASS ESdfParam
	{
		int split;
		int maxdepth; //���ϸ�����
		
		cfloat thres;   //��Сϸ�ֳߴ�
		cfloat iso;		//��Ҫ����ĵ�ֵ��
		cfloat safe;    //��ȫ���
		bool repeat;

		ESdfParam();
	};

	class CART3D_OFFSET_CLASS ExactSdfCompute
	{
	public:
		static void compute_exact_usdf(
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			ct_vector<cvector3d>& pts,
			ct_vector<cfloat>&sdf,
			ct_vector<int>& closetris,
			ct_vector<cvectort<int, 8>>& cell,
			ESdfParam param);



		//Todo...
		static void compute_exact_sdf(
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			ct_vector<cvector3d>& pts,
			ct_vector<cfloat>&sdf,
			ct_vector<cvectort<int, 8>>& cell,
			ESdfParam param);

	private:
		static void repeat_cell(ct_vector<cvector3d>& pts, ct_vector<cvectort<int, 8>>& cell);
		static int compute_exact_usdf_core(
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			ct_vector<cvector3d>& pts,
			ct_vector<cfloat>&sdf,
			ct_vector<int>& closetris,
			ct_vector<cvectort<int, 8>>& cell,
			ESdfParam param,cvector3d& minp,cvector3d& maxp,const int rev[8][3]);
	};


}


#endif