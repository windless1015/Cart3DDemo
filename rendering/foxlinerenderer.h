#pragma once


#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QVector>
#include <QVector4D>

/**
 * @brief 自定义的线条渲染器.
 */
class FoxLineRenderer: public QOpenGLFunctions
{
public:
	// 传入一圈顶点的范围 将绘制一圈的线
	FoxLineRenderer();
	// 设置线条的宽度
	void setLineWidth(const float& width);
	// 设置线条颜色
	void setLineColor(float r,float g,float b,float alpha);
	// 设置缩放
	void setScale(const float& scale);
	// 设置变换
	void setTransformation(const float& x, const float& y);
	
	// 设置顶点
	void setVector(const QVector<QVector3D>& controlPoints);
	void setVector(const QVector<QVector2D>& point);
	QVector<QVector3D>& getVector();
	// 设置VAO VBO
	void initialize();

	// 渲染
	void render();
private:
	QVector<QVector3D> m_controlPoints;
	QOpenGLVertexArrayObject m_VAO;
	QOpenGLBuffer m_VBO;
	bool m_visiblity; // 可见性
	float m_lineWidth; // 线条的宽度
	QVector4D m_lineColor; // 线条颜色
	float m_scaleFactor; // 缩放
	QVector3D m_movePlace; 

};


