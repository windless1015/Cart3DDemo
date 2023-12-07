#ifndef CART3D_TOOLS_COMFORMALMAPGENUS0_H
#define CART3D_TOOLS_COMFORMALMAPGENUS0_H

#include <Cart3DToolsDefine.h>
#include <Util/OpenMeshUtil.h>


namespace Cart3D {

	class CART3D_TOOLS_CLASS ConformalMapGenus0
	{
	public:
		/*
		 * @brife  球面参数化网格
		 * @detail 
		 * @param[in]     mesh 待参数化的网格
		 * @param[in] puncture 尖刺面片，一般是展开固定中心点
		 * @param[out]   tex2d 平面参数坐标
		 * @param[out]   tex3d 球面参数坐标
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