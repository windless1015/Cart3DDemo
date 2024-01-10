#include "foxopenGLwidget.h"

#include  "../rendering/foxcamera.h"
#include  "../rendering/foxlighting.h"
#include  "../model/foxmeshmodel.h"
#include "../model/foxmesh.h"
#include "../rendering/foxshaderprogram.h"

#include <QKeyEvent>
#include <QMatrix4x4>

#include <QtOpenGL/qgl.h>



using namespace OpenMesh;

FoxOpenGLWidget::FoxOpenGLWidget(QWidget* parent):QOpenGLWidget(parent)
{
    m_meshIsVisible = true;
    m_firstMouse = true;
    m_useTexturel = false;
    m_toothMeshModel = std::make_shared<FoxMeshModel>();
}

FoxOpenGLWidget::~FoxOpenGLWidget()
{
    // ȷ���ͷ�opengl��Դʱ��������ȷ
    makeCurrent();
    delete m_camera;
    //doneCurrent();
    std::cout << "~FoxOpenGLWidget\n";
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
    makeCurrent();
    m_shaderProgram->shaderBind();
    std::string fileName = path.toStdString();
    m_toothMeshModel->setMeshFileName(fileName);
    m_toothMeshModel->addMesh(m_shaderProgram->getShaderProgram());
    update();
    m_shaderProgram->shaderRelease();
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




void FoxOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_camera = new FoxCamera(QVector3D(0.0f, 0.0f, 3.0f));
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

    //// ��������ģ��
    //m_toothMeshModel = std::make_shared<FoxMeshModel>();
    //// ��ȡ�����ļ���·������ȡ�ļ���Ŀ¼�µ�����stl
    //m_toothMeshModel->setMeshFileFolder("E:\\3D\\TestData\\testData\\DownArch");
    //// �������
    //m_toothMeshModel->addMesh(m_shaderProgram->getShaderProgram());
    //// ��ȡ����ģ���ļ�
    //m_gingivaMeshModel = std::make_shared<FoxMeshModel>();
    //m_gingivaMeshModel->setMeshFileName("E:\\3D\\TestData\\testData\\DownArch\\gingiva\\m_CutGumPd0_14.stl");
    //m_gingivaMeshModel->addMesh(m_shaderProgram->getShaderProgram());

    m_meshPosition = QVector3D(0.0f, 0.0f, -30.0f);
    m_shaderProgram->shaderRelease();

    // �����ʼ��
    float cameraZoom = m_camera->getCameraZoom();
    m_projection.perspective(cameraZoom, (float)width() / (float)height(), 0.1f, 100.0f);
    m_view = m_camera->getViewMatrix();
    m_model.translate(m_meshPosition);
    m_model.scale(0.3f);
}

void FoxOpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}


void FoxOpenGLWidget::paintGL()
{
    // ���ڼ���������ƶ�ʱ��
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Z����(Z-buffer)��Ҳ����Ϊ��Ȼ���(Depth Buffer)
    glEnable(GL_DEPTH_TEST); //Ĭ�Ϲرյ�

    // ���ù۲�����
    QVector3D viewPos = m_camera->getPosition();
    // ����ɫ��
    m_shaderProgram->useShaderProgram(m_useTexturel,viewPos,m_projection,m_view,m_model);
     // ����
     m_toothTexture->bind();
     m_toothMeshModel->loadMesh(m_shaderProgram->getShaderProgram());


}

void FoxOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
   // std::cout << "����¼�\n";
   m_lastMousePos = event->pos();
}

void FoxOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    //std::cout << "�ƶ��¼�\n";
    event->accept();
    if(m_firstMouse){
            m_lastMousePos.setX(event->pos().x());
            m_lastMousePos.setY(event->pos().y());
            m_firstMouse = false;
    }
    float xoffset = m_lastMousePos.x()- event->pos().x();
    float yoffset = m_lastMousePos.y() - event->pos().y();
    m_lastMousePos.setX(event->pos().x());
    m_lastMousePos.setY(event->pos().y());
    float angle = 1.4f;
    m_model.rotate(angle, QVector3D(-yoffset, -xoffset, 0));
    
    update(); // �����ػ�
}

void FoxOpenGLWidget::wheelEvent(QWheelEvent* event)
{
    
    // �������ٶ�
    float speed = 1;
    // ��ȡ���ֵķ���ֵ������ǰ�����������Ǹ�
    float yoffset = event->angleDelta().y();
    // �жϹ��ֹ����ķ���
    if (yoffset > 0)
        yoffset = speed;
    if (yoffset < 0)
        yoffset = -speed;
    m_camera->wheelScrollEvent(yoffset);
    update();
}


