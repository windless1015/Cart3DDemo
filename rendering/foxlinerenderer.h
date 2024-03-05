#pragma once


#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QVector>
#include <QVector4D>

/**
 * @brief �Զ����������Ⱦ��.
 */
class FoxLineRenderer: public QOpenGLFunctions
{
public:
	// ����һȦ����ķ�Χ ������һȦ����
	FoxLineRenderer();
	// ���������Ŀ��
	void setLineWidth(const float& width);
	// ����������ɫ
	void setLineColor(float r,float g,float b,float alpha);
	// ��������
	void setScale(const float& scale);
	// ���ñ任
	void setTransformation(const float& x, const float& y);
	
	// ���ö���
	void setVector(const QVector<QVector3D>& controlPoints);
	void setVector(const QVector<QVector2D>& point);
	QVector<QVector3D>& getVector();
	// ����VAO VBO
	void initialize();

	// ��Ⱦ
	void render();
private:
	QVector<QVector3D> m_controlPoints;
	QOpenGLVertexArrayObject m_VAO;
	QOpenGLBuffer m_VBO;
	bool m_visiblity; // �ɼ���
	float m_lineWidth; // �����Ŀ��
	QVector4D m_lineColor; // ������ɫ
	float m_scaleFactor; // ����
	QVector3D m_movePlace; 

};


