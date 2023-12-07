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

class FoxOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
	FoxOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent){ }
    ~FoxOpenGLWidget();

    // ͨ���ļ�·����������ģ��
    void loadSTLFile(std::string_view path);
    
    // ���ü�������
    void setLoadMesh(Cart3D::OpenTriMesh mesh);


protected:
    // ��ʼ��
    void initializeGL() override;
    // ���´��ڴ�С
    void resizeGL(int w, int h) override;
    // ����
    void paintGL() override;

    QMatrix4x4 getViewMatrix();

    void calculateCamera();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;


private:
    Cart3D::OpenTriMesh m_mesh;
    QPoint m_lastMousePos;
    //std::vector<float> m_vertex;

    QOpenGLShaderProgram m_shaderProgram;
    QOpenGLVertexArrayObject m_VAO;
    QOpenGLBuffer m_VBO;

    float cameraSpeed{ 0.5f }; //�ƶ��ٶ�
    float cameraSensitivity{ 0.1f }; //����϶�������
    float projectionFovy{ 45.0f }; //͸��ͶӰ��fovy��������Ұ��Χ

    int rotate{ 0 };

    //Camera Attributes
    QVector3D cameraPos{ 0.0f, 0.0f, 3.0f };
    QVector3D cameraFront{ 0.0f, 0.0f, -1.0f };
    QVector3D cameraUp{ 0.0f, 1.0f, 0.0f };
    QVector3D cameraRight{ 1.0f, 0.0f, 0.0f };

    float eulerYaw{ -90.0f }; //ƫ���ǣ���y����ת
    float eulerPitch{ 0.0f }; //�����ǣ���x����ת



};

