#include "foxlighting.h"




FoxLighting::FoxLighting()
{
	// 初始化灯光的属性
	m_position = QVector3D(5.0f, 10.0f, 30.0f);
	m_ambient = QVector3D(0.3f, 0.3f, 0.3f);
	m_diffuse = QVector3D(0.7f, 0.7f, 0.7f);
	m_specular = QVector3D(1.0f, 1.0f, 1.0f);
	m_lightingColor = QVector3D(1.0f, 1.0f, 1.0f);
}

FoxLighting::~FoxLighting()
{
}

void FoxLighting::setAmbient(QVector3D ambient)
{
	m_ambient = ambient;
}

QVector3D& FoxLighting::getAmbient()
{
	return this->m_ambient;
}

void FoxLighting::setLightingColor(QVector3D color)
{
	m_lightingColor = color;
}

QVector3D& FoxLighting::getLightingColor()
{
	return this->m_lightingColor;
}

void FoxLighting::setDiffuse(QVector3D diffuse)
{
	m_diffuse = diffuse;
}

QVector3D& FoxLighting::getDiffuse()
{
	return this->m_diffuse;
}

void FoxLighting::setSpecuar(QVector3D specular)
{
	m_specular = specular;
}

QVector3D& FoxLighting::getSpecuar()
{
	return this->m_specular;
}

void FoxLighting::setPosition(QVector3D position)
{
	m_position = position;
}

QVector3D& FoxLighting::getPosition()
{
	return this->m_position;
}
