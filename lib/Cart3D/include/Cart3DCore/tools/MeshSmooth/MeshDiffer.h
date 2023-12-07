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
		 * @brief 计算三角形顶点法向量
		 * @detail 如果是孤立点、无效点、非流形点，均返回0
		 * @param[in] mesh 待计算网格
		 * @param[in]   vh 待计算顶点
		 * @return 顶点法向量
		 */
		static cvector3d compute_vertex_normal(
			const OpenTriMesh& mesh, const VH& vh);
		/*
		 * @brief 计算三角形面片法向量
		 * @detail 如果是无效面，均返回0
		 * @param[in]  mesh 待计算网格
		 * @param[in]    fh 待计算顶点
		 * @param[in]isunit 是否进行归一化
		 * @return 面片法向量
		 */
		static cvector3d compute_face_normal(
			const OpenTriMesh& mesh, const FH& fh,bool isunit=true);

		/*
		 * @brief 计算三角形顶点法曲率信息
		 * @detail 如果是孤立点、无效点、非流形点，均返回默认值
		 * @param[in] mesh 待计算网格
		 * @param[in]   vh 待计算顶点
		 * @return 顶点曲率信息
		 */
		static CurvatureNode compute_vertex_curvature(
			const OpenTriMesh& mesh, const VH& vh);

		static void compute_vertex_curvature(const OpenTriMesh& mesh,
			std::vector<CurvatureNode>& curvature);

		/*
		 * @brief 计算三角形顶点法曲率信息
		 * @detail 如果是孤立点、无效点、非流形点，均返回默认值,参考meshlab实现
		 * @param[in]       mesh 待计算网格
		 * @param[out] curvature 三角网格曲率
		 */
		static void compute_vertex_curvature_optim(
			const OpenTriMesh& mesh,
			std::vector<CurvatureNode>& curvature);

		/*
		 * @brief 计算三角形顶点曲率微商
		 * @detail 如果是孤立点、无效点、非流形点，均返回默认值,参考meshlab实现
		 * @param[in]        mesh 待计算网格
		 * @param[in]   curvature 三角网格曲率
		 * @param[out] dcurvature 三角网格曲率微商
		 */
		static bool compute_vertex_dcurvature(
			const OpenTriMesh& mesh,
			const std::vector<CurvatureNode>& curvature,
			std::vector<cvector4d>& dcurvature);



		/*
		 * @brief 计算三角网格高斯曲率
		 * @detail 高斯曲率反应曲面弯曲程度
		 * @param[in]         mesh 待计算网格
		 * @param[out]   curvature 三角网格曲率
		 */
		static void compute_lengths(const OpenTriMesh& mesh, std::vector<cfloat>& length);
		static void compute_angles(const OpenTriMesh& mesh, std::vector<cfloat>& angle);
		static bool compute_vertex_guassian_curvature(
			const OpenTriMesh& mesh, 
			std::vector<cfloat>& curvature);

	public:
		/*
		 * @brief 计算三角形顶点voronoi面积
		 * @detail 如果是孤立点、无效点、非流形点，均返回0
		 * @param[in] mesh 待计算网格 
		 * @param[in]   vh 待计算顶点 
		 * @return 顶点voronoi面积 
		 */
		static cfloat voronoi_area(
			const OpenTriMesh& mesh, const VH& vh);
		/*
		 * @brief 计算三角形边的余切权重
		 * @detail 如果是孤立点、无效点、非流形点，均返回0
		 * @param[in] mesh 待计算网格
		 * @param[in]   eh 待计算边id
		 * @return 余切权重
		 */
		static cfloat cotan_weight(const OpenTriMesh& mesh, const EH& eh);
		
		/*
		 * @brief 应用与补洞中的权重
		 * @detail 如果是孤立点、无效点、非流形点，均返回0
		 * @param[in] mesh 待计算网格
		 * @param[in]   hh 待计算边id
		 * @return 补洞权重
		 */
		static bool cot_laplace_matrix(
			const OpenTriMesh& mesh,
			std::vector<cfloat>& cot_vec,
			std::vector<cfloat>& area_vec);
		/*
		 * @brief 计算三角形顶点fair权重
		 * @detail 如果是孤立点、无效点、非流形点，均返回0
		 * @param[in] mesh 待计算网格
		 * @param[in]   vh 待计算顶点
		 * @return 顶点fair权重
		 */
		static cfloat fair_vertex_weight(const OpenTriMesh& mesh, const VH& vh);
		static cfloat robust_fair_vertex_weight(const OpenTriMesh& mesh, const VH& vh);
		/*
		 * @brief 计算三角形半边余切权重
		 * @detail 如果是孤立点、无效点、非流形点，均返回0
		 * @param[in] mesh 待计算网格
		 * @param[in]   hh 待计算边id
		 * @return 余切权重
		 */
		static cfloat fair_cotangent_weight(
			const OpenTriMesh& mesh,
			const HH& hh);

		static cfloat robust_fair_cotangent_weight(
			const OpenTriMesh& mesh,
			const HH& hh);

		/*
		 * @brief 统筹计算mesh常用信息
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