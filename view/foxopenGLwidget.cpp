#include "foxopenGLwidget.h"

#include  "../rendering/foxcamera.h"
#include  "../rendering/foxlighting.h"
#include  "../model/foxmeshmodel.h"
#include "../model/foxmesh.h"
#include "../rendering/foxshaderprogram.h"
#include "../rendering/foxrenderer.h"

#include <QKeyEvent>
#include <QMatrix4x4>

#include <QtOpenGL/qgl.h>

//----------------test----------------
#include "../rendering/foxactor.h"
#include "../rendering/foxpolydata.h"
#include "../rendering/foxopenglpolydatamapper.h"
#include "../rendering/foxrenderer.h"
#include "../rendering/foxlinerenderer.h"
#include "../geometry/foxspheresource.h"
//----------------test----------------

using namespace OpenMesh;

FoxOpenGLWidget::FoxOpenGLWidget(QWidget* parent):QOpenGLWidget(parent)
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
    qDebug() << "cuttingMesh" << m_renderer->getActors().size();
    if (m_renderer->getActors().size()==0) return;

    makeCurrent();
    // ��ȡ��ǰ����
    std::shared_ptr<FoxActor> actor = m_renderer->getActors()[0];
    // �����и��㷨����ȡ���polydata
    std::vector<std::shared_ptr<FoxPolyData>> polyDataList;
    std::shared_ptr<FoxPolyData> polydata = actor->getPolyDataMapper()->getPolyData();
    polyDataList = m_toothMeshModel->cuttingMesh(polydata->getMesh());
    // ���ض��polydata����
    m_renderer->clearActors(); // ����֮ǰ���֮ǰ������
    for(auto& data:polyDataList){
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
    for(auto &cpts: dataList){
        for(auto& point:cpts){
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


    for(auto& vertex: dataList){
        QVector<QVector3D> controlPoints = QVector<QVector3D>::fromStdVector(vertex);
        std::shared_ptr<FoxLineRenderer> lineRenderer = std::make_shared<FoxLineRenderer>();
        lineRenderer->setVector(controlPoints);
        m_lineRenderer.push_back(lineRenderer);
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
        actor->setProjection(zoom, (float)width() , (float)height(), 0.1f, 100.0f);
    }

    update();
}




void FoxOpenGLWidget::paintGL()
{
    glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Z����(Z-buffer)��Ҳ����Ϊ��Ȼ���(Depth Buffer)
    glEnable(GL_DEPTH_TEST); //Ĭ�Ϲرյ�

    m_renderer->renderer();
    for(auto& line:m_lineRenderer){
        line->initialize();
        line->render();
    }

}

void FoxOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    if (m_renderer->getActors().size() == 0) return;
   // std::cout << "����¼�\n";
    if(event->button() == Qt::LeftButton){
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
    if (m_renderer->getActors().size() == 0) return;

    event->accept();
    // ������µ���������ƶ�
    if (m_isPressMouseLeft) {

        float angle = 1.5f;
        QVector2D diff = QVector2D(event->pos())-QVector2D(m_leftMoveMousePos);
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
            m_middleMoveMousePos.setX(event->pos().x());
            m_middleMoveMousePos.setY(event->pos().y());
            m_firstMouse = false;
        }
        float xoffset = m_middleMoveMousePos.x() - event->pos().x();
        float yoffset = m_middleMoveMousePos.y() - event->pos().y();
        m_middleMoveMousePos.setX(event->pos().x());
        m_middleMoveMousePos.setY(event->pos().y());
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
        actor->setProjection(m_zoom, (float)width() ,(float)height(), 0.1f, 100.0f);
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


