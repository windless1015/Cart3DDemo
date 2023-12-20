#include "foxcamera.h"


#include <QMatrix4x4>

FoxCamera::FoxCamera():
	m_position(0.0f, 0.0f, 0.0f),m_up(0.0f, 1.0f, 0.0f),m_yaw(YAW),m_pitch(PITCH),
	m_front(0.0f, 0.0f, -1.0f),m_movementSpeed(SPEED),m_mouseSensitivity(SENSITIVITY),m_zoom(ZOOM)
{
}

FoxCamera::~FoxCamera()
{
}

void FoxCamera::setPosition(QVector3D position)
{
	m_position = position;
}

QMatrix4x4 FoxCamera::getViewMatrix()
{
	QMatrix4x4 view;
	view.lookAt(m_position, m_position + m_front, m_up);
	return view;
}



void FoxCamera::updateCameraVectors()
{
	QVector3D front;
	front.setX(qCos(qRadiansToDegrees(m_yaw))*qCos(qRadiansToDegrees(m_pitch)));
	front.setY(qSin(m_pitch));
	front.setZ(qSin(qRadiansToDegrees(m_yaw)) * qCos(qRadiansToDegrees(m_pitch)));

	m_front = front;
	m_right=QVector3D::crossProduct(m_front, m_worldUP).normalized();
	m_up = QVector3D::crossProduct(m_right,m_front).normalized();
}
