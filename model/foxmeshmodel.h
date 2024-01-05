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
///  ����������ģ�� 
///  �����и� �и�
/// </summary>
class FoxMesh;
class FoxMeshModel
{
	typedef std::shared_ptr<FoxMesh> sptr_FoxMesh;
public:
	FoxMeshModel();
	~FoxMeshModel();
	// ͨ���ļ�·����������ģ��
	void setMeshFileName(const std::string& meshFileName);
	// ͨ���ļ���·�����ö������ģ��
	void setMeshFileFolder(const std::string& meshFolderPath);
	// �����и��㷨������, ���������������
	void cuttingMesh();

	// ��������(��������)
	void loadMesh(QOpenGLShaderProgram* shader);
	// �������
	void addMesh(QOpenGLShaderProgram* shader);


	// ģ���Ƿ�ɼ� true�ɼ� false ���ɼ�
	void setVisible(bool isVisible);

private:
	// ����������ת���ɶ�������
	std::vector<float> meshDataToVertexData(Cart3D::OpenTriMesh &mesh);
	// ���ļ�·��ת��Ϊopenmesh������
	Cart3D::OpenTriMesh fileNameToMeshData(const std::string& fileName);
	// ���㷨��
	void setMeshNormals(Cart3D::OpenTriMesh& mesh);

private:
	bool m_isVisible;
	Cart3D::OpenTriMesh m_mesh; // ��ȡ����������

	Cart3D::OpenTriMesh m_beCutMesh; 
	Cart3D::OpenTriMesh m_cutMesh;
	
	std::vector<sptr_FoxMesh> m_foxMeshs;
	std::vector<Cart3D::OpenTriMesh> m_openTriMeshs;

	std::vector<sptr_FoxMesh> m_cuttingFoxMeshs;
	std::vector<Cart3D::OpenTriMesh> m_cuttingMeshs;


	QOpenGLShaderProgram* m_shaderProgram;
};

