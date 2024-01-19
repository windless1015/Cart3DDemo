#include "foxspheresource.h"

#include <iostream>


using namespace Cart3D;

const double PI = 3.1415926;

FoxSphereSource::FoxSphereSource():m_latitude(15),m_longitude(15),m_radius(2.5f)
{
	m_center = OpenTriMesh::Point(0.0, 0.0, 0.0);
}

FoxSphereSource::~FoxSphereSource()
{
}

void FoxSphereSource::setRadius(double radius)
{
	m_radius = radius;
}

void FoxSphereSource::setCenter(double x, double y, double z)
{
	m_center = OpenTriMesh::Point(x, y, z);
}

void FoxSphereSource::setLatitude(int latitude)
{
	m_latitude = latitude;
}

void FoxSphereSource::setLongitude(int logitude)
{
	m_longitude = logitude;
}

bool FoxSphereSource::getSphereMesh(Cart3D::OpenTriMesh& mesh)
{
	
	if (m_latitude < 2 || m_longitude < 3)
	{
		std::cout<< "m_latitudeӦ����1��longtudeӦ����2" << std::endl;
		return false;
	}
    int count = m_longitude * (m_latitude - 1) + 2; //������
    OpenTriMesh::VertexHandle* vhandle = new OpenTriMesh::VertexHandle[count];
    int k = 0;

    vhandle[k] = mesh.add_vertex(m_center + OpenTriMesh::Point(0, 0, m_radius)); //���Ϸ�����
    for (auto j = 1; j < m_latitude; j++)
    {
        double cos1 = cos(j * PI / m_latitude);
        double sin1 = sin(j * PI / m_latitude);
        for (auto i = 0; i < m_longitude; i++)
        {
            ++k;
            //��Ӷ���
            vhandle[k] = mesh.add_vertex(m_center +
                OpenTriMesh::Point(m_radius * sin1 * cos(2 * i * PI / m_longitude),  //x
                    m_radius * sin1 * sin(2 * i * PI / m_longitude),  //y
                    m_radius * cos1));                              //z
        }
    }
    vhandle[++k] = mesh.add_vertex(m_center + OpenTriMesh::Point(0, 0, -m_radius)); //���·�����

    std::vector<OpenTriMesh::VertexHandle>face_vhandles;

    //�м䲿�ֵ�������
    for (auto j = 1; j < (m_latitude - 1); j++)
    {
        for (auto i = 0; i < m_longitude; i++)
        {
            int topLeft = (j - 1) * m_longitude + i + 1;
            int topRight = (j - 1) * m_longitude + (i + 1) % m_longitude + 1;
            int bottomLeft = j * m_longitude + i + 1;
            int bottomRight = j * m_longitude + (i + 1) % m_longitude + 1;

            face_vhandles.clear();
            face_vhandles.push_back(vhandle[topLeft]);
            face_vhandles.push_back(vhandle[bottomLeft]);
            face_vhandles.push_back(vhandle[bottomRight]);
            mesh.add_face(face_vhandles);

            face_vhandles.clear();
            face_vhandles.push_back(vhandle[bottomRight]);
            face_vhandles.push_back(vhandle[topRight]);
            face_vhandles.push_back(vhandle[topLeft]);
            mesh.add_face(face_vhandles);
            
        }
    }

    //���Ϸ�������
    for (auto j = 1; j < m_longitude; j++)
    {
        face_vhandles.clear();
        face_vhandles.push_back(vhandle[0]);
        face_vhandles.push_back(vhandle[j]);
        face_vhandles.push_back(vhandle[j + 1]);
        mesh.add_face(face_vhandles);
    }
    face_vhandles.clear();
    face_vhandles.push_back(vhandle[0]);
    face_vhandles.push_back(vhandle[m_longitude]);
    face_vhandles.push_back(vhandle[1]);
    mesh.add_face(face_vhandles);

    //���·�������
    for (auto j = 1; j < m_longitude; j++)
    {
        face_vhandles.clear();
        face_vhandles.push_back(vhandle[k]);
        face_vhandles.push_back(vhandle[k - j]);
        face_vhandles.push_back(vhandle[k - j - 1]);
        mesh.add_face(face_vhandles);
    }
    face_vhandles.clear();
    face_vhandles.push_back(vhandle[k]);
    face_vhandles.push_back(vhandle[k - m_longitude]);
    face_vhandles.push_back(vhandle[k - 1]);
    mesh.add_face(face_vhandles);

	return true;
}
