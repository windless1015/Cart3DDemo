#pragma once


#include <memory>
#include <QString>
// 着色器程序
// 简化着色器的使用,对qt着色器程序进行封装
// 有两种模式一种是默认的渲染效果 还有 添加纹理后的效果
class QOpenGLShaderProgram;
class QOpenGLTexture;
class QObject;
class QString;
class QVector3D;
class QMatrix4x4;
class FoxLighting;
class FoxShaderProgram
{
public:
	FoxShaderProgram(QObject* parent);
	~FoxShaderProgram();
	// 绑定着色器
	void shaderBind();
	// 释放着色器
	void shaderRelease();
	// 设置物体颜色
	void setObjectColor(float r,float g,float b,float alpha=1.0f);
	// 设置矩阵
	void setMatrix4x4(QMatrix4x4& projection, QMatrix4x4& view, QMatrix4x4& model);
	// 是否使用材质 true 使用  false 不使用
	void setUseMaterial(bool useMaterial);
	void setMaterialPath(const QString& texturePath);
	void initTexture();
	void textureBind();
	// 设置灯光
	void setLighting(std::shared_ptr<FoxLighting> lighting);
	// 设置属性缓存
	void setVertexAttributeBuffe(const char* name, int offset, int tupleSize, int stride = 0);
	// 设置观察角度
	void setViewPosition(QVector3D& viewPosition);
	/// <summary>
	///  在渲染时执行着色器
	/// </summary>
	/// <param name="useMaterial">是否使用材质 true是 false否</param>
	/// <param name="viewPosition">观察的位置</param>
	/// <param name="projection">投影矩阵</param>
	/// <param name="view">视图矩阵</param>
	/// <param name="model">模型矩阵</param>
	void useShaderProgram(bool useMaterial,QVector3D& viewPosition,QMatrix4x4& projection,QMatrix4x4& view,QMatrix4x4& model);

	QOpenGLShaderProgram* getShaderProgram();
	void setShaderProgram(QOpenGLShaderProgram* shaderProgram);

private:
	// 着色器程序
	QOpenGLShaderProgram* m_shaderProgram;
	// 物体颜色
	float m_objectColor[4];
	QOpenGLTexture* m_texture;
	QString m_texturePath;
	bool m_useTexture;
};


