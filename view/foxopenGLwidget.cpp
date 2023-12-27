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
    // 确保释放opengl资源时上下文正确
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
    // 将事件转移给相机外加计算器时间, 计算时速
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
    // 设置牙齿纹理图片文件
    m_toothTexture = new QOpenGLTexture(QImage("E:\\3D\\TestData\\testData\\texture\\ToothTexture.png").mirrored());
    m_toothTexture->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
    m_toothTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    m_toothTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
    // 设置牙龈纹理图片文件
    m_gingivaTexture = new QOpenGLTexture(QImage("E:\\3D\\TestData\\testData\\texture\\GingivaTexture.png").mirrored());
    m_gingivaTexture->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::Linear);
    m_gingivaTexture->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    m_gingivaTexture->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

    // 创建着色器程序
    m_shaderProgram = new FoxShaderProgram(this);

    //// 加载两个模型
    //m_toothMeshModel = std::make_shared<FoxMeshModel>();
    //// 读取牙齿文件夹路径，读取文件夹目录下的所有stl
    //m_toothMeshModel->setMeshFileFolder("E:\\3D\\TestData\\testData\\DownArch");
    //// 添加网格
    //m_toothMeshModel->addMesh(m_shaderProgram->getShaderProgram());
    //// 读取牙龈模型文件
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
    // 用于计算相机的移动时速
    float currentFrame = m_elapsedTimer.elapsed() * 0.001;
    m_deltatime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //因为我们使用了深度测试，需要在每次渲染迭代之前清除深度缓冲
    //（否则前一帧的深度信息仍然保存在缓冲中）
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    //Z缓冲(Z-buffer)，也被称为深度缓冲(Depth Buffer)
    glEnable(GL_DEPTH_TEST); //默认关闭的

    // 设置观察向量
    QVector3D viewPos = m_camera->getPosition();

    // 设置投影矩阵
    QMatrix4x4 projection;
    float cameraZoom = m_camera->getCameraZoom();
    projection.perspective(cameraZoom, (float)width() / (float)height(), 0.1f, 100.0f);


    QMatrix4x4 view = m_camera->getViewMatrix();
    // 模型矩阵
    QMatrix4x4 model;
    model.translate(m_meshPosition);
    model.scale(0.3f);

    // 绑定着色器
    m_shaderProgram->useShaderProgram(m_useTexturel,viewPos,projection,view,model);

     // 绘制牙齿
     m_toothTexture->bind();
     m_toothMeshModel->loadMesh(m_shaderProgram->getShaderProgram());

     // 绘制纹理 和绘制牙龈
     //m_gingivaTexture->bind();
     //m_gingivaMeshModel->loadMesh(m_shaderProgram->getShaderProgram());


}

void FoxOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
   // std::cout << "点击事件\n";
   m_lastMousePos = event->pos();
}

void FoxOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    //std::cout << "移动事件\n";
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
    
    update(); // 触发重绘
}

void FoxOpenGLWidget::wheelEvent(QWheelEvent* event)
{
    // 滚动的速度
    float speed = 1;
    // 获取滚轮的返回值滚轮往前滚是正往后是负
    float yoffset = event->angleDelta().y();
    // 判断滚轮滚动的方向
    if (yoffset > 0)
        yoffset = speed;
    if (yoffset < 0)
        yoffset = -speed;
    m_camera->wheelScrollEvent(yoffset);
    update();
}


