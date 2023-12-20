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

    // 通过文件路径加载网格模型
    void loadSTLFile(const std::string& path);
    
    // 设置加载网格
    void setLoadMesh(Cart3D::OpenTriMesh mesh);

    // 设置顶点数据
    void setVertex(std::vector<float> vertex);

protected:
    // 初始化
    void initializeGL() override;
    // 更新窗口大小
    void resizeGL(int w, int h) override;
    // 绘制
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

    // 网格的位置
    QVector3D m_meshPosition;
    std::vector<float> m_vertex;

    // 相机
    FoxCamera* m_camera;
    // 灯光
    FoxLighting* m_lighting;
};

