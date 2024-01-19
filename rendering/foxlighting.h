#pragma once



#include <QVector3D>

/**
 * @brief �ƹ�����Ҫ�ڳ��������õƹ�����.
 *  ��Ҫ���ݾ��ǰ���һЩ�ƹ�����ã�����Щ���ö��������������
 *  ���ͨ��get set �ķ�����ȡ��Ӧ�ı���˵�ƹ���ɫ���ƹ��λ��������ǿ�Ⱦ��淴��ǿ�ȵ�
 *  �Ͳ���Ҫ����ɫ������������
 */
class QVector3D;
class FoxLighting
{
public:
	FoxLighting();
	~FoxLighting();

	// ���úͻ�ȡ������ǿ��
	void setAmbient(QVector3D ambient);
	QVector3D& getAmbient();

	// ���úͻ�ȡ�ƹ���ɫ
	void setLightingColor(QVector3D color);
	QVector3D& getLightingColor();

	// ���úͻ�ȡ������ǿ��
	void setDiffuse(QVector3D diffuse);
	QVector3D& getDiffuse();

	// ���úͻ�ȡ���淴��ǿ��
	void setSpecuar(QVector3D specular);
	QVector3D& getSpecuar();

	// ���úͻ�ȡ�ƹ�λ��
	void setPosition(QVector3D position);
	QVector3D& getPosition();

private:
	// �ƹ�����
	QVector3D m_position; // λ��
	QVector3D m_ambient; // ����
	QVector3D m_diffuse; // ������
	QVector3D m_specular; // ���淴��
	QVector3D m_lightingColor; // �ƹ���ɫ
};

