#pragma once

#include <memory>

// cart3D
#include <Util/OpenMeshUtil.h>


/**
 * @brief ͨ����γ�ȵķ�ʽ������һ������.
 */
class FoxPolyData;
class FoxSphereSource
{
public:
	FoxSphereSource();
	~FoxSphereSource();
	/// <summary>
	/// ����Բ�İ뾶
	/// </summary>
	/// <param name="radius">�뾶</param>
	void setRadius(double radius);

	/// <summary>
	/// ����Բ������
	/// </summary>
	/// <param name="x">����</param>
	/// <param name="y">����</param>
	/// <param name="z">����</param>
	void setCenter(double x,double y,double z);

	/// <summary>
	/// �����������γ��
	/// </summary>
	/// <param name="latitude">γ��</param>
	void setLatitude(int latitude);

	/// <summary>
	///  ������������񾭶�
	/// </summary>
	/// <param name="logitude">����</param>
	void setLongitude(int logitude);

	/// <summary>
	///  ��ȡ���ɵ���������
	/// </summary>
	/// <param name="mesh">����</param>
	/// <returns>true ���ɳɹ� false ����ʧ��</returns>
	bool getSphereMesh(Cart3D::OpenTriMesh &mesh);

	/// <summary>
	///  ��ȡ���������
	/// </summary>
	/// <returns> ���ض��������FoxPolyData </returns>
	std::shared_ptr<FoxPolyData> getOutputPolyData();

private:
	double m_radius; // �뾶
	Cart3D::OpenTriMesh::Point m_center; // Բ��
	Cart3D::OpenTriMesh m_mesh;// ����
	int m_latitude;  // ���γ��
	int m_longitude;  //  ��ľ���
	std::shared_ptr<FoxPolyData> m_polyData; // ���������
};

