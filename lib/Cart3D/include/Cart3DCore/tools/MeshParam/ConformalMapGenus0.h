#ifndef CART3D_TOOLS_COMFORMALMAPGENUS0_H
#define CART3D_TOOLS_COMFORMALMAPGENUS0_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D {

	class CART3D_TOOLS_CLASS ConformalMapGenus0
	{
	public:
		/*
		 * @brife  �������������
		 * @detail 
		 * @param[in]     mesh ��������������
		 * @param[in] puncture �����Ƭ��һ����չ���̶����ĵ�
		 * @param[out]   tex2d ƽ���������
		 * @param[out]   tex3d �����������
		 */
		static bool mesh_to_sphere(
			const OpenTriMesh& mesh,const FH& puncture,
			std::vector<cvector2d>& tex2d,
			std::vector<cvector3d>& tex3d);

	

	private:
		static cfloat compute_sphere_radius(
			const cvector2d& v0,const cvector2d& v1,const cvector2d& v2, 
			cfloat areaFraction);


	};

}



#endif