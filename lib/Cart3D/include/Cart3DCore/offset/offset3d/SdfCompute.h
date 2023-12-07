#ifndef CART3D_SDF_COMPUTE_H
#define CART3D_SDF_COMPUTE_H

#include <Cart3DOffsetDefine.h>
#include <Util/EigenUtil.h>
#include <offset3d/SdfUtil.h>

namespace Cart3D
{
	
	class CART3D_OFFSET_CLASS SdfCompute
	{
	public:
		static void compute_sdf(
			//��������
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//����
			const Grid& sgrid,
			//���볡
			cfloat* sdf,
			std::vector<int>* close_tris = nullptr,
			cfloat far_dist = DBL_MAX);
		static void compute_usdf(
			//��������
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//����
			const Grid& sgrid,
			//���볡
			cfloat* sdf,
			std::vector<int>* close_tris = nullptr,
			cfloat far_dist = DBL_MAX);
		static void compute_undercut(
			//��������
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//����
			const Grid& sgrid,
			//���볡
			cfloat* sdf,
			std::vector<int>* close_tris = nullptr,
			cfloat far_dist = DBL_MAX);
		static void compute_undercut(
			//��������
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//����
			const Grid& sgrid,
			//���볡
			cfloat* sdf,
			SdfInfo& sdfinfo);
		static void update_undercut(const Grid& sgrid, cfloat* sdf, SdfInfo& sdfinfo);
		static void compute_boundary_undercut(
			//��������
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//����
			const Grid& sgrid,
			//���볡
			cfloat* sdf,
			SdfInfo& sdfinfo);
		static void update_boundary_undercut(const Grid& sgrid, cfloat* sdf, SdfInfo& sdfinfo);
	public:
		//������Զ�������˲���
		static void smooth_sdf(const Grid& sgrid, cfloat* sdf,cfloat far_dist,int iter=3);

	private:
		static void compute_sdf_core(
			//��������
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//����
			const Grid& sgrid,
			//���볡
			cfloat* sdf,
			std::vector<int>& close_tris,
			//���볡��Ϣ
			std::vector<short>* intersection=nullptr,
			cfloat far_dist = DBL_MAX);

		//����fmm����Զ��
		static void geodesic_sdf(
			//��������
			const std::vector<cvector3d>& mesh_verts,
			const std::vector<int>& mesh_face,
			//����
			const Grid& sgrid,
			//���볡
			cfloat* sdf, std::vector<int>& close_tris,
			cfloat far_dist);
		//����������
		//static void fast_sweeping_sdf(
		//	//��������
		//	const std::vector<cvector3d>& mesh_verts,
		//	const std::vector<int>& mesh_face,
		//	//����
		//	const Grid& sgrid,
		//	//���볡
		//	cfloat* sdf, std::vector<int>& close_tris,
		//	cfloat far_dist);
	public:

	};



}


#endif