﻿#include "foxopenGLwidget.h"

#include  "../rendering/foxcamera.h"
#include  "../rendering/foxlighting.h"
#include  "../model/foxmeshmodel.h"
#include "../model/foxmesh.h"
#include "../rendering/foxshaderprogram.h"
#include "../rendering/foxrenderer.h"

#include <QKeyEvent>
#include <QMatrix4x4>
#include <QVector>
#include <QtOpenGL/qgl.h>
#include <gl/GLU.h>
//----------------test----------------
#include "../rendering/foxactor.h"
#include "../rendering/foxpolydata.h"
#include "../rendering/foxopenglpolydatamapper.h"
#include "../rendering/foxrenderer.h"
#include "../rendering/foxlinerenderer.h"
#include "../geometry/foxspheresource.h"
#include "../geometry/foxpipesource.h"
//----------------test----------------

//纹理库
#include <QImage>
#include <QOpenGLTexture>

using namespace OpenMesh;

FoxOpenGLWidget::FoxOpenGLWidget(QWidget* parent) :QOpenGLWidget(parent)
{
	m_meshIsVisible = true;
	m_firstMouse = true;
	m_useTexturel = false;
	m_isPressMouseLeft = false;
	m_isPressMouseMiddle = false;
	m_toothMeshModel = std::make_shared<FoxMeshModel>();
	m_angle = 0.0f;
	/// test
	m_renderer = std::make_shared<FoxRenderer>();
	m_foxPipeSource = std::make_shared<FoxPipeSource>();

	m_rotateQuat = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 30.0f);
	m_rotateQuat *= QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, -10.0f);
	// ��������
	QSurfaceFormat surfaceFormat;
	surfaceFormat.setSamples(4);
	setFormat(surfaceFormat);



	/*rotationQuat = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 30.0f);
	rotationQuat *= QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, -10.0f);*/
}

FoxOpenGLWidget::~FoxOpenGLWidget()
{
	// 确保释放opengl资源时上下文正确
	makeCurrent();
	delete m_camera;
	//doneCurrent();
}



void FoxOpenGLWidget::openMeshFolderPath(const QString& path)
{
	makeCurrent();
	m_shaderProgram->shaderBind();
	std::string folderPath = path.toStdString();
	m_toothMeshModel->setMeshFileFolder(folderPath);
	m_toothMeshModel->addMesh(m_shaderProgram->getShaderProgram());
	update();

	m_shaderProgram->shaderRelease();
}

//QVector3D(8.6045361, -1.9544933, 19.358801)
void FoxOpenGLWidget::openAttachmentFilePath(const QString& path, QVector3D& qv3d)
{
	//我正在尝试打开附件文件...
	//QMessageBox::information(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("我正在尝试打开附件文件..."));
	//qDebug() << QString::fromLocal8Bit("打开的附件文件路径为:[")<< path<<"]";
	//qDebug() << QString::fromLocal8Bit("打开的附件文件路径为:[%1]").arg(path);

	makeCurrent();

	// 下面的代码是测试封装的渲染类
	std::string fileName = path.toStdString();//应该是将const QString&转化为string吧
	Cart3D::OpenTriMesh mesh;//cart3d的网格//////////////////////////////////////////////////////////////////
	IO::read_mesh(mesh, fileName);//纯c++来读取文件

	std::shared_ptr<FoxPolyData> polydata = std::make_shared<FoxPolyData>(mesh);//获取网格的数据结构,什么顶点,面,法向量,纹理坐标,点数据之类的...
	std::shared_ptr<FoxOpenGLPolyDataMapper> mapper = std::make_shared<FoxOpenGLPolyDataMapper>();
	mapper->setPolyData(polydata);//OpenGLPolyDataMapper是polydata的数据映射
	
	std::shared_ptr<FoxActor> actor = std::make_shared<FoxActor>(this);
	actor->setPolyDataMapper(mapper);//演员
	//actor->setColor(0.5f, 0.5f, 0.5f);

	actor->setColor(1.0f, 0.0f, 0.0f);//设置红色


	// 应用矩阵变换
	QMatrix4x4 transformMatrix;
	transformMatrix.setToIdentity(); // 先将变换矩阵重置为单位矩阵
	transformMatrix.translate(qv3d); // 进行平移变换，将网格在 x 轴上移动 1.0 单位
	
	actor->setTransform(transformMatrix,qv3d);

	m_renderer->addActor(actor);
	update();

}

void FoxOpenGLWidget::openMeshFilePath(const QString& path)
{
	std::string fileName = path.toStdString();
	m_shaderProgram->shaderBind();
	//下面是之前的代码
	m_toothMeshModel->setMeshFileName(fileName);
	m_toothMeshModel->addMesh(m_shaderProgram->getShaderProgram());
	update();
	m_shaderProgram->shaderRelease();
}

void FoxOpenGLWidget::openMeshFilePath(const QString& upper, const QString& lower)
{
	makeCurrent();

	m_renderer->clearActors();
	//-------------------������Ⱦ��-------------------
	// ����ʱ�� : 2024-01-18 17:42  
	// ����Ĵ����ǲ��Է�װ����Ⱦ��

	std::string fileName = lower.toStdString();
	Cart3D::OpenTriMesh mesh;
	IO::read_mesh(mesh, fileName);

	std::shared_ptr<FoxPolyData> polydata = std::make_shared<FoxPolyData>(mesh);
	std::shared_ptr<FoxOpenGLPolyDataMapper> mapper = std::make_shared<FoxOpenGLPolyDataMapper>();
	mapper->setPolyData(polydata);
	std::shared_ptr<FoxActor> actor = std::make_shared<FoxActor>(this);
	actor->setPolyDataMapper(mapper);
	actor->setColor(0.5f, 0.5f, 0.5f);

	//// 上颌
	//std::string fileName1 = upper.toStdString();
	//// openmesh 读取成网格数据
	//Cart3D::OpenTriMesh mesh1;
	//IO::read_mesh(mesh1, fileName1);
	//// 交给polydata 转化成顶点数据
	//std::shared_ptr<FoxPolyData> polydata1 = std::make_shared<FoxPolyData>(mesh1);
	//std::shared_ptr<FoxOpenGLPolyDataMapper> mapper1 = std::make_shared<FoxOpenGLPolyDataMapper>();
	//mapper1->setPolyData(polydata1);
	//std::shared_ptr<FoxActor> actor1 = std::make_shared<FoxActor>(this);
	//actor1->setPolyDataMapper(mapper1);
	//// 设置蓝色
	//actor1->setColor(0.5f, 0.5f, 0.5f);

	m_renderer->addActor(actor);
	//m_renderer->addActor(actor1);
	update();
	//-----------------------------------------------
}

void FoxOpenGLWidget::openMeshFilePath(const QVector<QString>& tooth, const QString& gum)
{
	// �ڴ�������֮ǰ���֮ǰ�򿪵ļ�¼
	// Ҫȷ��Opengl��������ȷ �����޷�ִ���������Ⱦ
	makeCurrent();
	m_renderer->clearActors();
	// �������ݵ�ģ������
	for(auto& path: tooth){
		std::string fileName = path.toStdString();
		Cart3D::OpenTriMesh mesh;
		IO::read_mesh(mesh, fileName);
		std::shared_ptr<FoxPolyData> polydata = std::make_shared<FoxPolyData>(mesh);
		std::shared_ptr<FoxOpenGLPolyDataMapper> mapper = std::make_shared<FoxOpenGLPolyDataMapper>();
		mapper->setPolyData(polydata);
		std::shared_ptr<FoxActor> actor = std::make_shared<FoxActor>(this);
		actor->setPolyDataMapper(mapper);
		actor->setColor(0.5f, 0.5f, 0.5f);
		actor->setTexture(".\\res\\texture\\ToothTexture.png");

		m_renderer->addActor(actor);

	}
	// ��������
	std::string fileName = gum.toStdString();
	Cart3D::OpenTriMesh mesh;
	IO::read_mesh(mesh, fileName);
	std::shared_ptr<FoxPolyData> polydata = std::make_shared<FoxPolyData>(mesh);
	std::shared_ptr<FoxOpenGLPolyDataMapper> mapper = std::make_shared<FoxOpenGLPolyDataMapper>();
	mapper->setPolyData(polydata);
	std::shared_ptr<FoxActor> actor = std::make_shared<FoxActor>(this);
	actor->setPolyDataMapper(mapper);
	// ���ò���
	actor->setTexture(".\\res\\texture\\GingivaTexture.png");

	actor->setColor(0.5f, 0.5f, 0.5f);
	
	m_renderer->addActor(actor);

	update();

}

void FoxOpenGLWidget::setUseTexture(bool useTexture)
{
	makeCurrent();
	for (auto& actor : m_renderer->getActors()) {
		actor->setUseTexture(useTexture);
	}
	update();
}

void FoxOpenGLWidget::hiddenMesh()
{

	makeCurrent();
	m_meshIsVisible = false;
	m_toothMeshModel->setVisible(m_meshIsVisible);
	update();
}

void FoxOpenGLWidget::showMesh()
{
	makeCurrent();
	m_meshIsVisible = true;
	m_toothMeshModel->setVisible(m_meshIsVisible);
	update();
}

void FoxOpenGLWidget::cuttingMesh()
{
	if (m_renderer->getActors().size() == 0) return;
	makeCurrent();
	// 获取当前病例
	std::shared_ptr<FoxActor> actor = m_renderer->getActors()[0];
	// 调用切割算法并获取多个polydata
	std::vector<std::shared_ptr<FoxPolyData>> polyDataList;
	std::shared_ptr<FoxPolyData> polydata = actor->getPolyDataMapper()->getPolyData();
	polyDataList = m_toothMeshModel->cuttingMesh(polydata->getMesh());
	// 加载多个polydata数据
	m_renderer->clearActors(); // 加载之前清空之前的数据
	for (auto& data : polyDataList) {
		std::shared_ptr<FoxOpenGLPolyDataMapper> cuttingMapper = std::make_shared<FoxOpenGLPolyDataMapper>();
		cuttingMapper->setPolyData(data);
		std::shared_ptr<FoxActor> cuttingActor = std::make_shared<FoxActor>(this);
		cuttingActor->setPolyDataMapper(cuttingMapper);
		m_renderer->addActor(cuttingActor);
	}
	update();
}

void FoxOpenGLWidget::showSphereAndLine()
{
	if (m_renderer->getActors().size() == 0) return;
	makeCurrent();

	// 获取边界线顶点数据
	std::vector<std::vector<QVector3D>> dataList = m_toothMeshModel->getBoundaryVertex();
	for (auto& vertex : dataList) {
		for (auto& point : vertex) {
			// 创建球体
			FoxSphereSource sphere;
			sphere.setRadius(0.5f);
			// 设置圆心
			sphere.setCenter(point.x(), point.y(), point.z());
			std::shared_ptr<FoxOpenGLPolyDataMapper> mapper = std::make_shared<FoxOpenGLPolyDataMapper>();
			mapper->setPolyData(sphere.getOutputPolyData());
			std::shared_ptr<FoxActor> actor = std::make_shared<FoxActor>(this);
			actor->setPolyDataMapper(mapper);
			// 设置球体颜色
			actor->setColor(0.0f, 1.0f, 0.0f);
			m_renderer->addActor(actor);
		}
	}

	m_circle = this->buildCircle(0.5f, 48);

	for (auto& vertex : dataList) {
		m_path.clear();
		m_path = QVector<QVector3D>::fromStdVector(vertex);
		// 管道
		FoxPipeSource pipe;
		pipe.set(m_path, m_circle);

		// 添加至渲染当中
		std::shared_ptr<FoxOpenGLPolyDataMapper> mapper = std::make_shared<FoxOpenGLPolyDataMapper>();
		mapper->setPolyData(pipe.getOutputPolyData());
		std::shared_ptr<FoxActor> actor = std::make_shared<FoxActor>(this);
		actor->setPolyDataMapper(mapper);
		// 设置颜色
		actor->setColor(1.0f, 1.0f, 0.0f);
		m_renderer->addActor(actor);
	}


	update();

}

void FoxOpenGLWidget::setActorAlpha(float alpha)
{
	makeCurrent();

	for (auto& actor : m_renderer->getActors()) {
		QVector3D color = actor->getColor(); // 获取颜色
		float r = color.x();
		float g = color.y();
		float b = color.z();
		actor->setColor(r, g, b, alpha);
	}
	update();
}




void FoxOpenGLWidget::translate_point(QPoint& p_ab)
{
	// this->width() 表示视口的宽度，由于视口宽高一样，
	// 所以点(this->width(), this->height() )就是视口的中心点，即旋转中心。
	int x = p_ab.x() - this->width() / 2;
	int y = -(p_ab.y() - this->height() / 2);

	p_ab.setX(x);
	p_ab.setY(y);
}

void FoxOpenGLWidget::setPressPosition(QPoint p_ab)
{
	translate_point(p_ab);
	press_position = p_ab;
}

void FoxOpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	m_camera = new FoxCamera(QVector3D(0.0f, 0.0f, 6.0f));
	// 设置牙齿纹理图片文件
	m_toothTexture = new QOpenGLTexture(QImage(".\\res\\texture\\ToothTexture.png").mirrored());
	m_toothTexture->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
	m_toothTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	m_toothTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	// 设置牙龈纹理图片文件
	m_gingivaTexture = new QOpenGLTexture(QImage(".\\res\\texture\\GingivaTexture.png").mirrored());
	m_gingivaTexture->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
	m_gingivaTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	m_gingivaTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

	// 创建着色器程序
	m_shaderProgram = new FoxShaderProgram(this);

	// ------------------------------------------------
	// 2024-01-16
	// 下面的这些代码直接交给FoxRenderer类来管理
	// 在这个三维显示窗口只需要调用 read->draw();
	// ------------------------------------------------
	m_meshPosition = QVector3D(0.0f, 0.0f, -30.0f);
	m_shaderProgram->shaderRelease();
	m_zoom = m_camera->getCameraZoom();
	m_projection.perspective(m_zoom, (float)width() / (float)height(), 0.1f, 100.0f);
	m_view = m_camera->getViewMatrix();
	m_model.translate(m_meshPosition);
	m_model.scale(0.3f);
	// 设置观察向量
	m_viewPos = m_camera->getPosition();
	m_circle = this->buildCircle(0.5f, 48);

	std::vector<std::vector<QVector3D>> dataList = m_toothMeshModel->getBoundaryVertex();
	// -------------------bug---------------------
	// 2024年2月2日 17:16
	// 测试出来的原因是因为上一个点映射出来的面上的点和一个点垂直
	//qDebug() << QVector<QVector3D>::fromStdVector(dataList[5]);
	//m_path = QVector<QVector3D>::fromStdVector(dataList[5]);
	//m_path.push_back(dataList[5][0]);
	//m_path.push_back(dataList[6][0]);
	//m_path.push_back(dataList[6][1]);
	//for(auto& point: dataList[4]){
	//    m_path.push_back(point);
	//    //m_path.push_back(dataList[4][1]);
	//}

	/*
	* (-13.55668, -6.0114579, 13.011313)
(-13.487358, -7.1773224, 14.927433)
(-13.138556, -7.6332245, 15.899716)
(-12.338324, -8.0273628, 16.801361)
(-10.824355, -7.4393415, 17.726093)
(-10.209102, -6.3536015, 17.959667)
(-9.519865, -4.9496355, 17.846539)
(-8.8041353, -3.7513621, 17.34923)
(-9.1492462, -2.0842795, 17.507181)
(-9.4483528, -0.4770748, 17.476612)
(-9.5039253, 0.61780488, 17.190432)
(-9.5306892, 1.5089185, 16.862356)
(-9.0157328, 0.85421985, 16.185822)
(-7.8984418, -2.1116643, 14.888825)
(-8.108861, -3.3981972, 12.636942)
(-8.8557825, -4.25598, 10.784942)
(-9.8205938, -4.6516943, 9.5451708)
(-11.195418, -4.7247691, 9.4539118)
(-12.191826, -3.3123047, 11.043638)
(-12.960554, -3.1490266, 11.563456)
(-13.785104, -3.8911073, 12.069867)
	*/
	//m_path.push_back(QVector3D(-13.487358, -7.1773224, 14.927433));
	//m_path.push_back(QVector3D(-13.138556, -7.6332245, 15.899716));
	//m_path.push_back(QVector3D(-12.338324, -8.0273628, 16.801361));
	//m_path.push_back(QVector3D(-10.824355, -7.4393415, 17.726093));
	//m_path.push_back(QVector3D(-10.209102, -6.3536015, 17.959667));
	//m_path.push_back(QVector3D(-9.519865, -4.9496355, 17.846539));
	//m_path.push_back(QVector3D(-8.8041353, -3.7513621, 17.34923));
	//m_path.push_back(QVector3D(-9.1492462, -2.0842795, 17.507181));
	//m_path.push_back(QVector3D(-9.4483528, -0.4770748, 17.476612));
	//m_path.push_back(QVector3D(-9.5039253, 0.61780488, 17.190432));
	//m_path.push_back(QVector3D(-9.5306892, 1.5089185, 16.862356));
	//m_path.push_back(QVector3D(-9.0157328, 0.85421985, 16.185822));
	//m_path.push_back(QVector3D(-7.8984418, -2.1116643, 14.888825));
	//m_path.push_back(QVector3D(-8.108861, -3.3981972, 12.636942));
	//m_path.push_back(QVector3D(-8.8557825, -4.25598, 10.784942));
	//m_path.push_back(QVector3D(-9.8205938, -4.6516943, 9.5451708));
	//m_path.push_back(QVector3D(-11.195418, -4.7247691, 9.4539118));
	//m_path.push_back(QVector3D(-12.191826, -3.3123047, 11.043638));
	//m_path.push_back(QVector3D(-12.960554, -3.1490266, 11.563456));
	//m_path.push_back(QVector3D(-13.785104, -3.8911073, 12.069867));

	//m_foxPipeSource->set(m_path, m_circle);

	//Cart3D::OpenTriMesh mesh = m_foxPipeSource->createPipeMesh();
	//OpenMesh::IO::write_mesh(mesh, "E:\\3D\\TestData\\testData\\test\\pipe.stl");


}

// 窗口改变时执行
void FoxOpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	// -------------------------------------------
	// 2024-01-19 
	// 下面的东西我在想是否应该交给什么类来作为Actor的更新

	// 改变所有模型的投影矩阵保证模型不会变形
	float zoom = 45.0;
	for (auto& actor : m_renderer->getActors())
	{
		actor->setProjection(zoom, (float)width(), (float)height(), 0.1f, 100.0f);
	}
	update();


}




void FoxOpenGLWidget::paintGL()
{
	glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Z缓冲(Z-buffer)，也被称为深度缓冲(Depth Buffer)
	glEnable(GL_DEPTH_TEST); 
	// 开启混合模式
	glEnable(GL_BLEND);
	// 混合方程设置透明度
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_renderer->renderer();
}


void FoxOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
	qDebug() << "mousePressEvent";
	event->accept();
	mousePos = event->pos();

	if (m_renderer->getActors().size() == 0) return;
	if (event->button() == Qt::LeftButton) {
		m_leftMoveMousePos = event->pos();
		m_isPressMouseLeft = true;
		qDebug() << "mousePressEvent:[" << m_leftMoveMousePos<<"]";
	}
	if (event->button() == Qt::MiddleButton) {
		m_middleMoveMousePos = event->pos();
		m_isPressMouseMiddle = true;
	}

	//单击 
	QPoint p_ab = event->pos();
	// 如果是鼠标左键按下
	if (event->button() == Qt::LeftButton)
	{
		modelUse = modelSave;
		setPressPosition(p_ab);
	}


	//计算模型的旋转轴
	/*rotationAxis[0] = 0.0f;
	rotationAxis[1] = 1.0f;
	rotationAxis[2] = 0.0f;*/

}

void FoxOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
	qDebug() << "mouseMoveEvent";
	if (m_renderer->getActors().size() == 0) return;
	event->accept();
	// 如果按下的是左键就旋转
	if (m_isPressMouseLeft) {
		//qDebug() << "mouseMoveEvent--m_leftMoveMousePos:[" << event->pos() << "]";
		//QVector2D diff = QVector2D(event->pos()) - QVector2D(m_leftMoveMousePos);
		//qDebug() << "mouseMoveEvent--m_leftMoveMousePos:["<< diff << "]";

		/*float angle = 2.0f;
		m_leftMoveMousePos = event->pos();
		QVector3D n = QVector3D(diff.y(), diff.x(), 0.0f).normalized();
		m_rotateAxis = (m_rotateAxis + n).normalized();
		m_rotateQuat = QQuaternion::fromAxisAndAngle(m_rotateAxis, angle)* m_rotateQuat;
		for (auto& actor : m_renderer->getActors()) {
			actor->setModelRotate(m_rotateQuat);
		}*/
		
		//如何正确完成模型的旋转?
		event->accept();
		if (m_isPressMouseLeft) {
			QPoint p_ab = event->pos();
			translate_point(p_ab); // 坐标系转换 
			
			QPoint sub_point = p_ab - press_position;
			qDebug() << p_ab << "-" << press_position << "=" << sub_point;
			press_position = p_ab;
			// 计算鼠标移动的角度
			float angle = qSqrt(qPow(sub_point.x(), 2) + qPow(sub_point.y(), 2)) / 5;

			// 固定旋转轴，例如围绕Z轴旋转
			//QVector3D rotationAxis(0.0f, 0.0f, 1.0f);
			//QVector3D rotationAxis(1.0f, 0.0f, 0.0f);//x
			//QVector3D rotationAxis(0.0f, 1.0f, 0.0f);//y
			//QVector3D rotationAxis(0.0f, 0.0f, 1.0f);

			// 计算旋转轴
			QVector3D rotationAxis = QVector3D(-sub_point.y(), sub_point.x(), 0.0).normalized();

			// 根据旋转轴和角度创建四元数
			QQuaternion rotationQuat = QQuaternion::fromAxisAndAngle(rotationAxis, angle);



			//m_renderer->getActors()[0]->setModelRotate(rotationQuat);
			// 对每个模型进行旋转
			for (auto& actor : m_renderer->getActors()) {
				actor->setModelRotate(rotationQuat);
			}
			
		}


	}
	// �ж��Ƿ��µ����м�
	if (m_isPressMouseMiddle) {
		if (m_firstMouse) {
			// ����ǵ�һ�ΰ��¼�¼��ǰ��λ��
			m_middleMoveMousePos = event->pos();
			m_firstMouse = false;
		}
		float xoffset = m_middleMoveMousePos.x() - event->pos().x();
		float yoffset = m_middleMoveMousePos.y() - event->pos().y();
		m_middleMoveMousePos = event->pos();
		float sensitivity = 0.2;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		// ƽ��ģ��
		//m_model.translate(QVector3D(-xoffset, yoffset, 0));
		for (auto& actor : m_renderer->getActors()) {//middle key
			actor->setModelTranslation(QVector3D(-xoffset, yoffset, 0));
		}
	}
	update();
}

void FoxOpenGLWidget::wheelEvent(QWheelEvent* event)
{
	qDebug() << "wheelEvent";
	//qDebug() << "FoxOpenGLWidget::wheelEvent";
	if (m_renderer->getActors().size() == 0) return;
	// 滚动的速度
	float speed = 1;
	// 获取滚轮的返回值滚轮往前滚是正往后是负
	float yoffset = event->angleDelta().y();
	// 判断滚轮滚动的方向
	if (yoffset > 0)
		yoffset = speed;
	if (yoffset < 0)
		yoffset = -speed;
	//m_camera->wheelScrollEvent(yoffset);
	//m_zoom = m_camera->getCameraZoom();
	//QMatrix4x4 projection;
	//projection.perspective(m_zoom, (float)width() / (float)height(), 0.1f, 100.0f);
	//m_projection = projection;
	m_renderer->setCameraZoom(yoffset);
	m_zoom = m_renderer->getCameraZoom();
	for (auto& actor : m_renderer->getActors())
	{
		actor->setProjection(m_zoom, (float)width(), (float)height(), 0.1f, 100.0f);
	}

	update();
}

void FoxOpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
	qDebug() << "mouseReleaseEvent";
	if (m_renderer->getActors().size() == 0) return;
	if (event->button() == Qt::LeftButton) {
		// 松开左键后设置为false;
		m_isPressMouseLeft = false;
	}
	if (event->button() == Qt::MiddleButton) {
		m_isPressMouseMiddle = false;
	}



}

QVector<QVector3D> FoxOpenGLWidget::buildSpiralPath(float r1, float r2, float h1, float h2, float turns, int points)
{

	const float PI = acos(-1);
	QVector<QVector3D> vertices;
	QVector3D vertex;
	float r = r1;
	float rStep = (r2 - r1) / (points - 1);
	float y = h1;
	float yStep = (h2 - h1) / (points - 1);
	float a = 0;
	float aStep = (turns * 2 * PI) / (points - 1);
	for (int i = 0; i < points; ++i)
	{
		vertex.setX(r * cos(a));
		vertex.setZ(r * sin(a));
		vertex.setY(y);
		vertices.push_back(vertex);
		// next
		r += rStep;
		y += yStep;
		a += aStep;
	}
	return vertices;
}

QVector<QVector3D> FoxOpenGLWidget::buildSpiralPath(QVector3D r1, QVector3D r2, float h1, float h2, float turns, int points)
{
	const float PI = acos(-1);
	QVector<QVector3D> vertices;
	QVector3D vertex;
	QVector3D r = r1;
	QVector3D rStep = (r2 - r1) / (points - 1);
	float y = h1;
	float yStep = (h2 - h1) / (points - 1);
	float a = 0;
	float aStep = (turns * 2 * PI) / (points - 1);
	for (int i = 0; i < points; ++i)
	{
		vertex.setX(r.x() * cos(a));
		vertex.setZ(r.z() * sin(a));
		vertex.setY(r.y());
		vertices.push_back(vertex);
		// next
		r += rStep;
		y += yStep;
		a += aStep;
	}
	return vertices;
}

QVector<QVector3D> FoxOpenGLWidget::buildCircle(float radius, int steps)
{
	QVector<QVector3D> points;
	if (steps < 2) return points;

	const float PI2 = acos(-1) * 2.0f;
	float x, y, a;
	for (int i = 0; i <= steps; ++i)
	{
		// 这个相当于θ
		a = PI2 / steps * i;
		x = radius * cosf(a);
		y = radius * sinf(a);
		points.push_back(QVector3D(x, y, 0));
	}
	return points;
}


