#pragma once

#define _USE_MATH_DEFINES
// openmesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

// cart3D
#include <Util/OpenMeshUtil.h>


/// <summary>
///  网格数据模型
/// </summary>
class FoxMeshModel
{
public:
	FoxMeshModel();
	~FoxMeshModel();
	// 通过文件路径设置网格模型
	void setMesh(std::string_view meshFilePath);
	Cart3D::OpenTriMesh getMesh();

	// 测试切割算法的例子, 最后生成两个网格
	void cuttingMesh();
	// 获取切割的网格
	Cart3D::OpenTriMesh getCutMesh() { return m_cutMesh; }
	// 获取被切割网格
	Cart3D::OpenTriMesh getBeCutMesh() { return m_beCutMesh; }

private:
	Cart3D::OpenTriMesh m_mesh;

	Cart3D::OpenTriMesh m_beCutMesh; // 
	Cart3D::OpenTriMesh m_cutMesh;
};

