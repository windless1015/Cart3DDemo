
#include "foxopenglpolydatamapper.h"
#include"foxpolydata.h"
#include "foxshaderprogram.h"
FoxOpenGLPolyDataMapper::FoxOpenGLPolyDataMapper():m_polydata(nullptr)
{
	initializeOpenGLFunctions();
}

FoxOpenGLPolyDataMapper::~FoxOpenGLPolyDataMapper()
{
}


void FoxOpenGLPolyDataMapper::setPolyData(std::shared_ptr<FoxPolyData> polyData)
{
	if (polyData == nullptr) return;
	m_polydata = polyData;
}

void FoxOpenGLPolyDataMapper::bindVAO()
{
	m_VAO.bind();
}

void FoxOpenGLPolyDataMapper::releaseVAO()
{
	m_VAO.release();
}

void FoxOpenGLPolyDataMapper::releaseVBO()
{
	m_VBO.release();
}

void FoxOpenGLPolyDataMapper::renderer()
{
	std::cout << "mapper绘制----------->\n";
	// 绑定VAO 绘制
	QOpenGLVertexArrayObject::Binder vaoBinder(&m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_polydata->getMeshVertexDataSize());
}

void FoxOpenGLPolyDataMapper::bindVertexBuffObject(std::shared_ptr<FoxShaderProgram> shaderProgram)
{
	QOpenGLVertexArrayObject::Binder vaoBinder(&m_VAO);
	m_VBO.create();
	m_VBO.bind();
	// 将顶点数据传递给vbo
	std::vector<float> vertexData = m_polydata->getMeshVertexData();
	m_VBO.allocate(vertexData.data(), vertexData.size() * sizeof(float));
	shaderProgram->setVertexAttributeBuffe("aPos", 0, 3, 8 * sizeof(float));
	shaderProgram->setVertexAttributeBuffe("aNormal", sizeof(float) * 3, 3, 8 * sizeof(float));
	shaderProgram->setVertexAttributeBuffe("aPos", 0, 3, 8 * sizeof(float));
}
