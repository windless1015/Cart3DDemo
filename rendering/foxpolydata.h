#pragma once

// c++
#include <vector>

// cart3D
#include <Util/OpenMeshUtil.h>

/**
 * @brief FoxPolyData ����Ҫ�Ǳ��涥������.
 *  ��Ҫ�ǽ�Cart3D�е�OpenTriMeshת��Ϊstd::vector<float> ����
 *	�����о�һ��openmesh�İ�� �� ��Ƭ ���������Զ����Խ��䱣�浽FoxPolyData����
 *  ������ʱ���ڱ��涥��
 */
class FoxPolyData
{
public:
	FoxPolyData(Cart3D::OpenTriMesh& mesh);
	// ��ȡ����
	Cart3D::OpenTriMesh getMesh();

	// ��ȡ���������Ķ�������
	std::vector<float>&  getMeshVertexData();

	// ��ȡ���������Ķ������ݵĳ���
	int getMeshVertexDataSize();

private:
	// ������ת��Ϊԭʼ��������
	void meshToVertexData();

	// openmesh ���㷨��
	void calcuatingNormal();

private:
	Cart3D::OpenTriMesh m_mesh; // ��������
	std::vector<float> m_meshVertexData; // ���������Ķ�������

};
