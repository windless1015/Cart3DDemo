#ifndef CART3D_GEN_GRID_UTIL_H
#define CART3D_GEN_GRID_UTIL_H

#include <Cart3DGenerationDefine.h>
#include <Util/EigenUtil.h>
#include <Util/BoostUtil.h>
#include <csgmesh/CSGMesh.h>

namespace Cart3D
{
	using cell = cvectort<std::uint32_t, 8>;
	enum class PosType :unsigned char
	{
		inner,
		outer,
		boundary
	};

	struct CART3D_GENERATION_CLASS GridParam
	{
		bool is_curvature_adaptive;  //是否曲率自适应
		bool is_feature_alignment;   //是否特征对齐
		bool is_pca_oobb;            //旋转背景网格
		bool is_use_virtual_mesh;    //是否使用虚拟背景网格
		bool is_anisotropy;          //是否生成各向异性网格


		std::uint8_t  smooth_layer;        //光滑层数
		std::uint8_t  max_depth_layer;     //最大剖分层数
		std::uint8_t  min_depth_layer;     //最小剖分层数
		std::uint8_t  init_split;           //最大细分尺寸 
		std::uint8_t  end_split;           //最小细分尺寸 
		std::uint8_t  far_p;               //远场的尺寸
		GridParam();
	};


}




#endif