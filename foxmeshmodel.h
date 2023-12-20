#pragma once

#define _USE_MATH_DEFINES
// openmesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

// cart3D
#include <Util/OpenMeshUtil.h>


/// <summary>
///  负责处理网格模型 
///  包括切割 切割
/// </summary>
class FoxMeshModel
{
public:
	FoxMeshModel();
	~FoxMeshModel();
	// 通过文件路径设置网格模型
	void setMeshFilePath(const std::string& meshFilePath);
	// 获取网格
	Cart3D::OpenTriMesh getMesh();
	// 获取网格的顶点数组
	std::vector<float> getMeshVertexs();

	// 测试切割算法的例子, 最后生成两个网格
	void cuttingMesh();
	// 获取切割的网格
	Cart3D::OpenTriMesh getCutMesh();
	// 获取被切割网格
	Cart3D::OpenTriMesh getBeCutMesh();

protected:
	// 将网格数据转化成顶点数组
	std::vector<float> meshDataToVertexData(Cart3D::OpenTriMesh mesh);

private:
	Cart3D::OpenTriMesh m_mesh; // 读取出来的网格

	Cart3D::OpenTriMesh m_beCutMesh; // 
	Cart3D::OpenTriMesh m_cutMesh;// 
};

