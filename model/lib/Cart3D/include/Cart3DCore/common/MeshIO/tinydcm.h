#ifndef CART3D_TINY_DCM_H
#define CART3D_TINY_DCM_H

#include <Cart3DCommonDefine.h>
#include <Util/EigenUtil.h>
namespace Cart3D
{

	struct CART3D_COMMON_CLASS CBCTVoxelData
	{
		std::vector<float> ori;
		std::vector<float> data; // voxel�ڴ�, [z * size[1] * size[0] + y * size[0] + x]
		std::vector<float> spacing; // voxel�����طֱ��ʣ�[x,y,z]
		std::vector<int> size; // voxel�ߴ磬[x,y,z]
		             
		CBCTVoxelData();
	};

	CART3D_COMMON_API bool load_dcm(const std::string& path, CBCTVoxelData& cbct);

}



#endif