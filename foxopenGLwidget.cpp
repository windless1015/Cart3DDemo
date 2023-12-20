#include "foxopenGLwidget.h"

#include "foxcamera.h"
#include  "foxlighting.h"


#include <QMatrix4x4>

#include <QtOpenGL/qgl.h>

using namespace OpenMesh;

FoxOpenGLWidget::FoxOpenGLWidget(QWidget* parent):QOpenGLWidget(parent)
{
    m_camera = new FoxCamera();
    m_camera->setPosition(QVector3D(0.0f, 0.0f, 6.0f));

}

FoxOpenGLWidget::~FoxOpenGLWidget()
{
    makeCurrent();
    m_VBO.destroy();
    m_VAO.destroy();
    doneCurrent();

    delete m_camera;
    delete m_lighting;

}

void FoxOpenGLWidget::loadSTLFile(const std::string& path)
{
    if (IO::read_mesh(m_mesh, path.data())) {
        qDebug() << "Loaded STL file: " << path.data();
        //// 平移模型至中心
        Cart3D::OpenTriMesh::Point center(0.0, 0.0, 0.0);
        for (auto v_it = m_mesh.vertices_begin(); v_it != m_mesh.vertices_end(); ++v_it) {
            center += m_mesh.point(*v_it);
        }
        center /= m_mesh.n_vertices();

        for (auto v_it = m_mesh.vertices_begin(); v_it != m_mesh.vertices_end(); ++v_it) {
            m_mesh.set_point(*v_it, m_mesh.point(*v_it) - center);
        }
        update(); // Trigger repaint
    }
    else {
        qDebug() << "Failed to load STL file: " << path.data();
    }
}

void FoxOpenGLWidget::setLoadMesh(Cart3D::OpenTriMesh mesh)
{
    this->m_mesh = mesh;
}

void FoxOpenGLWidget::setVertex(std::vector<float> vertex)
{
    m_vertex = vertex;
}



void FoxOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_lighting = new FoxLighting();
    QVector3D ambient = QVector3D(0.3f, 0.3f, 0.3f);
    QVector3D diffuse = QVector3D(0.5f, 0.5f, 0.5f);
    QVector3D specular = QVector3D(1.0f, 1.0f, 1.0f);
    QVector3D position = QVector3D(5.2f, 10.0f, 30.0f);
    m_lighting->setLightingPosition(position);
    m_lighting->setLightingProperties(ambient, diffuse, specular);
    const char* vertexShaderCode = R"(#version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aNormal;
            out vec3 FragPos;
            out vec3 Normal;
            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;
            void main()
            {
                FragPos = vec3(model * vec4(aPos, 1.0));
                Normal = mat3(transpose(inverse(model))) * aNormal;
                gl_Position = projection * view * vec4(FragPos, 1.0);
            })";

    const char* fragmentShaderCode = R"(#version 330 core
            out vec4 FragColor;

            in vec3 Normal;
            in vec3 FragPos;
  
            uniform vec3 lightPos;
            uniform vec3 viewPos;
            uniform vec3 lightColor;
            uniform vec3 objectColor;

            void main()
            {
                float ambientStrength = 0.3;
                vec3 ambient = ambientStrength * lightColor;
                vec3 norm = normalize(Normal);
                vec3 lightDir = normalize(lightPos - FragPos);
                float diff = max(dot(norm, lightDir), 0.0);
                vec3 diffuse = diff * lightColor;
                float specularStrength = 0.5; 
                vec3 viewDir = normalize(viewPos - FragPos); 
                vec3 reflectDir = reflect(-lightDir, norm);
                float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
                vec3 specular = specularStrength * spec * lightColor;
                vec3 result = (ambient + diffuse + specular) * objectColor;
                FragColor = vec4(result, 1.0);
            })";

    // 顶点着色器
    QOpenGLShader* vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    //vertexShader->compileSourceFile("E:\\learning\\OpenGL_learning\\ColorAndLightLearning\\ColorLightTest\\ShaderFile\\basic_lighting_vs.hlsli");
    vertexShader->compileSourceCode(vertexShaderCode);
    // 片段着色器
    QOpenGLShader* fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    //fragmentShader->compileSourceFile("E:\\learning\\OpenGL_learning\\ColorAndLightLearning\\ColorLightTest\\ShaderFile\\basic_lighting_fs.hlsli");
    fragmentShader->compileSourceCode(fragmentShaderCode);
    m_shaderProgram = new QOpenGLShaderProgram;
    m_shaderProgram->addShader(vertexShader);
    m_shaderProgram->addShader(fragmentShader);

    m_shaderProgram->link();
    m_shaderProgram->bind();
    m_VAO.create();
    m_VAO.bind();
   // QOpenGLVertexArrayObject::Binder{ &m_VAO };
    m_VBO.create();
    m_VBO.bind();


    m_VBO.allocate(m_vertex.data(), m_vertex.size()*sizeof(float));
    // 设置物体的颜色
    m_shaderProgram->setUniformValue("objectColor", QVector3D(0.5f, 0.5f, 0.5f));
    // 设置灯光的颜色
    m_shaderProgram->setUniformValue("lightColor", QVector3D(1.0f, 1.0f, 1.0f));
    m_shaderProgram->setAttributeBuffer("aPos", GL_FLOAT, 0, 3, 8 * sizeof(float));
    m_shaderProgram->enableAttributeArray("aPos");
    m_shaderProgram->setAttributeBuffer("aNormal", GL_FLOAT, sizeof(float) * 3, 3, 8 * sizeof(float));
    m_shaderProgram->enableAttributeArray("aNormal");
    //m_shaderProgram->setAttributeBuffer(2, GL_FLOAT, sizeof(GL_FLOAT) *6, 2, 8 * sizeof(float));
    //m_shaderProgram->enableAttributeArray(2);

    m_shaderProgram->release();
    m_VAO.release();

    m_meshPosition = QVector3D(0.0f, 0.0f, m_vertex[0]);


}

void FoxOpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}


void FoxOpenGLWidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //因为我们使用了深度测试，需要在每次渲染迭代之前清除深度缓冲
    //（否则前一帧的深度信息仍然保存在缓冲中）
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Z缓冲(Z-buffer)，也被称为深度缓冲(Depth Buffer)
    glEnable(GL_DEPTH_TEST); //默认关闭的

    m_shaderProgram->bind();

    QMatrix4x4 projection;
    projection.perspective(45.0f, (float)width() / (float)height(), 0.1f, 100.0f);

    QMatrix4x4 view = m_camera->getViewMatrix();
    //QMatrix4x4 view;
    QMatrix4x4 model;
    model.translate(m_meshPosition);
    model.scale(0.5f);

    m_shaderProgram->setUniformValue("projection", projection);
    m_shaderProgram->setUniformValue("view", view);
    m_shaderProgram->setUniformValue("model", model);

    m_VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, m_vertex.size());

    m_lighting->setLightingMatrix4x4(projection, view);
    m_lighting->drawLightingArrays();

}

void FoxOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    std::cout << "点击事件\n";
   // m_lastMousePos = event->pos();
}

void FoxOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    std::cout << "移动事件\n";
    //event->accept();
    //int x_offset = event->pos().x() - m_lastMousePos.x();
    //int y_offset = event->pos().y() - m_lastMousePos.y();
    //m_lastMousePos = event->pos();
    ////y轴的坐标是从下往上，所以相反
    ////我这里移动的是摄像机，所以场景往相反方向动
    //eulerYaw += x_offset * cameraSensitivity;
    //eulerPitch -= y_offset * cameraSensitivity;

    //if (eulerPitch > 89.0f)
    //    eulerPitch = 89.0f;
    //else if (eulerPitch < -89.0f)
    //    eulerPitch = -89.0f;
    //calculateCamera();

    //update(); // 触发重绘
}

void FoxOpenGLWidget::wheelEvent(QWheelEvent* event)
{
    ////std::cout << "滑动滚轮事件\n";
    //event->accept();
    ////fovy越小，模型看起来越大
    //if (event->delta() < 0) {
    //    //鼠标向下滑动为-，这里作为zoom out
    //    projectionFovy += cameraSpeed;
    //    if (projectionFovy > 90)
    //        projectionFovy = 90;
    //}
    //else {
    //    //鼠标向上滑动为+，这里作为zoom in
    //    projectionFovy -= cameraSpeed;
    //    if (projectionFovy < 1)
    //        projectionFovy = 1;
    //}

}

void FoxOpenGLWidget::keyPressEvent(QKeyEvent* event)
{



}
