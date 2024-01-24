#pragma once


#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QVector>


/**
 * @brief 自定义的线条渲染器.
 */
class FoxLineRenderer: public QOpenGLFunctions
{
public:
	// 传入一圈顶点的范围 将绘制一圈的线
	FoxLineRenderer();

	// 设置顶点
	void setVector(const QVector<QVector3D>& controlPoints);
	// 设置VAO VBO
	void initialize();

	// 渲染
	void render();
private:
	QVector<QVector3D> m_controlPoints;
	QOpenGLVertexArrayObject m_VAO;
	QOpenGLBuffer m_VBO;
	bool m_visiblity; // 可见性
};


