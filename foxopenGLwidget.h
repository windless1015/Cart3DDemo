#pragma once

#define _USE_MATH_DEFINES


#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>
#include <qopenglfunctions_4_5_core.h>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QtMath>

#include <QKeyEvent>


#include <common/Util/OpenMeshUtil.h>
//
class FoxCamera;
class FoxLighting;
class FoxOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
    FoxOpenGLWidget(QWidget* parent);
    ~FoxOpenGLWidget();

    // ͨ���ļ�·����������ģ��
    void loadSTLFile(const std::string& path);
    
    // ���ü�������
    void setLoadMesh(Cart3D::OpenTriMesh mesh);

    // ���ö�������
    void setVertex(std::vector<float> vertex);

protected:
    // ��ʼ��
    void initializeGL() override;
    // ���´��ڴ�С
    void resizeGL(int w, int h) override;
    // ����
    void paintGL() override;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;


private:
    Cart3D::OpenTriMesh m_mesh;
    QPoint m_lastMousePos;

    QOpenGLShaderProgram *m_shaderProgram;
    QOpenGLVertexArrayObject m_VAO;
    QOpenGLBuffer m_VBO;

    // �����λ��
    QVector3D m_meshPosition;
    std::vector<float> m_vertex;

    // ���
    FoxCamera* m_camera;
    // �ƹ�
    FoxLighting* m_lighting;
};

