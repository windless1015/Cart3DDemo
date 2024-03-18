#pragma once


#include <memory>
#include <QString>
// ��ɫ������
// ����ɫ����ʹ��,��qt��ɫ��������з�װ
// ������ģʽһ����Ĭ�ϵ���ȾЧ�� ���� ���������Ч��
class QOpenGLShaderProgram;
class QOpenGLTexture;
class QObject;
class QString;
class QVector3D;
class QMatrix4x4;
class FoxLighting;
class FoxShaderProgram
{
public:
	FoxShaderProgram(QObject* parent);
	~FoxShaderProgram();
	// ����ɫ��
	void shaderBind();
	// �ͷ���ɫ��
	void shaderRelease();
	// ����������ɫ
	void setObjectColor(float r,float g,float b,float alpha=1.0f);
	// ���þ���
	void setMatrix4x4(QMatrix4x4& projection, QMatrix4x4& view, QMatrix4x4& model);
	// �Ƿ�ʹ�ò��� true ʹ��  false ��ʹ��
	void setUseMaterial(bool useMaterial);
	void setMaterialPath(const QString& texturePath);
	void initTexture();
	void textureBind();
	// ���õƹ�
	void setLighting(std::shared_ptr<FoxLighting> lighting);
	// �������Ի���
	void setVertexAttributeBuffe(const char* name, int offset, int tupleSize, int stride = 0);
	// ���ù۲�Ƕ�
	void setViewPosition(QVector3D& viewPosition);
	/// <summary>
	///  ����Ⱦʱִ����ɫ��
	/// </summary>
	/// <param name="useMaterial">�Ƿ�ʹ�ò��� true�� false��</param>
	/// <param name="viewPosition">�۲��λ��</param>
	/// <param name="projection">ͶӰ����</param>
	/// <param name="view">��ͼ����</param>
	/// <param name="model">ģ�;���</param>
	void useShaderProgram(bool useMaterial,QVector3D& viewPosition,QMatrix4x4& projection,QMatrix4x4& view,QMatrix4x4& model);

	QOpenGLShaderProgram* getShaderProgram();
	void setShaderProgram(QOpenGLShaderProgram* shaderProgram);

private:
	// ��ɫ������
	QOpenGLShaderProgram* m_shaderProgram;
	// ������ɫ
	float m_objectColor[4];
	QOpenGLTexture* m_texture;
	QString m_texturePath;
	bool m_useTexture;
};


