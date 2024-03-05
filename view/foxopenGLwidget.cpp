#include "foxopenGLwidget.h"

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

//----------------test----------------
#include "../rendering/foxactor.h"
#include "../rendering/foxpolydata.h"
#include "../rendering/foxopenglpolydatamapper.h"
#include "../rendering/foxrenderer.h"
#include "../rendering/foxlinerenderer.h"
#include "../geometry/foxspheresource.h"
#include "../geometry/foxpipesource.h"
//----------------test----------------

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
}

FoxOpenGLWidget::~FoxOpenGLWidget()
{
	// ȷ���ͷ�opengl��Դʱ��������ȷ
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

void FoxOpenGLWidget::openMeshFilePath(const QString& path)
{
	std::string fileName = path.toStdString();
	m_shaderProgram->shaderBind();
	//������֮ǰ�Ĵ���
	m_toothMeshModel->setMeshFileName(fileName);
	m_toothMeshModel->addMesh(m_shaderProgram->getShaderProgram());
	update();
	m_shaderProgram->shaderRelease();
}

void FoxOpenGLWidget::openMeshFilePath(const QString& upper, const QString& lower)
{
	makeCurrent();

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

	//// ���
	//std::string fileName1 = upper.toStdString();
	//// openmesh ��ȡ����������
	//Cart3D::OpenTriMesh mesh1;
	//IO::read_mesh(mesh1, fileName1);
	//// ����polydata ת���ɶ�������
	//std::shared_ptr<FoxPolyData> polydata1 = std::make_shared<FoxPolyData>(mesh1);
	//std::shared_ptr<FoxOpenGLPolyDataMapper> mapper1 = std::make_shared<FoxOpenGLPolyDataMapper>();
	//mapper1->setPolyData(polydata1);
	//std::shared_ptr<FoxActor> actor1 = std::make_shared<FoxActor>(this);
	//actor1->setPolyDataMapper(mapper1);
	//// ������ɫ
	//actor1->setColor(0.5f, 0.5f, 0.5f);

	m_renderer->addActor(actor);
	//m_renderer->addActor(actor1);
	update();
	//-----------------------------------------------
}

void FoxOpenGLWidget::setUseTexture(bool useTexture)
{
	makeCurrent();
	m_useTexturel = useTexture;
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
	// ��ȡ��ǰ����
	std::shared_ptr<FoxActor> actor = m_renderer->getActors()[0];
	// �����и��㷨����ȡ���polydata
	std::vector<std::shared_ptr<FoxPolyData>> polyDataList;
	std::shared_ptr<FoxPolyData> polydata = actor->getPolyDataMapper()->getPolyData();
	polyDataList = m_toothMeshModel->cuttingMesh(polydata->getMesh());
	// ���ض��polydata����
	m_renderer->clearActors(); // ����֮ǰ���֮ǰ������
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

	// ��ȡ�߽��߶�������
	std::vector<std::vector<QVector3D>> dataList = m_toothMeshModel->getBoundaryVertex();
	for (auto& vertex : dataList) {
		for (auto& point : vertex) {
			// ��������
			FoxSphereSource sphere;
			sphere.setRadius(0.5f);
			// ����Բ��
			sphere.setCenter(point.x(), point.y(), point.z());
			std::shared_ptr<FoxOpenGLPolyDataMapper> mapper = std::make_shared<FoxOpenGLPolyDataMapper>();
			mapper->setPolyData(sphere.getOutputPolyData());
			std::shared_ptr<FoxActor> actor = std::make_shared<FoxActor>(this);
			actor->setPolyDataMapper(mapper);
			// ����������ɫ
			actor->setColor(0.0f, 1.0f, 0.0f);
			m_renderer->addActor(actor);
		}
	}

	m_circle = this->buildCircle(0.5f, 48);

	for (auto& vertex : dataList) {
		m_path.clear();
		m_path = QVector<QVector3D>::fromStdVector(vertex);
		// �ܵ�
		FoxPipeSource pipe;
		pipe.set(m_path, m_circle);

		// �������Ⱦ����
		std::shared_ptr<FoxOpenGLPolyDataMapper> mapper = std::make_shared<FoxOpenGLPolyDataMapper>();
		mapper->setPolyData(pipe.getOutputPolyData());
		std::shared_ptr<FoxActor> actor = std::make_shared<FoxActor>(this);
		actor->setPolyDataMapper(mapper);
		// ������ɫ
		actor->setColor(1.0f, 1.0f, 0.0f);
		m_renderer->addActor(actor);
	}


	update();

}

void FoxOpenGLWidget::setActorAlpha(float alpha)
{
	makeCurrent();

	for (auto& actor : m_renderer->getActors()) {
		QVector3D color = actor->getColor(); // ��ȡ��ɫ
		float r = color.x();
		float g = color.y();
		float b = color.z();
		actor->setColor(r, g, b, alpha);
	}
	update();
}




void FoxOpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	m_camera = new FoxCamera(QVector3D(0.0f, 0.0f, 6.0f));
	// ������������ͼƬ�ļ�
	m_toothTexture = new QOpenGLTexture(QImage(".\\res\\texture\\ToothTexture.png").mirrored());
	m_toothTexture->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
	m_toothTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	m_toothTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
	// ������������ͼƬ�ļ�
	m_gingivaTexture = new QOpenGLTexture(QImage(".\\res\\texture\\GingivaTexture.png").mirrored());
	m_gingivaTexture->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
	m_gingivaTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
	m_gingivaTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

	// ������ɫ������
	m_shaderProgram = new FoxShaderProgram(this);

	// ------------------------------------------------
	// 2024-01-16
	// �������Щ����ֱ�ӽ���FoxRenderer��������
	// �������ά��ʾ����ֻ��Ҫ���� read->draw();
	// ------------------------------------------------
	m_meshPosition = QVector3D(0.0f, 0.0f, -30.0f);
	m_shaderProgram->shaderRelease();
	m_zoom = m_camera->getCameraZoom();
	m_projection.perspective(m_zoom, (float)width() / (float)height(), 0.1f, 100.0f);
	m_view = m_camera->getViewMatrix();
	m_model.translate(m_meshPosition);
	m_model.scale(0.3f);
	// ���ù۲�����
	m_viewPos = m_camera->getPosition();
	m_circle = this->buildCircle(0.5f, 48);

	std::vector<std::vector<QVector3D>> dataList = m_toothMeshModel->getBoundaryVertex();
	// -------------------bug---------------------
	// 2024��2��2�� 17:16
	// ���Գ�����ԭ������Ϊ��һ����ӳ����������ϵĵ��һ���㴹ֱ
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

// ���ڸı�ʱִ��
void FoxOpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	// -------------------------------------------
	// 2024-01-19 
	// ����Ķ����������Ƿ�Ӧ�ý���ʲô������ΪActor�ĸ���

	// �ı�����ģ�͵�ͶӰ����֤ģ�Ͳ������
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
	//Z����(Z-buffer)��Ҳ����Ϊ��Ȼ���(Depth Buffer)
	glEnable(GL_DEPTH_TEST); 
	// �������ģʽ
	glEnable(GL_BLEND);
	// ��Ϸ�������͸����
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_renderer->renderer();

 
}

void FoxOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
	//qDebug() << " FoxOpenGLWidget::mousePressEvent";
	if (m_renderer->getActors().size() == 0) return;
	// std::cout << "����¼�\n";
	if (event->button() == Qt::LeftButton) {
		m_leftMoveMousePos = event->pos();
		m_isPressMouseLeft = true;
	}
	if (event->button() == Qt::MiddleButton) {
		m_middleMoveMousePos = event->pos();
		m_isPressMouseMiddle = true;
	}
}

void FoxOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
	//qDebug() << "FoxOpenGLWidget::mouseMoveEvent";
	if (m_renderer->getActors().size() == 0) return;

	event->accept();
	// ������µ���������ƶ�
	if (m_isPressMouseLeft) {

		float angle = 1.5f;
		QVector2D diff = QVector2D(event->pos()) - QVector2D(m_leftMoveMousePos);
		m_leftMoveMousePos = event->pos();
		QVector3D n;
		n = QVector3D(diff.y(), diff.x(), 0.0f).normalized();
		m_rotateAxis = (m_rotateAxis + n).normalized();
		m_rotateQuat = QQuaternion::fromAxisAndAngle(m_rotateAxis, angle);
		for (auto& actor : m_renderer->getActors()) {
			actor->setModelRotate(m_rotateQuat);
		}
		update();

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
		for (auto& actor : m_renderer->getActors()) {
			actor->setModelTranslation(QVector3D(-xoffset, yoffset, 0));
		}
	}

	update(); // �����ػ�
}

void FoxOpenGLWidget::wheelEvent(QWheelEvent* event)
{
	//qDebug() << "FoxOpenGLWidget::wheelEvent";
	if (m_renderer->getActors().size() == 0) return;
	// �������ٶ�
	float speed = 1;
	// ��ȡ���ֵķ���ֵ������ǰ�����������Ǹ�
	float yoffset = event->angleDelta().y();
	// �жϹ��ֹ����ķ���
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
	if (m_renderer->getActors().size() == 0) return;
	if (event->button() == Qt::LeftButton) {
		// �ɿ����������Ϊfalse;
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
		// ����൱�ڦ�
		a = PI2 / steps * i;
		x = radius * cosf(a);
		y = radius * sinf(a);
		points.push_back(QVector3D(x, y, 0));
	}
	return points;
}


