#include "foxactor.h"
#include "foxshaderprogram.h"
#include "foxopenglpolydatamapper.h"
#include "foxcamera.h"

#include <iostream>
#include <QObject>

FoxActor::FoxActor(QObject* parent):m_zoom(45.0f),m_nearPlane(0.1f),m_farPlane(100.0f)
{
	
	// ��ռ��Ĭ��
	m_aspectRatio = (float)800 / (float)600;
	m_shaderProgarm = std::make_shared<FoxShaderProgram>(parent);
	// ����ģ�;����ͶӰ����
	//QVector3D viewPos = QVector3D(0.0, 0.0, -40.0f);
	//m_view.translate(viewPos);
	//m_view.scale(0.4);
	m_model.translate(QVector3D(0.0, 0.0, -30.0f));
	m_model.scale(0.3f);
	m_projection.perspective(m_zoom, m_aspectRatio, m_nearPlane, m_farPlane);
	m_shaderProgarm->setUseMaterial(false);
	m_shaderProgarm->setObjectColor(0.5f, 0.5f, 0.5f);
	// actor �Ƿ�ɼ�
	m_actorVisibility = true;
	m_useTexture = false;
}

FoxActor::~FoxActor()
{

}

void FoxActor::setPolyDataMapper(std::shared_ptr<FoxOpenGLPolyDataMapper> polyDataMapper)
{
	// ���ö�Ӧ�Ķ�������
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
///   ʹ������
/// </summary>
/// <param name="useTexture">����true ʹ�� false ��ʹ��</param>
void FoxActor::setUseTexture(bool useTexture)
{
	// ����Ϊtrue֮ǰ��Ҫ�ж��Ƿ��Ѿ���ʼ��������
	// �����Ƿ�Ӧ���Ƿ����쳣
	if (m_texturePath.isEmpty()) return;
	m_useTexture = useTexture;
	m_shaderProgarm->setUseMaterial(m_useTexture);
}

/// <summary>
///  ���ò��ʵ�ͼƬ·��
/// </summary>
/// <param name="textureName">���ʵ�ͼƬ·��</param>
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
	// TODO: �ڴ˴����� return ���
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
	// TODO: �ڴ˴����� return ���
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
	// TODO: �ڴ˴����� return ���
	return m_view;
}



void FoxActor::updataShaderProgram()
{
	// ����ɫ��
	m_shaderProgarm->shaderBind();
	// �������þ���
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
	// ������ɼ��� ֱ�ӷ���
	if (!m_actorVisibility) return;
	if (m_useTexture)
	{
		m_shaderProgarm->textureBind();
	}
	m_shaderProgarm->shaderBind();
	m_polyDataMapper->renderer();
}
