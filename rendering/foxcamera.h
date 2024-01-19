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

// 相机类
class FoxCamera:public QObject 
{

public:
	FoxCamera(QVector3D position=QVector3D(0.0f, 0.0f, 0.0f),QVector3D up=QVector3D(0.0f, 1.0f, 0.0f),
		float yaw=YAW,float pitch = PITCH);
	~FoxCamera();
	float getCameraZoom();
	QVector3D getPosition();
	// 设置相机的位置
	void setPosition(QVector3D position);
	// 返回欧拉角和lookat矩阵计算的视图矩阵
	QMatrix4x4 getViewMatrix();
	// 处理鼠标事件
	void processMouseMovement(float xoffset, float yoffset,GLboolean constrainPitch =true);

	// 处理鼠标滚轮事件
	void wheelScrollEvent(float yoffset);

protected:
	// 更新相机的向量
	void updateCameraVectors();

private:
	// 相机的属性
	QVector3D m_position;
	QVector3D m_front;
	QVector3D m_up;
	QVector3D m_right;
	QVector3D m_worldUP;

	// 欧拉角
	float m_yaw;
	float m_pitch;

	// 相机镜头选项
	float m_movementSpeed;
	float m_mouseSensitivity;
	float m_zoom;

};
