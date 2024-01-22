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
    makeCurrent();
    m_toothMeshModel->cuttingMesh();
    m_toothMeshModel->addMesh(m_shaderProgram->getShaderProgram());
    update();
}

void FoxOpenGLWidget::showSphere()
{
    if (m_renderer->getActors().size() == 0) return;
    makeCurrent();
    std::vector<QVector3D> cpts1;
    cpts1.push_back(QVector3D(-27.336922, -0.094851606, -22.03377));
    cpts1.push_back(QVector3D(-30.468161, -0.1347039, -20.110193));
    cpts1.push_back(QVector3D(-31.713745, -0.70289636, -17.194614));
    cpts1.push_back(QVector3D(-30.220974, -2.65732, -12.747708));
    cpts1.push_back(QVector3D(-26.199223, -2.8259952, -10.861499));
    cpts1.push_back(QVector3D(-22.798359, -0.83309388, -11.493107));
    cpts1.push_back(QVector3D(-20.818401, -2.0832605, -12.664121));
    cpts1.push_back(QVector3D(-20.490623, -4.0871673, -14.601606));
    cpts1.push_back(QVector3D(-20.636423, -4.1962366, -17.01095));
    cpts1.push_back(QVector3D(-21.415751, -3.6642685, -19.164167));
    cpts1.push_back(QVector3D(-23.169182, -1.9599953, -22.090446));
    for(auto& point:cpts1){
        FoxSphereSource sphere;
        sphere.setRadius(0.5f);
        sphere.setCenter(point.x(), point.y(), point.z());
        std::shared_ptr<FoxOpenGLPolyDataMapper> mapper = std::make_shared<FoxOpenGLPolyDataMapper>();
        mapper->setPolyData(sphere.getOutputPolyData());
        std::shared_ptr<FoxActor> actor = std::make_shared<FoxActor>(this);
        actor->setPolyDataMapper(mapper);
        actor->setColor(1.0f, 0.0f, 0.0f);
        m_renderer->addActor(actor);
    }
   //m_toothMeshModel->showSphere(m_shaderProgram->getShaderProgram());
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
    //QMatrix4x4 model = m_model;
    //QMatrix4x4 view = m_view;
    //QMatrix4x4 projection = m_projection;
    // // ����ɫ�� 
    // m_shaderProgram->useShaderProgram(m_useTexturel, m_viewPos, projection, view, model);
    // // ����
    // m_toothTexture->bind();
    // m_toothMeshModel->loadMesh(m_shaderProgram->getShaderProgram());
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
        //// ����ǵ�һ�ΰ������¼��λ��
        //if(m_firstMouse){
        //        m_leftMoveMousePos.setX(event->pos().x());
        //        m_leftMoveMousePos.setY(event->pos().y());
        //        m_firstMouse = false;
        //}
        //// ��һ�ε�λ�ü�ȥ��ǰ��λ�õõ��ƶ��Ľ��
        //float xoffset = m_leftMoveMousePos.x()- event->pos().x();
        //float yoffset = m_leftMoveMousePos.y() - event->pos().y();
        //m_leftMoveMousePos.setX(event->pos().x());
        //m_leftMoveMousePos.setY(event->pos().y());
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


