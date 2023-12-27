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
#include <QElapsedTimer>
#include <QOpenGLTexture>
#include <QKeyEvent>


#include <common/Util/OpenMeshUtil.h>

class FoxCamera;
class FoxLighting;
class FoxMeshModel;
class FoxShaderProgram;
class FoxOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
    FoxOpenGLWidget(QWidget* parent);
    ~FoxOpenGLWidget();
    // 设置顶点数据
    void setVertex(std::vector<float> vertex);
    // 键盘输入
    void keyboardPressInput(QKeyEvent* event);

    /// -------------------菜单事件-------------------
    // 读取文件夹
    void openMeshFolderPath(const QString& path);
    // 读取文件
    void openMeshFilePath(const QString& path);
    // 设置使用纹理
    void setUseTexture(bool useTexture);

    // 窗口的OpenGL事件
protected:
    // 初始化
    void initializeGL() override;
    // 更新窗口大小
    void resizeGL(int w, int h) override;
    // 绘制
    void paintGL() override;

    // 窗口的交互事件
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;


private:
    std::vector<float> m_vertex;
    QVector3D m_lightPos;
    //Cart3D::OpenTriMesh m_mesh;
    // 鼠标的位置
    QPoint m_lastMousePos; 
    // 是否是第一次鼠标操作
    bool m_firstMouse;
    // 计时器
    QElapsedTimer m_elapsedTimer;
    float m_deltatime;
    float m_lastFrame;
    // 设置是否使用材质
    bool m_useTexturel;
    // 网格的位置
    QVector3D m_meshPosition;
    // 相机
    FoxCamera* m_camera;
    // 灯光
    FoxLighting* m_lighting;
    // 着色器
    FoxShaderProgram* m_shaderProgram;

    // 牙齿模型
    std::shared_ptr<FoxMeshModel> m_toothMeshModel;
    // 牙龈模型
    std::shared_ptr<FoxMeshModel> m_gingivaMeshModel;

    // 牙齿纹理
    QOpenGLTexture* m_toothTexture;
    // 牙龈纹理
    QOpenGLTexture* m_gingivaTexture;
};

