#pragma once

// c++
#include <vector>

// cart3D
#include <Util/OpenMeshUtil.h>

/**
 * @brief FoxPolyData 类主要是保存顶点数据.
 *  主要是将Cart3D中的OpenTriMesh转化为std::vector<float> 数据
 *	后面研究一下openmesh的半边 线 面片 其他的属性都可以将其保存到FoxPolyData类中
 *  现在暂时用于保存顶点
 */
class FoxPolyData
{
public:
	FoxPolyData(Cart3D::OpenTriMesh& mesh);
	// 获取网格
	Cart3D::OpenTriMesh getMesh();

	// 获取网格完整的顶点数据
	std::vector<float>&  getMeshVertexData();

	// 获取网格完整的顶点数据的长度
	int getMeshVertexDataSize();

private:
	// 将网格转化为原始顶点数据
	void meshToVertexData();

	// openmesh 计算法线
	void calcuatingNormal();

private:
	Cart3D::OpenTriMesh m_mesh; // 网格数据
	std::vector<float> m_meshVertexData; // 网格完整的顶点数据

};
