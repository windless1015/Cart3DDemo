
#include "foxpolydata.h"


#include <qmath.h>

FoxPolyData::FoxPolyData(Cart3D::OpenTriMesh& mesh):m_mesh(mesh)
{
    // ���㷨����ȷ����ȡ������ʱ����ȷ��ȡ
    calcuatingNormal();
	// ������ת����������
	meshToVertexData();
}

Cart3D::OpenTriMesh FoxPolyData::getMesh()
{
	return m_mesh;
}

std::vector<float>& FoxPolyData::getMeshVertexData()
{
    return m_meshVertexData;
}


// ��ȡ�������������Ķ������ݳ���
int FoxPolyData::getMeshVertexDataSize()
{
    int size = m_meshVertexData.size();
    return size;
}

void FoxPolyData::meshToVertexData()
{
	for (Cart3D::OpenTriMesh::FaceIter f_it = m_mesh.faces_begin(); f_it != m_mesh.faces_end(); ++f_it)
	{
		// ������Ƭ�ϵĶ���
		for (Cart3D::OpenTriMesh::FaceVertexIter fv_it = m_mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
		{

			// ��ȡÿ����Ƭ�ϵĵ�
			auto& point = m_mesh.point(*fv_it);
			// ��ȡ������
			auto& normal = m_mesh.normal(*fv_it);
			m_meshVertexData.push_back(point[0]);
			m_meshVertexData.push_back(point[1]);
			m_meshVertexData.push_back(point[2]);

			// ��ӷ�����
			m_meshVertexData.push_back(normal[0]);
			m_meshVertexData.push_back(normal[1]);
			m_meshVertexData.push_back(normal[2]);
			// �����������
			float u = (qAtan2(normal[1], normal[0]) / (2 * M_PI));
			float v = (qAsin(normal[2]) / M_PI);
			if (u < 0.0) u *= -1.0;
			if (v < 0.0) v *= -1.0;
			m_meshVertexData.push_back(u);
			m_meshVertexData.push_back(v);
		}
	}

}

void FoxPolyData::calcuatingNormal()
{
    // ���󶥵㷨����
    m_mesh.request_vertex_normals();
    if (!m_mesh.has_vertex_normals()) {
        std::cout << "��ȡ�������쳣!!!!\n";
        return;
    };
    // ���㷨����
    m_mesh.request_face_normals();
    m_mesh.update_normals();
    m_mesh.release_face_normals();

}


