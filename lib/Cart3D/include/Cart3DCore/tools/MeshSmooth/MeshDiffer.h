#pragma once
#ifndef CART3D_MESH_DIFFER_H
#define CART3D_MESH_DIFFER_H

#include <Cart3DToolsDefine.h>
#include "Util/OpenMeshUtil.h"

namespace Cart3D
{
	struct CART3D_TOOLS_CLASS CurvatureNode
	{
		VH vh;
		cvector3d vn;
		cfloat fMaxCurvature, fMinCurvature;
		cvector3d cMaxCurvDir, cMinCurvDir;
		CurvatureNode();
	};


	class CART3D_TOOLS_CLASS MeshDiffer
	{
	public:
		/*
		 * @brief ���������ζ��㷨����
		 * @detail ����ǹ����㡢��Ч�㡢�����ε㣬������0
		 * @param[in] mesh ����������
		 * @param[in]   vh �����㶥��
		 * @return ���㷨����
		 */
		static cvector3d compute_vertex_normal(
			const OpenTriMesh& mesh, const VH& vh);
		/*
		 * @brief ������������Ƭ������
		 * @detail �������Ч�棬������0
		 * @param[in]  mesh ����������
		 * @param[in]    fh �����㶥��
		 * @param[in]isunit �Ƿ���й�һ��
		 * @return ��Ƭ������
		 */
		static cvector3d compute_face_normal(
			const OpenTriMesh& mesh, const FH& fh,bool isunit=true);

		/*
		 * @brief ���������ζ��㷨������Ϣ
		 * @detail ����ǹ����㡢��Ч�㡢�����ε㣬������Ĭ��ֵ
		 * @param[in] mesh ����������
		 * @param[in]   vh �����㶥��
		 * @return ����������Ϣ
		 */
		static CurvatureNode compute_vertex_curvature(
			const OpenTriMesh& mesh, const VH& vh);

		static void compute_vertex_curvature(const OpenTriMesh& mesh,
			std::vector<CurvatureNode>& curvature);

		/*
		 * @brief ���������ζ��㷨������Ϣ
		 * @detail ����ǹ����㡢��Ч�㡢�����ε㣬������Ĭ��ֵ,�ο�meshlabʵ��
		 * @param[in]       mesh ����������
		 * @param[out] curvature ������������
		 */
		static void compute_vertex_curvature_optim(
			const OpenTriMesh& mesh,
			std::vector<CurvatureNode>& curvature);

		/*
		 * @brief ���������ζ�������΢��
		 * @detail ����ǹ����㡢��Ч�㡢�����ε㣬������Ĭ��ֵ,�ο�meshlabʵ��
		 * @param[in]        mesh ����������
		 * @param[in]   curvature ������������
		 * @param[out] dcurvature ������������΢��
		 */
		static bool compute_vertex_dcurvature(
			const OpenTriMesh& mesh,
			const std::vector<CurvatureNode>& curvature,
			std::vector<cvector4d>& dcurvature);



		/*
		 * @brief �������������˹����
		 * @detail ��˹���ʷ�Ӧ���������̶�
		 * @param[in]         mesh ����������
		 * @param[out]   curvature ������������
		 */
		static void compute_lengths(const OpenTriMesh& mesh, std::vector<cfloat>& length);
		static void compute_angles(const OpenTriMesh& mesh, std::vector<cfloat>& angle);
		static bool compute_vertex_guassian_curvature(
			const OpenTriMesh& mesh, 
			std::vector<cfloat>& curvature);

	public:
		/*
		 * @brief ���������ζ���voronoi���
		 * @detail ����ǹ����㡢��Ч�㡢�����ε㣬������0
		 * @param[in] mesh ���������� 
		 * @param[in]   vh �����㶥�� 
		 * @return ����voronoi��� 
		 */
		static cfloat voronoi_area(
			const OpenTriMesh& mesh, const VH& vh);
		/*
		 * @brief ���������αߵ�����Ȩ��
		 * @detail ����ǹ����㡢��Ч�㡢�����ε㣬������0
		 * @param[in] mesh ����������
		 * @param[in]   eh �������id
		 * @return ����Ȩ��
		 */
		static cfloat cotan_weight(const OpenTriMesh& mesh, const EH& eh);
		
		/*
		 * @brief Ӧ���벹���е�Ȩ��
		 * @detail ����ǹ����㡢��Ч�㡢�����ε㣬������0
		 * @param[in] mesh ����������
		 * @param[in]   hh �������id
		 * @return ����Ȩ��
		 */
		static bool cot_laplace_matrix(
			const OpenTriMesh& mesh,
			std::vector<cfloat>& cot_vec,
			std::vector<cfloat>& area_vec);
		/*
		 * @brief ���������ζ���fairȨ��
		 * @detail ����ǹ����㡢��Ч�㡢�����ε㣬������0
		 * @param[in] mesh ����������
		 * @param[in]   vh �����㶥��
		 * @return ����fairȨ��
		 */
		static cfloat fair_vertex_weight(const OpenTriMesh& mesh, const VH& vh);
		static cfloat robust_fair_vertex_weight(const OpenTriMesh& mesh, const VH& vh);
		/*
		 * @brief ���������ΰ������Ȩ��
		 * @detail ����ǹ����㡢��Ч�㡢�����ε㣬������0
		 * @param[in] mesh ����������
		 * @param[in]   hh �������id
		 * @return ����Ȩ��
		 */
		static cfloat fair_cotangent_weight(
			const OpenTriMesh& mesh,
			const HH& hh);

		static cfloat robust_fair_cotangent_weight(
			const OpenTriMesh& mesh,
			const HH& hh);

		/*
		 * @brief ͳ�����mesh������Ϣ
		 */
		static void compute_mesh_info(
			const OpenTriMesh& mesh, 
			std::vector<cvector3d>& vnormals,
			std::vector<cfloat>& vareas,
			std::vector<cvector3d>& fareas);
	public:

		static bool cot_laplace_matrix(
			const OpenTriMesh& mesh,
			Eigen::SparseMatrix<cfloat>& L,
			Eigen::SparseMatrix<cfloat>& M);

		static bool cot_laplace_matrix(
			const OpenTriMesh& mesh,
			const VH& vh,
			Eigen::Triplet<cfloat, int>& ii,
			std::vector<Eigen::Triplet<cfloat, int>>& ij);
	};
}


#endif