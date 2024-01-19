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
	m_model.translate(QVector3D(0.0, 0.0, -30.0f));
	m_model.scale(0.3f);
	m_projection.perspective(m_zoom, m_aspectRatio, m_nearPlane, m_farPlane);
	m_shaderProgarm->setUseMaterial(false);
	m_shaderProgarm->setObjectColor(0.5f, 0.5f, 0.5f);
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

void FoxActor::setColor(float r, float g, float b)
{
	m_shaderProgarm->shaderBind();
	m_shaderProgarm->setObjectColor(r, g, b);
}

void FoxActor::setActorPosition(QVector3D& position)
{
	m_actorPosition = position;
}

void FoxActor::setProjection(float zoom, float width, float hight, float nearPlane, float farPlane)
{
	float aspectRatio = width / hight;
	m_projection.perspective(zoom, aspectRatio, nearPlane, farPlane);
}

void FoxActor::setModelTranslation(QVector3D& position)
{
	m_model.translate(position);
}

void FoxActor::setModelScale(float factor)
{
	m_model.scale(factor);
}

void FoxActor::setView(std::shared_ptr<FoxCamera> camera)
{
	m_view = camera->getViewMatrix();
}



void FoxActor::updataShaderProgram()
{
	// 绑定着色器
	m_shaderProgarm->shaderBind();
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
	m_shaderProgarm->setVertexAttributeBuffe("aPos", 0, 3, 8 * sizeof(float));
}

void FoxActor::draw()
{
	m_shaderProgarm->shaderBind();
	m_polyDataMapper->renderer();
}
