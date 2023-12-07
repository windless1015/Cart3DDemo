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
		bool is_curvature_adaptive;  //�Ƿ���������Ӧ
		bool is_feature_alignment;   //�Ƿ���������
		bool is_pca_oobb;            //��ת��������
		bool is_use_virtual_mesh;    //�Ƿ�ʹ�����ⱳ������
		bool is_anisotropy;          //�Ƿ����ɸ�����������


		std::uint8_t  smooth_layer;        //�⻬����
		std::uint8_t  max_depth_layer;     //����ʷֲ���
		std::uint8_t  min_depth_layer;     //��С�ʷֲ���
		std::uint8_t  init_split;           //���ϸ�ֳߴ� 
		std::uint8_t  end_split;           //��Сϸ�ֳߴ� 
		std::uint8_t  far_p;               //Զ���ĳߴ�
		GridParam();
	};


}




#endif