#pragma once




#include <qopenglfunctions.h>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QObject>
// �ƹ���
// �ƹ������е�����
// 1. �ƹ��Լ�����ɫ��
// 2. �ƹ��λ��
// 3. �ƹ��ģ�Ͷ���(������Ǹ��򵥵ĺ���)


class FoxLighting:public QObject, public QOpenGLFunctions
{

public:
	FoxLighting();
	~FoxLighting();
	/// <summary>
	///  ���õƹ��λ��
	/// </summary>
	/// <param name="position">����ƹ����άλ����Ϣ����Ĭ��ֵ</param>
	void setLightingPosition(QVector3D position=QVector3D(5.2f, 10.0f, 30.0f));
	
	/// <summary>
	///  ���õƹ������
	/// </summary>
	/// <param name="ambient">������Ӱ��ǿ��</param>
	/// <param name="diffuse">������Ӱ��ǿ��</param>
	/// <param name="specular">���淴���Ӱ��ǿ��</param>
	void setLightingProperties(QVector3D ambient,QVector3D diffuse,QVector3D specular);

	/// <summary>
	///  ���õƹ����Ⱦ����
	/// </summary>
	/// <param name="projection">ͶӰ����</param>
	/// <param name="view">�۲����</param>
	void setLightingMatrix4x4(QMatrix4x4 projection, QMatrix4x4 view);

	/// <summary>
	///  ���Ƶƹ�
	/// </summary>
	void drawLightingArrays();

private:
	// �ƹ�����
	QVector3D m_position;
	QVector3D m_ambient;
	QVector3D m_diffuse;
	QVector3D m_specular;

	// �ƹ�Ļ���
	QOpenGLBuffer m_lightingVBO;
	QOpenGLVertexArrayObject m_lightingVAO;
	QOpenGLShaderProgram* m_shaderProgram;

	

};

