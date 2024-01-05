#pragma once

#define _USE_MATH_DEFINES
// openmesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

//qt
#include <QOpenGLShaderProgram>

// cart3D
#include <Util/OpenMeshUtil.h>

/// <summary>
///  负责处理网格模型 
///  包括切割 切割
/// </summary>
class FoxMesh;
class FoxMeshModel
{
	typedef std::shared_ptr<FoxMesh> sptr_FoxMesh;
public:
	FoxMeshModel();
	~FoxMeshModel();
	// 通过文件路径设置网格模型
	void setMeshFileName(const std::string& meshFileName);
	// 通过文件夹路径设置多个网格模型
	void setMeshFileFolder(const std::string& meshFolderPath);
	// 测试切割算法的例子, 最后生成两个网格
	void cuttingMesh();

	// 加载网格(绘制网格)
	void loadMesh(QOpenGLShaderProgram* shader);
	// 添加网格
	void addMesh(QOpenGLShaderProgram* shader);


	// 模型是否可见 true可见 false 不可见
	void setVisible(bool isVisible);

private:
	// 将网格数据转化成顶点数组
	std::vector<float> meshDataToVertexData(Cart3D::OpenTriMesh &mesh);
	// 将文件路径转化为openmesh的网格
	Cart3D::OpenTriMesh fileNameToMeshData(const std::string& fileName);
	// 计算法线
	void setMeshNormals(Cart3D::OpenTriMesh& mesh);

private:
	bool m_isVisible;
	Cart3D::OpenTriMesh m_mesh; // 读取出来的网格

	Cart3D::OpenTriMesh m_beCutMesh; 
	Cart3D::OpenTriMesh m_cutMesh;
	
	std::vector<sptr_FoxMesh> m_foxMeshs;
	std::vector<Cart3D::OpenTriMesh> m_openTriMeshs;

	std::vector<sptr_FoxMesh> m_cuttingFoxMeshs;
	std::vector<Cart3D::OpenTriMesh> m_cuttingMeshs;


	QOpenGLShaderProgram* m_shaderProgram;
};

