#pragma once


#include <QtMath>
#include <QVector3D>
#include <QObject>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// �����
class FoxCamera:public QObject 
{

public:
	FoxCamera();
	~FoxCamera();

	// ���������λ��
	void setPosition(QVector3D position);

	// ����ŷ���Ǻ�lookat����������ͼ����
	QMatrix4x4 getViewMatrix();

	// �������������
	void updateCameraVectors();

private:
	// ���������
	QVector3D m_position;
	QVector3D m_front;
	QVector3D m_up;
	QVector3D m_right;
	QVector3D m_worldUP;

	// ŷ����
	float m_yaw;
	float m_pitch;

	// �����ͷѡ��
	float m_movementSpeed;
	float m_mouseSensitivity;
	float m_zoom;

};
