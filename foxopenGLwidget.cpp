#include "foxopenGLwidget.h"

#include <QMatrix4x4>

#include <QtOpenGL/qgl.h>

using namespace OpenMesh;

FoxOpenGLWidget::~FoxOpenGLWidget()
{
    makeCurrent();
    m_VBO.destroy();
    m_VAO.destroy();
    doneCurrent();
}

void FoxOpenGLWidget::loadSTLFile(std::string_view path)
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



void FoxOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    const char* vertex_str = R"(#version 330 core
        layout (location = 0) in vec3 inPos;
        layout (location = 1) in vec2 inTexCoord;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
        gl_Position = projection * view * model * vec4(inPos, 1.0);
       
        })";

    const char* fragment_str = R"(#version 330 core
        out vec4 fragColor;
        void main()
        {
        fragColor = vec4(1.0f, 1.0f, 1.0f, 0.0f);

        })";
    //将source编译为指定类型的着色器，并添加到此着色器程序
    if (!m_shaderProgram.addCacheableShaderFromSourceCode(
        QOpenGLShader::Vertex, vertex_str)) {
        qDebug() << "compiler vertex error" << m_shaderProgram.log();
    }
    if (!m_shaderProgram.addCacheableShaderFromSourceCode(
        QOpenGLShader::Fragment, fragment_str)) {
        qDebug() << "compiler fragment error" << m_shaderProgram.log();
    }
    //使用addShader()将添加到该程序的着色器链接在一起。
    if (!m_shaderProgram.link()) {
        qDebug() << "link shaderprogram error" << m_shaderProgram.log();
    }

    // 测试的方块
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };



    //makeCurrent();
    m_VAO.create();
    m_VAO.bind();

    m_VBO = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_VBO.create();
    m_VBO.bind();
    // openmesh读取的牙齿模型的顶点
    //m_VBO.allocate(&m_mesh.points()[0], m_mesh.n_vertices());
     
    
    // 测试用的方块数据
    m_VBO.allocate(vertices,sizeof(vertices));
     
    
    
   // position attribute
    m_shaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 5);
    m_shaderProgram.enableAttributeArray(0);

}

void FoxOpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

static QVector3D cubePositions[] = {
    QVector3D(0.0f,  0.0f,  0.0f),
    QVector3D(2.0f,  5.0f, -15.0f),
    QVector3D(-1.5f, -2.2f, -2.5f),
    QVector3D(-3.8f, -2.0f, -12.3f),
    QVector3D(2.4f, -0.4f, -3.5f),
    QVector3D(-1.7f,  3.0f, -7.5f),
    QVector3D(1.3f, -2.0f, -2.5f),
    QVector3D(1.5f,  2.0f, -2.5f),
    QVector3D(1.5f,  0.2f, -1.5f),
    QVector3D(-1.3f,  1.0f, -1.5f)
};


void FoxOpenGLWidget::paintGL()
{

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //因为我们使用了深度测试，需要在每次渲染迭代之前清除深度缓冲
        //（否则前一帧的深度信息仍然保存在缓冲中）
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Z缓冲(Z-buffer)，也被称为深度缓冲(Depth Buffer)
        glEnable(GL_DEPTH_TEST); //默认关闭的

        m_shaderProgram.bind();
        m_VAO.bind();

        // 模型单位矩阵
        QMatrix4x4 model;
        model.scale(20.0f, 20.0f);
        m_shaderProgram.setUniformValue("model", model);

        // 视图矩阵
        m_shaderProgram.setUniformValue("view", getViewMatrix());

        // 投影矩阵
        QMatrix4x4 projection;
        projection.perspective(projectionFovy, 1.0f * width() / height(), 0.1f, 100.0f);
        m_shaderProgram.setUniformValue("projection", projection);
        // 绘制牙齿stl模型
        //glDrawArrays(GL_TRIANGLES, 0, m_mesh.n_vertices());

        // 绘制测试用的方块箱子
        for (unsigned int i = 0; i < 10; i++) {
            //计算模型矩阵
            QMatrix4x4 model;
            //平移
            model.translate(cubePositions[i]);
            //这样每个箱子旋转的速度就不一样
            float angle = (i + 1.0f) * rotate;
            //旋转
            model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
            //传入着色器并绘制
            m_shaderProgram.setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        m_VAO.release();
        //m_VBO.release();
        m_shaderProgram.release();

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 渲染模式为填充
    //
    //// 开始渲染模型
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glEnableClientState(GL_VERTEX_ARRAY);
    //glBegin(GL_TRIANGLES);
    //for (Cart3D::OpenTriMesh::FaceIter f_it = m_mesh.faces_begin(); f_it != m_mesh.faces_end(); ++f_it) {
    //    for (Cart3D::OpenTriMesh::FaceVertexIter fv_it = m_mesh.fv_begin(*f_it); fv_it != m_mesh.fv_end(*f_it); ++fv_it) {
    //        Cart3D::OpenTriMesh::Point point = m_mesh.point(*fv_it);
    //        //auto normal = m_mesh.normal(*fv_it).data();
    //        glColor3f(point[0]+0.5, point[1]+0.5, point[2]+0.5);
    //        //glNormal3fv((const float*)normal);
    //        glVertex3f(point[0], point[1], point[2]);
    //    }
    //}
    //glEnd();

    //glDisableClientState(GL_VERTEX_ARRAY);




}

QMatrix4x4 FoxOpenGLWidget::getViewMatrix()
{
    QMatrix4x4 view; //观察矩阵
    view.lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    //view.lookAt(QVector3D(0.0f, 0.0f, -5.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f,0.0f));
    return view;
}

void FoxOpenGLWidget::calculateCamera()
{
    const float yaw = qDegreesToRadians(eulerYaw);
    const float pitch = qDegreesToRadians(eulerPitch);
    QVector3D front;
    front.setX(std::cos(yaw) * std::cos(pitch));
    front.setY(std::sin(pitch));
    front.setZ(std::sin(yaw) * std::cos(pitch));
    cameraFront = front.normalized();

}

void FoxOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    m_lastMousePos = event->pos();
}

void FoxOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
   // printf("void MyOpenGLWidget::mouseMoveEvent(QMouseEvent* event)\n");

    // 判断鼠标按钮
    //Qt::MouseButtons buttons = event->buttons();
    //if (buttons & Qt::LeftButton) {
    //    // 左键旋转
    //    // 计算鼠标移动的距离
    //    int dx = event->x() - m_lastMousePos.x();
    //    int dy = event->y() - m_lastMousePos.y();

    //    // 根据移动距离进行旋转
    //    float angleX = M_PI * dy / height();
    //    float angleY = M_PI * dx / width();

    //    // 遍历网格的顶点，并根据旋转角度进行坐标变换
    //    for (Cart3D::OpenTriMesh::VertexIter v_it = m_mesh.vertices_begin(); v_it != m_mesh.vertices_end(); ++v_it)
    //    {
    //        Cart3D::OpenTriMesh::Point& point = m_mesh.point(*v_it);
    //        // 绕X轴旋转
    //        point = Cart3D::OpenTriMesh::Point(
    //            point[0],
    //            point[1] * cos(angleX) - point[2] * sin(angleX),
    //            point[1] * sin(angleX) + point[2] * cos(angleX)
    //        );
    //        // 绕Y轴旋转
    //        point = Cart3D::OpenTriMesh::Point(
    //            point[0] * cos(angleY) + point[2] * sin(angleY),
    //            point[1],
    //            -point[0] * sin(angleY) + point[2] * cos(angleY)
    //        );
    //    }
    //}
    //else if (buttons & Qt::RightButton) {
    //    // 右键拖动
    //    // 计算鼠标移动的距离
    //    int dx = event->x() - m_lastMousePos.x();
    //    int dy = event->y() - m_lastMousePos.y();

    //    // 根据移动距离进行平移
    //    float translationX = dx / float(width());
    //    float translationY = -dy / float(height());

    //    // 遍历网格的顶点，并根据平移距离进行坐标变换
    //    for (Cart3D::OpenTriMesh::VertexIter v_it = m_mesh.vertices_begin(); v_it != m_mesh.vertices_end(); ++v_it)
    //    {
    //        Cart3D::OpenTriMesh::Point& point = m_mesh.point(*v_it);
    //        point[0] += translationX;
    //        point[1] += translationY;
    //    }
    //}

    //m_lastMousePos = event->pos();


    event->accept();
    int x_offset = event->pos().x() - m_lastMousePos.x();
    int y_offset = event->pos().y() - m_lastMousePos.y();
    m_lastMousePos = event->pos();
    //y轴的坐标是从下往上，所以相反
    //我这里移动的是摄像机，所以场景往相反方向动
    eulerYaw += x_offset * cameraSensitivity;
    eulerPitch -= y_offset * cameraSensitivity;

    if (eulerPitch > 89.0f)
        eulerPitch = 89.0f;
    else if (eulerPitch < -89.0f)
        eulerPitch = -89.0f;
    calculateCamera();

    update(); // 触发重绘
}

void FoxOpenGLWidget::wheelEvent(QWheelEvent* event)
{
    // 计算缩放因子
    //float scaleFactor = 1.0 + event->angleDelta().y() / 1200.0;

    //// 遍历网格的顶点，并根据缩放因子进行坐标变换
    //for (Cart3D::OpenTriMesh::VertexIter v_it = m_mesh.vertices_begin(); v_it != m_mesh.vertices_end(); ++v_it)
    //{
    //    Cart3D::OpenTriMesh::Point& point = m_mesh.point(*v_it);
    //    point *= scaleFactor; // 缩放顶点坐标
    //}

    event->accept();
    //fovy越小，模型看起来越大
    if (event->delta() < 0) {
        //鼠标向下滑动为-，这里作为zoom out
        projectionFovy += cameraSpeed;
        if (projectionFovy > 90)
            projectionFovy = 90;
    }
    else {
        //鼠标向上滑动为+，这里作为zoom in
        projectionFovy -= cameraSpeed;
        if (projectionFovy < 1)
            projectionFovy = 1;
    }

    update(); // 触发重绘
}

void FoxOpenGLWidget::keyPressEvent(QKeyEvent* event)
{
    //横向是移动，不是绕0点
    switch (event->key()) {
    case Qt::Key_W: //摄像机往上，场景往下
        cameraPos -= QVector3D::crossProduct(cameraFront, cameraRight).normalized() * cameraSpeed;
        break;
    case Qt::Key_S: //摄像机往下，场景往上
        cameraPos += QVector3D::crossProduct(cameraFront, cameraRight).normalized() * cameraSpeed;
        break;
    case Qt::Key_A: //摄像机往左，场景往右
        cameraPos -= QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
        break;
    case Qt::Key_D: //摄像机往右，场景往左
        cameraPos += QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
        break;
    case Qt::Key_E: //远
        cameraPos -= cameraFront * cameraSpeed;
        break;
    case Qt::Key_Q: //近
        cameraPos += cameraFront * cameraSpeed;
        break;
    default:
        break;
    }
    update();


}
