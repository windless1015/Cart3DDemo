#pragma once

#ifndef CART3D_GENREATION_SOLVERPOISSON_H
#define CART3D_GENREATION_SOLVERPOISSON_H

#include <Cart3DGenerationDefine.h>
#include <Util/EigenUtil.h>  
#include "MeshGeneration/GridSolver.h"
namespace Cart3D {

	struct CART3D_GENERATION_CLASS  SolverPoisson
	{
		void operator()(
			/*
			*plane:给出Fsce[0~umax,(vmax~1)*umax-vmax*umax,(0~vmax)*umax，（0~vmax）*umax+umax-1]
			*block: 给出js，je，ks，ke，ls，le的值注意遍历的顺序是（jkl）
			*/
			cfloat* ptsXX, //x-jkl方向的离散点数之积(uv方向的离散点数之积)
			cfloat* ptsYY, //y-jkl方向的离散点数之积(uv方向的离散点数之积)
			cfloat* ptsZZ, //z-jkl方向的离散点数之积(uv方向的离散点数之积) 
			unsigned int* start,//[1,1,1]（https://people.sc.fsu.edu/~jburkardt/cpp_src/tiler_3d/tiler_3d.html）
			unsigned int* iend,//face:[umax,vmax,1],Block:[jmax,kmax,lmax]
			unsigned dim1, //face:umax  block:jmax
			unsigned dim2, //face:vmax  block:kmax
			unsigned dim3, //face:1     block:lmax
			unsigned dimax);//face:max(umax,vmax),block:max(jmax,kmax,lmax)

		/*
		 * @brief 求解2.5d泊松方程生成曲面
		 * @param[in] us ue
		 * @param[in] vs ve
		 * @param[out] dompts 曲面信息，需要外部开辟空间
		 */
		void tfiSurface(
			unsigned int udim, unsigned int vdim,
			std::vector<cvector3d> &us,
			std::vector<cvector3d> &ue,
			std::vector<cvector3d> &vs,
			std::vector<cvector3d> &ve,
			cvector3d * dompts);
	public:
		/*
		 * @brief 求解3d泊松方程生成参数空间
		 * @param[out] dompts 曲面信息，需要外部开辟空间
		 */
		void tfiVolume(GridSolver& src);
	};
}

#endif