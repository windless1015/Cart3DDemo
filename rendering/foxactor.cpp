#include "foxactor.h"
#include "foxshaderprogram.h"
#include "foxopenglpolydatamapper.h"
#include "foxcamera.h"

#include <iostream>
#include <QObject>

FoxActor::FoxActor(QObject* parent):m_zoom(45.0f),m_nearPlane(0.1f),m_farPlane(100.0f)
{
	
	// 屏占比默认
	m_aspectRatio = (float)800 / (float)600;
	m_shaderProgarm = std::make_shared<FoxShaderProgram>(parent);
	// 设置模型矩阵和投影矩阵
	//QVector3D viewPos = QVector3D(0.0, 0.0, -40.0f);
	//m_view.translate(viewPos);
	//m_view.scale(0.4);
	m_model.translate(QVector3D(0.0, 0.0, -30.0f));
	m_model.scale(0.3f);
	m_projection.perspective(m_zoom, m_aspectRatio, m_nearPlane, m_farPlane);
	m_shaderProgarm->setUseMaterial(false);
	m_shaderProgarm->setObjectColor(0.5f, 0.5f, 0.5f);
	// actor 是否可见
	m_actorVisibility = true;
	m_useTexture = false;
}

FoxActor::~FoxActor()
{

}

void FoxActor::setPolyDataMapper(std::shared_ptr<FoxOpenGLPolyDataMapper> polyDataMapper)
{
	// 设置对应的顶点属性
	m_polyDataMapper = polyDataMapper;
	m_polyDataMapper->bindVertexBuffObject(m_shaderProgarm);
}

std::shared_ptr<FoxOpenGLPolyDataMapper> FoxActor::getPolyDataMapper()
{
	return m_polyDataMapper;
}

void FoxActor::setColor(float r, float g, float b, float alpha)
{
	m_shaderProgarm->shaderBind();
	m_color = QVector3D(r, g, b);
	m_shaderProgarm->setObjectColor(r, g, b, alpha);
}

QVector3D FoxActor::getColor()
{
	return m_color;
}

void FoxActor::setActorPosition(QVector3D& position)
{
	m_actorPosition = position;
}

void FoxActor::setVisibility(bool visibility)
{
	m_actorVisibility = visibility;
}

/// <summary>
///   使用纹理
/// </summary>
/// <param name="useTexture">输入true 使用 false 不使用</param>
void FoxActor::setUseTexture(bool useTexture)
{
	// 设置为true之前先要判断是否已经初始化材质了
	// 这里是否应该是返回异常
	if (m_texturePath.isEmpty()) return;
	m_useTexture = useTexture;
	m_shaderProgarm->setUseMaterial(m_useTexture);
}

/// <summary>
///  设置材质的图片路径
/// </summary>
/// <param name="textureName">材质的图片路径</param>
void FoxActor::setTexture(const QString& textureName)
{
	m_texturePath = textureName;
	m_shaderProgarm->setMaterialPath(m_texturePath);
	m_shaderProgarm->initTexture();
}

void FoxActor::setProjection(const QMatrix4x4& projection)
{
	m_projection = projection;
}

void FoxActor::setProjection(float zoom, float width, float hight, float nearPlane, float farPlane)
{
	float aspectRatio = width / hight;
	m_zoom = zoom;
	QMatrix4x4 projection;
	projection.perspective(m_zoom, aspectRatio, nearPlane, farPlane);
	m_projection = projection;
	updataShaderProgram();
}

QMatrix4x4& FoxActor::getProjection()
{
	// TODO: 在此处插入 return 语句
	return m_projection;
}

void FoxActor::setModel(const QMatrix4x4& model)
{
	m_model = model;
}

void FoxActor::setModelTranslation(QVector3D& position)
{
	m_model.translate(position);
	updataShaderProgram();
}

void FoxActor::setModelScale(float factor)
{
	m_model.scale(factor);
	updataShaderProgram();
}

void FoxActor::setModelRotate(QQuaternion& rotateQuat)
{
	m_model.rotate(rotateQuat);
	updataShaderProgram();
}

QMatrix4x4& FoxActor::getModel()
{
	// TODO: 在此处插入 return 语句
	return m_model;
}

void FoxActor::setView(const QMatrix4x4& view)
{
	m_view = view;
	updataShaderProgram();
}

void FoxActor::setView(std::shared_ptr<FoxCamera> camera)
{
	m_view = camera->getViewMatrix();
	updataShaderProgram();
}

void FoxActor::setViewRotate(QQuaternion& rotateQuat)
{
	m_view.rotate(rotateQuat);
	updataShaderProgram();
}

QMatrix4x4& FoxActor::getView()
{
	// TODO: 在此处插入 return 语句
	return m_view;
}



void FoxActor::updataShaderProgram()
{
	// 绑定着色器
	m_shaderProgarm->shaderBind();
	// 重新设置矩阵
	m_shaderProgarm->setMatrix4x4(m_projection, m_view, m_model);
}

std::shared_ptr<FoxShaderProgram> FoxActor::getShaderProgram()
{
	return m_shaderProgarm;
}

void FoxActor::setVertexBuffe()
{
	m_shaderProgarm->setVertexAttributeBuffe("aPos", 0, 3, 8 * sizeof(float));
	m_shaderProgarm->setVertexAttributeBuffe("aNormal", sizeof(float) * 3, 3, 8 * sizeof(float));
	m_shaderProgarm->setVertexAttributeBuffe("aTexCoords", sizeof(float) * 6, 2, 8 * sizeof(float));
}

void FoxActor::draw()
{
	// 如果不可见就 直接返回
	if (!m_actorVisibility) return;
	if (m_useTexture)
	{
		m_shaderProgarm->textureBind();
	}
	m_shaderProgarm->shaderBind();
	m_polyDataMapper->renderer();
}
