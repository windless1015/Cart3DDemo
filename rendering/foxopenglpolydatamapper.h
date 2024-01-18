#pragma once

// c++
#include <memory>
// qt
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QVector3D>
/**
 * @brief FoxOpenGLPolyDataMapper ��Ҫ�ǽ���������ӳ�䵽VBO��.
 * Χ���������ʼ��Ⱦ, ���յ���Ⱦ��ʵ��������������
 */
class FoxPolyData;
class FoxShaderProgram;
class FoxOpenGLPolyDataMapper :public QOpenGLFunctions
{
public:
	FoxOpenGLPolyDataMapper();
	~FoxOpenGLPolyDataMapper();

	// ���ö�������
	void setPolyData(std::shared_ptr<FoxPolyData> polyData);

	// ��VAO ����ʱ��Ҫbind VAO
	void bindVAO();
	// �ͷ�VAO
	void releaseVAO();
	// �ͷ�VBO
	void releaseVBO();
	// ��Ⱦ
	void renderer();
	// ��VBO����
	void bindVertexBuffObject(std::shared_ptr<FoxShaderProgram> shaderProgram);


private:
	QOpenGLBuffer m_VBO;  // ���㻺��
	QOpenGLVertexArrayObject m_VAO; // ��������
	std::shared_ptr<FoxPolyData> m_polydata; // ��������
	std::shared_ptr<FoxShaderProgram> m_shaderProgram;
};
