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
    m_firstMouse = true;
    m_useTexturel = false;
    m_deltatime = 0.0f;
    m_lastFrame = 0.0f;
    m_elapsedTimer.start();
    m_toothMeshModel = std::make_shared<FoxMeshModel>();
}

FoxOpenGLWidget::~FoxOpenGLWidget()
{
    // ȷ���ͷ�opengl��Դʱ��������ȷ
    makeCurrent();
    delete m_camera;
    doneCurrent();
}

void FoxOpenGLWidget::setVertex(std::vector<float> vertex)
{
    m_vertex = vertex;
}

void FoxOpenGLWidget::keyboardPressInput(QKeyEvent* event)
{
    // ���¼�ת�Ƹ������Ӽ�����ʱ��, ����ʱ��
    m_camera->processKeyboard(event, m_deltatime);
    update();
}

void FoxOpenGLWidget::openMeshFolderPath(const QString& path)
{
    makeCurrent();
    //m_shaderProgram->bind();
    m_shaderProgram->shaderBind();
    std::string folderPath = path.toStdString();
    m_toothMeshModel->setMeshFileFolder(folderPath);
    m_toothMeshModel->addMesh(m_shaderProgram->getShaderProgram());
    update();
    //m_shaderProgram->release();
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



void FoxOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_camera = new FoxCamera(QVector3D(0.0f, 0.0f, 6.0f));
    // ������������ͼƬ�ļ�
    m_toothTexture = new QOpenGLTexture(QImage("E:\\3D\\TestData\\testData\\texture\\ToothTexture.png").mirrored());
    m_toothTexture->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
    m_toothTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    m_toothTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
    // ������������ͼƬ�ļ�
    m_gingivaTexture = new QOpenGLTexture(QImage("E:\\3D\\TestData\\testData\\texture\\GingivaTexture.png").mirrored());
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
}

void FoxOpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}


void FoxOpenGLWidget::paintGL()
{
    // ���ڼ���������ƶ�ʱ��
    float currentFrame = m_elapsedTimer.elapsed() * 0.001;
    m_deltatime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //��Ϊ����ʹ������Ȳ��ԣ���Ҫ��ÿ����Ⱦ����֮ǰ�����Ȼ���
    //������ǰһ֡�������Ϣ��Ȼ�����ڻ����У�
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    //Z����(Z-buffer)��Ҳ����Ϊ��Ȼ���(Depth Buffer)
    glEnable(GL_DEPTH_TEST); //Ĭ�Ϲرյ�

    // ���ù۲�����
    QVector3D viewPos = m_camera->getPosition();

    // ����ͶӰ����
    QMatrix4x4 projection;
    float cameraZoom = m_camera->getCameraZoom();
    projection.perspective(cameraZoom, (float)width() / (float)height(), 0.1f, 100.0f);


    QMatrix4x4 view = m_camera->getViewMatrix();
    // ģ�;���
    QMatrix4x4 model;
    model.translate(m_meshPosition);
    model.scale(0.3f);

    // ����ɫ��
    m_shaderProgram->useShaderProgram(m_useTexturel,viewPos,projection,view,model);

     // ��������
     m_toothTexture->bind();
     m_toothMeshModel->loadMesh(m_shaderProgram->getShaderProgram());

     // �������� �ͻ�������
     //m_gingivaTexture->bind();
     //m_gingivaMeshModel->loadMesh(m_shaderProgram->getShaderProgram());


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
    m_camera->processMouseMovement(xoffset, yoffset);
    
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


