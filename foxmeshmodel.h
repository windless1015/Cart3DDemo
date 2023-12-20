#pragma once

#define _USE_MATH_DEFINES
// openmesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

// cart3D
#include <Util/OpenMeshUtil.h>


/// <summary>
///  ����������ģ�� 
///  �����и� �и�
/// </summary>
class FoxMeshModel
{
public:
	FoxMeshModel();
	~FoxMeshModel();
	// ͨ���ļ�·����������ģ��
	void setMeshFilePath(const std::string& meshFilePath);
	// ��ȡ����
	Cart3D::OpenTriMesh getMesh();
	// ��ȡ����Ķ�������
	std::vector<float> getMeshVertexs();

	// �����и��㷨������, ���������������
	void cuttingMesh();
	// ��ȡ�и������
	Cart3D::OpenTriMesh getCutMesh();
	// ��ȡ���и�����
	Cart3D::OpenTriMesh getBeCutMesh();

protected:
	// ����������ת���ɶ�������
	std::vector<float> meshDataToVertexData(Cart3D::OpenTriMesh mesh);

private:
	Cart3D::OpenTriMesh m_mesh; // ��ȡ����������

	Cart3D::OpenTriMesh m_beCutMesh; // 
	Cart3D::OpenTriMesh m_cutMesh;// 
};

