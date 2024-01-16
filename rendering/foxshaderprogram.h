#pragma once



// 着色器程序
// 简化着色器的使用,对qt着色器程序进行封装
// 有两种模式一种是默认的渲染效果 还有 添加纹理后的效果

class QOpenGLShaderProgram;
class QObject;
class QVector3D;
class QMatrix4x4;
class FoxShaderProgram
{
public:
	FoxShaderProgram(QObject* parent);
	~FoxShaderProgram();
	void shaderBind();
	void shaderRelease();
	

	void setObjectColor(float r,float g,float b);

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
	float m_objectColor[3];
};


