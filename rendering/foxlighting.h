#pragma once



#include <QVector3D>

/**
 * @brief 灯光类主要在程序中设置灯光属性.
 *  主要内容就是包含一些灯光的设置，将这些设置都包含在这个类中
 *  最后通过get set 的方法获取对应的比如说灯光颜色，灯光的位置漫反射强度镜面反射强度等
 *  就不需要再着色器程序中设置
 */
class QVector3D;
class FoxLighting
{
public:
	FoxLighting();
	~FoxLighting();

	// 设置和获取环境光强度
	void setAmbient(QVector3D ambient);
	QVector3D& getAmbient();

	// 设置和获取灯光颜色
	void setLightingColor(QVector3D color);
	QVector3D& getLightingColor();

	// 设置和获取漫反射强度
	void setDiffuse(QVector3D diffuse);
	QVector3D& getDiffuse();

	// 设置和获取镜面反射强度
	void setSpecuar(QVector3D specular);
	QVector3D& getSpecuar();

	// 设置和获取灯光位置
	void setPosition(QVector3D position);
	QVector3D& getPosition();

private:
	// 灯光属性
	QVector3D m_position; // 位置
	QVector3D m_ambient; // 环境
	QVector3D m_diffuse; // 漫反射
	QVector3D m_specular; // 镜面反射
	QVector3D m_lightingColor; // 灯光颜色
};

