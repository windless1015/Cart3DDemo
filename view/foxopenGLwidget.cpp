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

    //-------------------测试渲染类-------------------
    // 北京时间 : 2024-01-18 17:42  
    // 下面的代码是测试封装的渲染类
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
        actor->setProjection(zoom, (float)width() , (float)height(), 0.1f, 100.0f);
    }

    update();
}


void FoxOpenGLWidget::paintGL()
{
    glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Z缓冲(Z-buffer)，也被称为深度缓冲(Depth Buffer)
    glEnable(GL_DEPTH_TEST); //默认关闭的

    m_renderer->renderer();
    //QMatrix4x4 model = m_model;
    //QMatrix4x4 view = m_view;
    //QMatrix4x4 projection = m_projection;
    // // 绑定着色器 
    // m_shaderProgram->useShaderProgram(m_useTexturel, m_viewPos, projection, view, model);
    // // 绘制
    // m_toothTexture->bind();
    // m_toothMeshModel->loadMesh(m_shaderProgram->getShaderProgram());
}

void FoxOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    if (m_renderer->getActors().size() == 0) return;
   // std::cout << "点击事件\n";
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
    // 如果按下的是左键就移动
    if (m_isPressMouseLeft) {
        //// 如果是第一次按下则记录下位置
        //if(m_firstMouse){
        //        m_leftMoveMousePos.setX(event->pos().x());
        //        m_leftMoveMousePos.setY(event->pos().y());
        //        m_firstMouse = false;
        //}
        //// 上一次的位置减去当前的位置得到移动的结果
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
    // 判断是否按下的是中键
    if (m_isPressMouseMiddle) {
        if (m_firstMouse) {
            // 如果是第一次按下记录当前的位置
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
        // 平移模型
        //m_model.translate(QVector3D(-xoffset, yoffset, 0));
        for (auto& actor : m_renderer->getActors()) {
            actor->setModelTranslation(QVector3D(-xoffset, yoffset, 0));
        }
    }

    update(); // 触发重绘
}

void FoxOpenGLWidget::wheelEvent(QWheelEvent* event)
{
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
        actor->setProjection(m_zoom, (float)width() ,(float)height(), 0.1f, 100.0f);
    }

    update();
}

void FoxOpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (m_renderer->getActors().size() == 0) return;
    if (event->button() == Qt::LeftButton) {
        // 松开左键后设置为false;
        m_isPressMouseLeft = false;
    }
    if (event->button() == Qt::MiddleButton) {
        m_isPressMouseMiddle = false;
    }

    

}


