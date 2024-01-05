#pragma once

//c++
#include <vector>

// cart3D
#include <Util/OpenMeshUtil.h>

// qt 
#include <qopenglfunctions.h>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QObject>
#include <QOpenGLShaderProgram>

// ������
class FoxMesh : public QOpenGLFunctions
{
public:
	FoxMesh(std::vector<float> vertexData, QOpenGLShaderProgram* shaderProgram);
	~FoxMesh();

	// ��������ģ��
	void darw(QOpenGLShaderProgram* shaderProgram);

private:
	void setupMesh();

private:
	std::vector<float> m_vertexData;
	QOpenGLBuffer m_VBO;
	QOpenGLVertexArrayObject m_VAO;
	QOpenGLShaderProgram* m_shaderProgram;


};

