#include "foxlighting.h"



// �ƹ���ɫ����Դ���� 
// VS��ʾVertex Shader  ������ɫ��
// FS��ʾ Fragment Shader Ƭ����ɫ��
// ������ɫ��
const char* lightingShaderCode_VS = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

// Ƭ����ɫ��
const char* lightingShaderCode_FS = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0); 
}
)";

// ��������
float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

FoxLighting::FoxLighting()
{
	initializeOpenGLFunctions();
	// ������ɫ��
	QOpenGLShader* vertexShader = new QOpenGLShader(QOpenGLShader::Vertex,this);
	vertexShader->compileSourceCode(lightingShaderCode_VS);
	QOpenGLShader* fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	fragmentShader->compileSourceCode(lightingShaderCode_FS);

	// ������ɫ��������Ӱ�����
	m_shaderProgram = new QOpenGLShaderProgram;

	m_shaderProgram->addShader(vertexShader);
	m_shaderProgram->addShader(fragmentShader);

	m_shaderProgram->link();
	m_shaderProgram->bind();
	// vao vbo
	m_lightingVAO.create();
	m_lightingVAO.bind();

	m_lightingVBO.create();
	m_lightingVBO.bind();
	m_lightingVBO.allocate(vertices, sizeof(vertices));
	// ������ɫ����������
	m_shaderProgram->setAttributeBuffer("aPos",GL_FLOAT,0, 3, 6*sizeof(float));
	m_shaderProgram->enableAttributeArray("aPos");


	m_shaderProgram->release();
	m_lightingVAO.release();
}

FoxLighting::~FoxLighting()
{
	if (m_shaderProgram != nullptr) {
		delete m_shaderProgram;
		m_shaderProgram = nullptr;
	}
}

void FoxLighting::setLightingPosition(QVector3D position)
{
	m_position = position;
}

void FoxLighting::setLightingProperties(QVector3D ambient, QVector3D diffuse, QVector3D specular)
{
	m_shaderProgram->bind();
	m_shaderProgram->setUniformValue("ambient", ambient);
	m_shaderProgram->setUniformValue("diffuse", diffuse);
	m_shaderProgram->setUniformValue("specular", specular);

}

void FoxLighting::setLightingMatrix4x4(QMatrix4x4 projection, QMatrix4x4 view)
{
	m_shaderProgram->bind();
	m_shaderProgram->setUniformValue("projection", projection);
	m_shaderProgram->setUniformValue("view", view);
	QMatrix4x4 lightingModel;
	lightingModel.translate(m_position);
	lightingModel.scale(0.2f);
	m_shaderProgram->setUniformValue("view", lightingModel);
}

void FoxLighting::drawLightingArrays()
{
	m_shaderProgram->bind();
	m_lightingVAO.bind();
	
	glDrawArrays(GL_TRIANGLES, 0, 36);

}
