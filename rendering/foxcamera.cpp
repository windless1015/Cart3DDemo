#include "foxcamera.h"


#include <QMatrix4x4>


FoxCamera::FoxCamera(QVector3D position, QVector3D up,
	float yaw, float pitch):
	m_front(0.0f, 0.0f, -1.0f),m_movementSpeed(SPEED),m_mouseSensitivity(SENSITIVITY),m_zoom(ZOOM)
{
	m_position = position;
	m_worldUP = up;
	m_yaw = yaw;
	m_pitch = pitch;
	updateCameraVectors();
}

FoxCamera::~FoxCamera()
{
}

float FoxCamera::getCameraZoom()
{
	return m_zoom;
}

QVector3D FoxCamera::getPosition()
{
	return m_position;
}

void FoxCamera::setPosition(QVector3D position)
{
	m_position = position;
	//updateCameraVectors();
}

QMatrix4x4 FoxCamera::getViewMatrix() 
{
	QMatrix4x4 view;
	view.lookAt(m_position, m_position + m_front, m_up);
	return view;
}

void FoxCamera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{

	m_yaw += xoffset* m_mouseSensitivity;
	m_pitch += yoffset* m_mouseSensitivity;


	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;
	updateCameraVectors();
}



void FoxCamera::wheelScrollEvent(float yoffset)
{

	m_zoom -= yoffset;
	// ÏÞ¶¨·¶Î§
	if (m_zoom < 1.0f) {
		m_zoom = 1.0f;
	}
	if (m_zoom > 45.0f)
	{
		m_zoom = 45.0f;
	}

}

   

void FoxCamera::updateCameraVectors()
{
	QVector3D front;
	front.setX(qCos(qDegreesToRadians(m_yaw))*qCos(qDegreesToRadians(m_pitch)));
	front.setY(qSin(qDegreesToRadians(m_pitch)));
	front.setZ(qSin(qDegreesToRadians(m_yaw)) * qCos(qDegreesToRadians(m_pitch)));

	m_front = front.normalized();
	m_right=QVector3D::crossProduct(m_front, m_worldUP).normalized();
	m_up = QVector3D::crossProduct(m_right,m_front).normalized();
}
