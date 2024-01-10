#pragma once


#include <QtMath>
#include <QVector3D>
#include <QObject>
#include <qopengl.h>
#include <QKeyEvent>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 4.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// �����
class FoxCamera:public QObject 
{

public:
	FoxCamera(QVector3D position=QVector3D(0.0f, 0.0f, 0.0f),QVector3D up=QVector3D(0.0f, 1.0f, 0.0f),
		float yaw=YAW,float pitch = PITCH);
	~FoxCamera();
	float getCameraZoom();
	QVector3D getPosition();
	// ���������λ��
	void setPosition(QVector3D position);
	// ����ŷ���Ǻ�lookat����������ͼ����
	QMatrix4x4 getViewMatrix();
	// ��������¼�
	void processMouseMovement(float xoffset, float yoffset,GLboolean constrainPitch =true);

	// �����������¼�
	void wheelScrollEvent(float yoffset);

protected:
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
