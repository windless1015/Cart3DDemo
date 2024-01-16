#pragma once



// ��ɫ������
// ����ɫ����ʹ��,��qt��ɫ��������з�װ
// ������ģʽһ����Ĭ�ϵ���ȾЧ�� ���� ���������Ч��

class QOpenGLShaderProgram;
class QObject;
class QVector3D;
class QMatrix4x4;
class FoxShaderProgram
{
public:
	FoxShaderProgram(QObject* parent);
	~FoxShaderProgram();
	void shaderBind();
	void shaderRelease();
	

	void setObjectColor(float r,float g,float b);

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
	float m_objectColor[3];
};


