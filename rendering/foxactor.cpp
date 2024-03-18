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

/***************************************************
//transformMatrix.translate(qv3d);是从官方得到了,我们直接拿来用没啥问题,直接就是m_model =   m_model * transformMatrix;即可
//也就是说QVector3D& qv3d这个参数是多余的,我们是用来练习自定义矩阵变换,才加上的这个参数
*****************************************************/
void FoxActor::setTransform(QMatrix4x4& transformMatrix, QVector3D& qv3d) {
	qDebug() << QString::fromLocal8Bit("设置变换矩阵...<foxactor.cpp>");
	//m_model.translate(QVector3D(8.6045361, -1.9544933, 19.358801));
	//m_model.translate(QVector3D((8.6045361, -1.9544933, 19.358801)
	
	//从(0,0,0) x:(1,0,0) y:(0,1,0)
	//平移到
	//从(qv3d.x,qv3d.y,qv3d.z) x:(1,0,0) y:(0,1,0) 方向位置,我们假设不变

	QVector3D A_position(0,0,0);

	QVector3D A_x(1, 0, 0);
	QVector3D A_y(0, 1, 0);

	A_x.normalize();
	A_y.normalize();

	//QVector3D A_z = A_x * A_y;
	QVector3D A_z = QVector3D::crossProduct(A_x, A_y);
	A_z.normalize();

	//QVector3D A_new_Y = A_z *  A_x;
	QVector3D A_new_Y = QVector3D::crossProduct(A_z, A_x);
	A_new_Y.normalize();
	//这个变换矩阵 matA 描述了从原始坐标系到目标坐标系的变换。
	//float matA[4][4] = {
	//	{A_x[0], new_Y[0], A_z[0], A_position[0]}, // First row
	//	{A_x[1], new_Y[1], A_z[1], A_position[1]}, // Second row
	//	{A_x[2], new_Y[2], A_z[2], A_position[2]}, // Third row
	//	{0, 0, 0, 1}
	//};

	QMatrix4x4 transformA(
			A_x[0], A_new_Y[0], A_z[0], A_position[0] , // First row
			A_x[1], A_new_Y[1], A_z[1], A_position[1], // Second row
			A_x[2], A_new_Y[2], A_z[2], A_position[2], // Third row
			0, 0, 0, 1);

	QMatrix4x4 transformAInvert = transformA;
	transformAInvert.inverted();



	QVector3D B_position(qv3d);

	QVector3D B_x(1, 0, 0);
	QVector3D B_y(0, 1, 0);

	B_x.normalize();
	B_y.normalize();

	//QVector3D B_z = B_x * B_y;
	QVector3D B_z = QVector3D::crossProduct(B_x, B_y);
	B_z.normalize();

	//QVector3D B_new_Y = B_z * B_x;
	QVector3D B_new_Y = QVector3D::crossProduct(B_z, B_x);
	B_new_Y.normalize();
	//这个变换矩阵 matA 描述了从原始坐标系到目标坐标系的变换。
	//float matA[4][4] = {
	//	{A_x[0], new_Y[0], A_z[0], A_position[0]}, // First row
	//	{A_x[1], new_Y[1], A_z[1], A_position[1]}, // Second row
	//	{A_x[2], new_Y[2], A_z[2], A_position[2]}, // Third row
	//	{0, 0, 0, 1}
	//};

	QMatrix4x4 transformB(
		B_x[0], B_new_Y[0], B_z[0], B_position[0], // First row
		B_x[1], B_new_Y[1], B_z[1], B_position[1], // Second row
		B_x[2], B_new_Y[2], B_z[2], B_position[2], // Third row
		0, 0, 0, 1);


	//[Mb] * [Ma] - 1
	QMatrix4x4 ResultMatrix4x4 = transformMatrix ;
	QMatrix4x4 ResultMatrix4x4_ = transformB * transformAInvert;
	//QMatrix4x4 ResultMatrix4x4_ = transformAInvert * transformB  ;

	qDebug() << "++++++++++++++++++++++++";
	for (int i = 0; i < 4; ++i) {;
		for (int j = 0; j < 4; ++j) {
			std::cout << ResultMatrix4x4(i, j)<<" ";
		}
		qDebug() << "";
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << ResultMatrix4x4_(i, j) << " ";
		}
		qDebug() << "";
	}
	qDebug() << "++++++++++++++++++++++++";
	//m_model.translate(QVector3D(qv3d));
	m_model = m_model * ResultMatrix4x4_;
	
	//后乘得到的结果是错误的
	//m_model =    transformMatrix * m_model;

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
	m_shaderProgarm->shaderBind();
	m_polyDataMapper->renderer();
}
