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
    // ���¼�ת�Ƹ������Ӽ�����ʱ��, ����ʱ��
    m_camera->processKeyboard(event, m_deltatime);
    update();
}

void FoxOpenGLWidget::openMeshFolderPath(QString path)
{
     // չʾû��
    //std::string folderPath = path.toStdString();
    //m_toothMeshModel->setMeshFileFolder(folderPath);
    //m_toothMeshModel->addMesh(m_shaderProgram);
    //update();

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
    // ���õƹ�
    m_lighting = new FoxLighting();
    QVector3D ambient = QVector3D(0.3f, 0.3f, 0.3f);
    QVector3D diffuse = QVector3D(0.5f, 0.5f, 0.5f);
    QVector3D specular = QVector3D(1.0f, 1.0f, 1.0f);
    QVector3D position = QVector3D(5.0f, 10.0f, 30.0f);

    m_lightPos = position;

    m_lighting->setLightingPosition(position);
    m_lighting->setLightingProperties(ambient, diffuse, specular);
    // ������ɫ������
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

    // Ƭ����ɫ������
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

    // ������ɫ��
    QOpenGLShader* vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vertexShader->compileSourceCode(vertexShaderCode);

    // Ƭ����ɫ��
    QOpenGLShader* fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fragmentShader->compileSourceCode(fragmentShaderCode);
    // ������ɫ������
    m_shaderProgram = new QOpenGLShaderProgram;
    m_shaderProgram->addShader(vertexShader);
    m_shaderProgram->addShader(fragmentShader);
    // ����ɫ��������������ɫ��������
    m_shaderProgram->link();
    m_shaderProgram->bind();


    // ��������ģ��
    m_toothMeshModel = std::make_shared<FoxMeshModel>();
    // ��ȡ�����ļ���·������ȡ�ļ���Ŀ¼�µ�����stl
    m_toothMeshModel->setMeshFileFolder("E:\\3D\\TestData\\testData\\DownArch");
    // �������
    m_toothMeshModel->addMesh(m_shaderProgram);
    // ��ȡ����ģ���ļ�
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

    // ����ɫ��1
    m_shaderProgram->bind();

    m_toothTexture->bind();
    // ���õƹ�
    m_shaderProgram->setUniformValue("light.position",m_lightPos);
    m_shaderProgram->setUniformValue("light.ambient", QVector3D(0.3f,0.3f,0.3f));
    m_shaderProgram->setUniformValue("light.diffuse", QVector3D(0.7f, 0.7f, 0.7f));
    m_shaderProgram->setUniformValue("light.specular", QVector3D(1.0f, 1.0f, 1.0f));

    // ���ò���
    m_shaderProgram->setUniformValue("material.specular", QVector3D(0.5f, 0.5f, 0.5f));
    m_shaderProgram->setUniformValue("material.shininess", 64.0f);


    // ���ù۲�����
    QVector3D viewPos = m_camera->getPosition();
    m_shaderProgram->setUniformValue("viewPos", viewPos);
    // ����ͶӰ����
    QMatrix4x4 projection;
    float cameraZoom = m_camera->getCameraZoom();
    projection.perspective(cameraZoom, (float)width() / (float)height(), 0.1f, 100.0f);

    QMatrix4x4 view = m_camera->getViewMatrix();
    // ģ�;���
    QMatrix4x4 model;
    model.translate(m_meshPosition);
    model.scale(0.3f);
    // ����������ɫ��������
    m_shaderProgram->setUniformValue("projection", projection);
    m_shaderProgram->setUniformValue("view", view);
    m_shaderProgram->setUniformValue("model", model);
     // ��������
     m_toothMeshModel->loadMesh(m_shaderProgram);

     // �������� �ͻ�������
     m_gingivaTexture->bind();
     m_gingivaMeshModel->loadMesh(m_shaderProgram);

    m_lighting->setLightingMatrix4x4(projection, view);
    m_lighting->drawLightingArrays();

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


}


