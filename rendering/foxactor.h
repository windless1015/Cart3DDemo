#pragma once


#include <QMatrix4x4>
#include <QVector3D>

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
	
	// ������ɫ
	void setColor(float r, float g, float b);

	// ����λ��
	void setActorPosition(QVector3D& position);
	
	// ����ͶӰ����
	void setProjection(float zoom, float width, float hight, float nearPlane, float farPlane);

	// ����ģ�;���
	void setModelTranslation(QVector3D& position);
	void setModelScale(float factor);

	// ������ͼ����
	void setView(std::shared_ptr<FoxCamera> camera);

	// ����actor����ɫ������
	void updataShaderProgram();
	std::shared_ptr<FoxShaderProgram> getShaderProgram();

	// ���ö��㻺������
	void setVertexBuffe();

	// ����
	void draw();

private:
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

};
