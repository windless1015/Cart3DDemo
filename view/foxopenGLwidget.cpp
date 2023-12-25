#include "foxopenGLwidget.h"

#include  "../rendering/foxcamera.h"
#include  "../rendering/foxlighting.h"
#include  "../model/foxmeshmodel.h"
#include "../model/foxmesh.h"

#include <QKeyEvent>
#include <QMatrix4x4>

#include <QtOpenGL/qgl.h>



using namespace OpenMesh;

FoxOpenGLWidget::FoxOpenGLWidget(QWidget* parent):QOpenGLWidget(parent)
{
    m_firstMouse = true;
    m_deltatime = 0.0f;
    m_lastFrame = 0.0f;
    m_elapsedTimer.start();

}

FoxOpenGLWidget::~FoxOpenGLWidget()
{
    delete m_camera;
    delete m_lighting;
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

void FoxOpenGLWidget::openMeshFolderPath(QString path)
{
     // 展示没用
    //std::string folderPath = path.toStdString();
    //m_toothMeshModel->setMeshFileFolder(folderPath);
    //m_toothMeshModel->addMesh(m_shaderProgram);
    //update();

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
    // 设置灯光
    m_lighting = new FoxLighting();
    QVector3D ambient = QVector3D(0.3f, 0.3f, 0.3f);
    QVector3D diffuse = QVector3D(0.5f, 0.5f, 0.5f);
    QVector3D specular = QVector3D(1.0f, 1.0f, 1.0f);
    QVector3D position = QVector3D(5.0f, 10.0f, 30.0f);

    m_lightPos = position;

    m_lighting->setLightingPosition(position);
    m_lighting->setLightingProperties(ambient, diffuse, specular);
    // 顶点着色器代码
    const char* vertexShaderCode = R"(#version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aNormal;
            layout (location = 2) in vec2 aTexCoords;
            
            out vec3 FragPos;
            out vec3 Normal;
            out vec2 TexCoords;
            
            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;
            void main()
            {
                FragPos = vec3(model * vec4(aPos, 1.0));
                Normal = mat3(transpose(inverse(model))) * aNormal;
                TexCoords = aTexCoords;
                gl_Position = projection * view * vec4(FragPos, 1.0);
            })";

    // 片段着色器代码
    const char* fragmentShaderCode = R"(#version 330 core
    out vec4 FragColor;

    struct Material
    {
        sampler2D diffuse;
        sampler2D specular;
        float shininess;
    };

    struct Light
    {
        vec3 position;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };

    in vec3 FragPos;
    in vec3 Normal;
    in vec2 TexCoords;
  
    uniform vec3 viewPos;
    uniform Material material;
    uniform Light light;


    void main()
    {

        vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light.position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;
    
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    }
    )";

    // 顶点着色器
    QOpenGLShader* vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vertexShader->compileSourceCode(vertexShaderCode);

    // 片段着色器
    QOpenGLShader* fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fragmentShader->compileSourceCode(fragmentShaderCode);
    // 创建着色器程序
    m_shaderProgram = new QOpenGLShaderProgram;
    m_shaderProgram->addShader(vertexShader);
    m_shaderProgram->addShader(fragmentShader);
    // 将着色器代码链接至着色器程序中
    m_shaderProgram->link();
    m_shaderProgram->bind();


    // 加载两个模型
    m_toothMeshModel = std::make_shared<FoxMeshModel>();
    // 读取牙齿文件夹路径，读取文件夹目录下的所有stl
    m_toothMeshModel->setMeshFileFolder("E:\\3D\\TestData\\testData\\DownArch");
    // 添加网格
    m_toothMeshModel->addMesh(m_shaderProgram);
    // 读取牙龈模型文件
    m_gingivaMeshModel = std::make_shared<FoxMeshModel>();
    m_gingivaMeshModel->setMeshFileName("E:\\3D\\TestData\\testData\\DownArch\\gingiva\\m_CutGumPd0_14.stl");
    m_gingivaMeshModel->addMesh(m_shaderProgram);

    m_meshPosition = QVector3D(0.0f, 0.0f, -30.0f);
    m_shaderProgram->release();
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

    // 绑定着色器1
    m_shaderProgram->bind();

    m_toothTexture->bind();
    // 设置灯光
    m_shaderProgram->setUniformValue("light.position",m_lightPos);
    m_shaderProgram->setUniformValue("light.ambient", QVector3D(0.3f,0.3f,0.3f));
    m_shaderProgram->setUniformValue("light.diffuse", QVector3D(0.7f, 0.7f, 0.7f));
    m_shaderProgram->setUniformValue("light.specular", QVector3D(1.0f, 1.0f, 1.0f));

    // 设置材质
    m_shaderProgram->setUniformValue("material.specular", QVector3D(0.5f, 0.5f, 0.5f));
    m_shaderProgram->setUniformValue("material.shininess", 64.0f);


    // 设置观察向量
    QVector3D viewPos = m_camera->getPosition();
    m_shaderProgram->setUniformValue("viewPos", viewPos);
    // 设置投影矩阵
    QMatrix4x4 projection;
    float cameraZoom = m_camera->getCameraZoom();
    projection.perspective(cameraZoom, (float)width() / (float)height(), 0.1f, 100.0f);

    QMatrix4x4 view = m_camera->getViewMatrix();
    // 模型矩阵
    QMatrix4x4 model;
    model.translate(m_meshPosition);
    model.scale(0.3f);
    // 将矩阵传入着色器程序当中
    m_shaderProgram->setUniformValue("projection", projection);
    m_shaderProgram->setUniformValue("view", view);
    m_shaderProgram->setUniformValue("model", model);
     // 绘制牙齿
     m_toothMeshModel->loadMesh(m_shaderProgram);

     // 绘制纹理 和绘制牙龈
     m_gingivaTexture->bind();
     m_gingivaMeshModel->loadMesh(m_shaderProgram);

    m_lighting->setLightingMatrix4x4(projection, view);
    m_lighting->drawLightingArrays();

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


}


