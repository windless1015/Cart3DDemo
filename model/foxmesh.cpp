#include "foxmesh.h"


#include <common/Sys/Logger.h>



FoxMesh::FoxMesh(std::vector<float> vertexData,QOpenGLShaderProgram* shaderProgram)
{
	initializeOpenGLFunctions();
    m_vertexData = vertexData;
	m_shaderProgram = shaderProgram;
	setupMesh(); 
}

FoxMesh::~FoxMesh()
{
	m_VBO.destroy();
	m_VAO.destroy();
}

void FoxMesh::darw(QOpenGLShaderProgram* shaderProgram)
{
	QOpenGLVertexArrayObject::Binder vaoBinder(&m_VAO);
	//m_VAO.bind();
	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size());
	//m_VAO.release();

}

void FoxMesh::setupMesh()
{
	

	QOpenGLVertexArrayObject::Binder vaoBinder(&m_VAO);

	m_VBO.create();
	m_VBO.bind();

	m_VBO.allocate(m_vertexData.data(), m_vertexData.size()*sizeof(float));

	m_shaderProgram->setAttributeBuffer("aPos", GL_FLOAT, 0, 3, 8 * sizeof(float));
	m_shaderProgram->enableAttributeArray("aPos");
	m_shaderProgram->setAttributeBuffer("aNormal", GL_FLOAT, sizeof(float) * 3, 3, 8 * sizeof(float));
	m_shaderProgram->enableAttributeArray("aNormal");
	m_shaderProgram->setAttributeBuffer("aTexCoords", GL_FLOAT, sizeof(float) * 6, 2, 8 * sizeof(float));
	m_shaderProgram->enableAttributeArray("aTexCoords");

	m_VBO.release();
    //m_shaderProgram->release();
	//m_VAO.release();
}


