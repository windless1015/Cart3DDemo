#ifndef CART3D_TOOLS_MESHPARAM_H
#define CART3D_TOOLS_MESHPARAM_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D {

	class CART3D_TOOLS_CLASS MeshParam
	{
	public:
		
		//static bool harmonic_parameterization(const OpenTriMesh& mesh);
	public:

		/*
		 * @brief Բ�̲���������
		 * @detail Բ�̲�����������Ҫ������������ǵ���ͨ�ģ��б߽�
		 * @param[in]   mesh ��������������
		 * @param[out] loops �̶��߽�
		 * @param[out]  texs ���������
		 */
		static bool mesh_to_disk(const OpenTriMesh& mesh,
			std::vector<VH>& loops,
			std::vector<cvector2d>& texs);
		/*
		 * @brief Բ�̲���������
		 * @detail Բ�̲�����������Ҫ������������ǵ���ͨ�ģ��б߽�
		 * @param[in]     mesh ��������������
		 * @param[out]   loops �̶��߽�
		 * @param[out] rangles �Ƕ�
		 * @param[out]    texs ���������
		 */
		static bool mesh_to_disk(const OpenTriMesh& mesh,
			std::vector<VH>& loops,
			std::vector<cfloat>& rangles,
			std::vector<cvector2d>& texs);
		/*
		 * @brief Բ�̲���������
		 * @detail Բ�̲�����������Ҫ������������ǵ���ͨ�ģ��б߽�
		 * @param[in]     mesh ��������������
		 * @param[in]     cent ������Բ������
		 * @param[in]        r ������Բ�̰뾶
		 * @param[out]   loops �̶��߽�
		 * @param[out] rangles �Ƕ�
		 * @param[out]    texs ���������
		 */
		static bool mesh_to_disk(const OpenTriMesh& mesh,
			const cvector2d& cent, cfloat r,
			std::vector<VH>& loops,
			std::vector<cfloat>& rangles,
			std::vector<cvector2d>& texs);

		

		/*
		 * @brief �޶�Բ�̲�������������Ϊ�˽���ָ��������
		 * @detail Բ�̲�����������Ҫ������������ǵ���ͨ�ģ��б߽�
		 * @param[in]   mesh ��������������
		 * @param[in]  loops �̶��߽�
		 * @param[in]   ctex �߽���������
		 * @param[out]  texs ���������
		 */
		static bool constrin_mesh_to_disk(
			const OpenTriMesh& mesh,
			const std::vector<VH>& loops,
			const std::vector<cvector2d>& ctex,
			std::vector<cvector2d>& texs);

	public:
		//������Ϊ0 ��mesh�����и������Բ��
		static bool cut_mesh(const OpenTriMesh& mesh, const cvector3d& zdir,
			std::vector<int>& fids);
		//Ѱ���и�·��,ע���ⲿ��Ҫ���׵��ô˽ӿ�
		static bool cut_mesh(
			const OpenTriMesh& mesh,
			const std::vector<int>& fids,
			OpenTriMesh& mesh0, std::vector<VH>& vhs0,
			OpenTriMesh& mesh1, std::vector<VH>& vhs1,
			std::vector<VH>& path);
	public:
		/*
		 * @brief ������Ϊ0������ӳ��Ϊһ����
		 * @detail �⽫�����ܵ��ָ��߸��ţ������ײ������ػ���
		 * @param[in]  mesh ����Ϊ0����ע��������Ҫ�ⲿ�жϣ��ڲ��������
		 * @param[in]  zdir �������������ﶨ������ļ�����ϵ����
		 * @param[out] texs �������������
		 * @return �Ƿ�������ɹ�
		 */
		static bool mesh_to_sphere(
			const OpenTriMesh& mesh,
			const cvector3d& zdir,
			std::vector<cvector3d>& texs);
	public:
		//ע������Ϊ�˷�ֹӳ�䷢�����ɻ��䣬���û����ķ�ʽ����ӳ��
		static bool disk_to_halfsphere(cfloat zdir,
			const cvector2d&ccent, cfloat r0,
			const cvector3d&scent, cfloat r,
			const std::vector<cvector2d>&circle,
			std::vector<cvector3d>& sphere);

	};

}

#endif