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

    // 通过文件路径加载网格模型
    void loadSTLFile(std::string_view path);
    
    // 设置加载网格
    void setLoadMesh(Cart3D::OpenTriMesh mesh);


protected:
    // 初始化
    void initializeGL() override;
    // 更新窗口大小
    void resizeGL(int w, int h) override;
    // 绘制
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

    float cameraSpeed{ 0.5f }; //移动速度
    float cameraSensitivity{ 0.1f }; //鼠标拖动灵敏度
    float projectionFovy{ 45.0f }; //透视投影的fovy参数，视野范围

    int rotate{ 0 };

    //Camera Attributes
    QVector3D cameraPos{ 0.0f, 0.0f, 3.0f };
    QVector3D cameraFront{ 0.0f, 0.0f, -1.0f };
    QVector3D cameraUp{ 0.0f, 1.0f, 0.0f };
    QVector3D cameraRight{ 1.0f, 0.0f, 0.0f };

    float eulerYaw{ -90.0f }; //偏航角，绕y左右转
    float eulerPitch{ 0.0f }; //俯仰角，绕x上下转



};

