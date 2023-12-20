#pragma once




#include <qopenglfunctions.h>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QObject>
// 灯光类
// 灯光所具有的属性
// 1. 灯光自己的着色器
// 2. 灯光的位置
// 3. 灯光的模型顶点(这里就是个简单的盒子)


class FoxLighting:public QObject, public QOpenGLFunctions
{

public:
	FoxLighting();
	~FoxLighting();
	/// <summary>
	///  设置灯光的位置
	/// </summary>
	/// <param name="position">传入灯光的三维位置信息，有默认值</param>
	void setLightingPosition(QVector3D position=QVector3D(5.2f, 10.0f, 30.0f));
	
	/// <summary>
	///  设置灯光的属性
	/// </summary>
	/// <param name="ambient">环境光影响强度</param>
	/// <param name="diffuse">漫反射影响强度</param>
	/// <param name="specular">镜面反射的影响强度</param>
	void setLightingProperties(QVector3D ambient,QVector3D diffuse,QVector3D specular);

	/// <summary>
	///  设置灯光的渲染矩阵
	/// </summary>
	/// <param name="projection">投影矩阵</param>
	/// <param name="view">观察矩阵</param>
	void setLightingMatrix4x4(QMatrix4x4 projection, QMatrix4x4 view);

	/// <summary>
	///  绘制灯光
	/// </summary>
	void drawLightingArrays();

private:
	// 灯光属性
	QVector3D m_position;
	QVector3D m_ambient;
	QVector3D m_diffuse;
	QVector3D m_specular;

	// 灯光的绘制
	QOpenGLBuffer m_lightingVBO;
	QOpenGLVertexArrayObject m_lightingVAO;
	QOpenGLShaderProgram* m_shaderProgram;

	

};

