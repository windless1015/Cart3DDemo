#pragma once


#include <QMatrix4x4>
#include <QVector3D>
#include <QQuaternion>
/**
 * @brief Actor����Ҫ�Ǹ���ģ�����Ե�����.
 * ����˵ģ�͵ľ���任��ģ�͵���ɫ�޸ĵ���ص���Ⱦ����
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
	// ����ӳ���mapper
	void setPolyDataMapper(std::shared_ptr<FoxOpenGLPolyDataMapper> polyDataMapper);
	std::shared_ptr<FoxOpenGLPolyDataMapper> getPolyDataMapper();

	// ������ɫ
	void setColor(float r, float g, float b);

	// ����λ��
	void setActorPosition(QVector3D& position);
	
	// �Ƿ�ɼ� true �ɼ� false ���ɼ�
	void setVisibility(bool visibility);

	// ����ͶӰ����
	void setProjection(const QMatrix4x4& projection);
	void setProjection(float zoom, float width, float hight, float nearPlane, float farPlane);
	QMatrix4x4& getProjection();

	// ����ģ�;��� �任 ���� ��ת
	void setModel(const QMatrix4x4& model);
	void setModelTranslation(QVector3D& position);
	void setModelScale(float factor);
	void setModelRotate(QQuaternion& rotateQuat);
	QMatrix4x4& getModel();

	// ������ͼ���� ��ת��ͼ����
	void setView(const QMatrix4x4& view);
	void setView(std::shared_ptr<FoxCamera> camera);
	void setViewRotate(QQuaternion& rotateQuat);
	QMatrix4x4& getView();

	// ����actor����ɫ������
	void updataShaderProgram();
	std::shared_ptr<FoxShaderProgram> getShaderProgram();

	// ���ö��㻺������
	void setVertexBuffe();

	// ����
	void draw();

private:
	QQuaternion m_rotateQuat;// ������ת����Ԫ��
	QMatrix4x4 m_model; // ģ�;���
	QMatrix4x4 m_projection; // ͶӰ����
	QMatrix4x4 m_view; // ��ͼ����
	QVector3D m_actorPosition; // λ��
	std::shared_ptr<FoxOpenGLPolyDataMapper> m_polyDataMapper; // ����ӳ��
	std::shared_ptr<FoxShaderProgram> m_shaderProgarm; // ��ɫ��
	float m_zoom; 
	float m_aspectRatio; // ��ռ��
	float m_nearPlane;
	float m_farPlane;
	bool m_useTexture; // �Ƿ�ʹ�ò���
	bool m_actorVisibility; // �ɼ���
};
