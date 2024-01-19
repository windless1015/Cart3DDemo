#pragma once

// c++
#include <memory>
// qt
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QVector3D>
/**
 * @brief FoxOpenGLPolyDataMapper 主要是将顶点数据映射到VBO中.
 * 围绕着这个开始渲染, 最终的渲染其实是在这个类中完成
 */
class FoxPolyData;
class FoxShaderProgram;
class FoxOpenGLPolyDataMapper :public QOpenGLFunctions
{
public:
	FoxOpenGLPolyDataMapper();
	~FoxOpenGLPolyDataMapper();

	// 设置顶点数据
	void setPolyData(std::shared_ptr<FoxPolyData> polyData);

	// 绑定VAO 绘制时需要bind VAO
	void bindVAO();
	// 释放VAO
	void releaseVAO();
	// 释放VBO
	void releaseVBO();
	// 渲染
	void renderer();
	// 绑定VBO数据
	void bindVertexBuffObject(std::shared_ptr<FoxShaderProgram> shaderProgram);


private:
	QOpenGLBuffer m_VBO;  // 顶点缓存
	QOpenGLVertexArrayObject m_VAO; // 顶点数组
	std::shared_ptr<FoxPolyData> m_polydata; // 顶点数据
	std::shared_ptr<FoxShaderProgram> m_shaderProgram;
};
