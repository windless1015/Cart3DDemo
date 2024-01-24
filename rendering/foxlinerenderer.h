#pragma once


#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QVector>


/**
 * @brief �Զ����������Ⱦ��.
 */
class FoxLineRenderer: public QOpenGLFunctions
{
public:
	// ����һȦ����ķ�Χ ������һȦ����
	FoxLineRenderer();

	// ���ö���
	void setVector(const QVector<QVector3D>& controlPoints);
	// ����VAO VBO
	void initialize();

	// ��Ⱦ
	void render();
private:
	QVector<QVector3D> m_controlPoints;
	QOpenGLVertexArrayObject m_VAO;
	QOpenGLBuffer m_VBO;
	bool m_visiblity; // �ɼ���
};


