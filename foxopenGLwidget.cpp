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
        //// ƽ��ģ��������
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
    //��source����Ϊָ�����͵���ɫ��������ӵ�����ɫ������
    if (!m_shaderProgram.addCacheableShaderFromSourceCode(
        QOpenGLShader::Vertex, vertex_str)) {
        qDebug() << "compiler vertex error" << m_shaderProgram.log();
    }
    if (!m_shaderProgram.addCacheableShaderFromSourceCode(
        QOpenGLShader::Fragment, fragment_str)) {
        qDebug() << "compiler fragment error" << m_shaderProgram.log();
    }
    //ʹ��addShader()����ӵ��ó������ɫ��������һ��
    if (!m_shaderProgram.link()) {
        qDebug() << "link shaderprogram error" << m_shaderProgram.log();
    }

    // ���Եķ���
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
    // openmesh��ȡ������ģ�͵Ķ���
    //m_VBO.allocate(&m_mesh.points()[0], m_mesh.n_vertices());
     
    
    // �����õķ�������
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
        //��Ϊ����ʹ������Ȳ��ԣ���Ҫ��ÿ����Ⱦ����֮ǰ�����Ȼ���
        //������ǰһ֡�������Ϣ��Ȼ�����ڻ����У�
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Z����(Z-buffer)��Ҳ����Ϊ��Ȼ���(Depth Buffer)
        glEnable(GL_DEPTH_TEST); //Ĭ�Ϲرյ�

        m_shaderProgram.bind();
        m_VAO.bind();

        // ģ�͵�λ����
        QMatrix4x4 model;
        model.scale(20.0f, 20.0f);
        m_shaderProgram.setUniformValue("model", model);

        // ��ͼ����
        m_shaderProgram.setUniformValue("view", getViewMatrix());

        // ͶӰ����
        QMatrix4x4 projection;
        projection.perspective(projectionFovy, 1.0f * width() / height(), 0.1f, 100.0f);
        m_shaderProgram.setUniformValue("projection", projection);
        // ��������stlģ��
        //glDrawArrays(GL_TRIANGLES, 0, m_mesh.n_vertices());

        // ���Ʋ����õķ�������
        for (unsigned int i = 0; i < 10; i++) {
            //����ģ�;���
            QMatrix4x4 model;
            //ƽ��
            model.translate(cubePositions[i]);
            //����ÿ��������ת���ٶȾͲ�һ��
            float angle = (i + 1.0f) * rotate;
            //��ת
            model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
            //������ɫ��������
            m_shaderProgram.setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        m_VAO.release();
        //m_VBO.release();
        m_shaderProgram.release();

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // ��ȾģʽΪ���
    //
    //// ��ʼ��Ⱦģ��
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
    QMatrix4x4 view; //�۲����
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

    // �ж���갴ť
    //Qt::MouseButtons buttons = event->buttons();
    //if (buttons & Qt::LeftButton) {
    //    // �����ת
    //    // ��������ƶ��ľ���
    //    int dx = event->x() - m_lastMousePos.x();
    //    int dy = event->y() - m_lastMousePos.y();

    //    // �����ƶ����������ת
    //    float angleX = M_PI * dy / height();
    //    float angleY = M_PI * dx / width();

    //    // ��������Ķ��㣬��������ת�ǶȽ�������任
    //    for (Cart3D::OpenTriMesh::VertexIter v_it = m_mesh.vertices_begin(); v_it != m_mesh.vertices_end(); ++v_it)
    //    {
    //        Cart3D::OpenTriMesh::Point& point = m_mesh.point(*v_it);
    //        // ��X����ת
    //        point = Cart3D::OpenTriMesh::Point(
    //            point[0],
    //            point[1] * cos(angleX) - point[2] * sin(angleX),
    //            point[1] * sin(angleX) + point[2] * cos(angleX)
    //        );
    //        // ��Y����ת
    //        point = Cart3D::OpenTriMesh::Point(
    //            point[0] * cos(angleY) + point[2] * sin(angleY),
    //            point[1],
    //            -point[0] * sin(angleY) + point[2] * cos(angleY)
    //        );
    //    }
    //}
    //else if (buttons & Qt::RightButton) {
    //    // �Ҽ��϶�
    //    // ��������ƶ��ľ���
    //    int dx = event->x() - m_lastMousePos.x();
    //    int dy = event->y() - m_lastMousePos.y();

    //    // �����ƶ��������ƽ��
    //    float translationX = dx / float(width());
    //    float translationY = -dy / float(height());

    //    // ��������Ķ��㣬������ƽ�ƾ����������任
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
    //y��������Ǵ������ϣ������෴
    //�������ƶ���������������Գ������෴����
    eulerYaw += x_offset * cameraSensitivity;
    eulerPitch -= y_offset * cameraSensitivity;

    if (eulerPitch > 89.0f)
        eulerPitch = 89.0f;
    else if (eulerPitch < -89.0f)
        eulerPitch = -89.0f;
    calculateCamera();

    update(); // �����ػ�
}

void FoxOpenGLWidget::wheelEvent(QWheelEvent* event)
{
    // ������������
    //float scaleFactor = 1.0 + event->angleDelta().y() / 1200.0;

    //// ��������Ķ��㣬�������������ӽ�������任
    //for (Cart3D::OpenTriMesh::VertexIter v_it = m_mesh.vertices_begin(); v_it != m_mesh.vertices_end(); ++v_it)
    //{
    //    Cart3D::OpenTriMesh::Point& point = m_mesh.point(*v_it);
    //    point *= scaleFactor; // ���Ŷ�������
    //}

    event->accept();
    //fovyԽС��ģ�Ϳ�����Խ��
    if (event->delta() < 0) {
        //������»���Ϊ-��������Ϊzoom out
        projectionFovy += cameraSpeed;
        if (projectionFovy > 90)
            projectionFovy = 90;
    }
    else {
        //������ϻ���Ϊ+��������Ϊzoom in
        projectionFovy -= cameraSpeed;
        if (projectionFovy < 1)
            projectionFovy = 1;
    }

    update(); // �����ػ�
}

void FoxOpenGLWidget::keyPressEvent(QKeyEvent* event)
{
    //�������ƶ���������0��
    switch (event->key()) {
    case Qt::Key_W: //��������ϣ���������
        cameraPos -= QVector3D::crossProduct(cameraFront, cameraRight).normalized() * cameraSpeed;
        break;
    case Qt::Key_S: //��������£���������
        cameraPos += QVector3D::crossProduct(cameraFront, cameraRight).normalized() * cameraSpeed;
        break;
    case Qt::Key_A: //��������󣬳�������
        cameraPos -= QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
        break;
    case Qt::Key_D: //��������ң���������
        cameraPos += QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
        break;
    case Qt::Key_E: //Զ
        cameraPos -= cameraFront * cameraSpeed;
        break;
    case Qt::Key_Q: //��
        cameraPos += cameraFront * cameraSpeed;
        break;
    default:
        break;
    }
    update();


}
