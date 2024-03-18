#pragma once


#include <QMatrix4x4>
#include <QVector3D>
#include <QQuaternion>
#include <QMessageBox>

#include <QOpenGLTexture>
/**
 * @brief Actor类主要是负责模型属性的设置.
 * 比如说模型的矩阵变换，模型的颜色修改等相关的渲染设置
 */
class QObject;
class FoxOpenGLPolyDataMapper;
class FoxCamera;
class FoxShaderProgram;
class FoxActor 
{
public:
	FoxActor(QObject* parent);
	~FoxActor();
	// 设置映射的mapper
	void setPolyDataMapper(std::shared_ptr<FoxOpenGLPolyDataMapper> polyDataMapper);
	std::shared_ptr<FoxOpenGLPolyDataMapper> getPolyDataMapper();

	//设置变换矩阵
	void FoxActor::setTransform(QMatrix4x4& transformMatrix, QVector3D& qv3d);

	// 设置颜色
	void setColor(float r, float g, float b,float alpha=1.0f);
	QVector3D getColor();

	// 设置位置
	void setActorPosition(QVector3D& position);
	
	// 是否可见 true 可见 false 不可见
	void setVisibility(bool visibility);

	// 设置投影矩阵
	void setProjection(const QMatrix4x4& projection);
	void setProjection(float zoom, float width, float hight, float nearPlane, float farPlane);
	QMatrix4x4& getProjection();

	// 设置模型矩阵 变换 缩放 旋转
	void setModel(const QMatrix4x4& model);
	void setModelTranslation(QVector3D& position);
	void setModelScale(float factor);
	void setModelRotate(QQuaternion& rotateQuat);
	QMatrix4x4& getModel();

	// 设置视图矩阵 旋转视图矩阵
	void setView(const QMatrix4x4& view);
	void setView(std::shared_ptr<FoxCamera> camera);
	void setViewRotate(QQuaternion& rotateQuat);
	QMatrix4x4& getView();

	// 更新actor的着色器数据
	void updataShaderProgram();
	std::shared_ptr<FoxShaderProgram> getShaderProgram();

	// 设置顶点缓存属性
	void setVertexBuffe();

	// 绘制
	void draw();

private:
	QQuaternion m_rotateQuat;// 用于旋转的四元数
	QMatrix4x4 m_model; // 模型矩阵
	QMatrix4x4 m_projection; // 投影矩阵
	QMatrix4x4 m_view; // 视图矩阵
	QVector3D m_actorPosition; // 位置
	std::shared_ptr<FoxOpenGLPolyDataMapper> m_polyDataMapper; // 数据映射
	std::shared_ptr<FoxShaderProgram> m_shaderProgarm; // 着色器
	float m_zoom; 
	float m_aspectRatio; // 屏占比
	float m_nearPlane;
	float m_farPlane;
	bool m_useTexture; // 是否使用材质
	bool m_actorVisibility; // 可见性
	QVector3D m_color; //颜色


};
