#pragma once

#define _USE_MATH_DEFINES
// openmesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

// cart3D
#include <Util/OpenMeshUtil.h>


/// <summary>
///  ��������ģ��
/// </summary>
class FoxMeshModel
{
public:
	FoxMeshModel();
	~FoxMeshModel();
	// ͨ���ļ�·����������ģ��
	void setMesh(std::string_view meshFilePath);
	Cart3D::OpenTriMesh getMesh();

	// �����и��㷨������, ���������������
	void cuttingMesh();
	// ��ȡ�и������
	Cart3D::OpenTriMesh getCutMesh() { return m_cutMesh; }
	// ��ȡ���и�����
	Cart3D::OpenTriMesh getBeCutMesh() { return m_beCutMesh; }

private:
	Cart3D::OpenTriMesh m_mesh;

	Cart3D::OpenTriMesh m_beCutMesh; // 
	Cart3D::OpenTriMesh m_cutMesh;
};

