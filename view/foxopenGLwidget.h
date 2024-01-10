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
    /// -------------------菜单事件-------------------
    // 读取文件夹
    void openMeshFolderPath(const QString& path);
    // 读取文件
    void openMeshFilePath(const QString& path);
    // 设置使用纹理
    void setUseTexture(bool useTexture);
    // 隐藏模型
    void hiddenMesh();
    // 显示模型
    void showMesh();
    // 切割
    void cuttingMesh();


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
    bool m_meshIsVisible;
    // 鼠标的位置
    QPoint m_lastMousePos; 
    // 是否是第一次鼠标操作
    bool m_firstMouse;
    // 设置是否使用材质
    bool m_useTexturel;
    // 网格的位置
    QVector3D m_meshPosition;
    // 相机 灯光 着色器
    FoxCamera* m_camera;
    FoxLighting* m_lighting;
    FoxShaderProgram* m_shaderProgram;
    // 模型矩阵 视图矩阵 投影矩阵
    QMatrix4x4 m_model;
    QMatrix4x4 m_view;
    QMatrix4x4 m_projection;

    // 牙齿模型
    std::shared_ptr<FoxMeshModel> m_toothMeshModel;
    // 牙龈模型
    std::shared_ptr<FoxMeshModel> m_gingivaMeshModel;

    // 牙齿纹理
    QOpenGLTexture* m_toothTexture;
    // 牙龈纹理
    QOpenGLTexture* m_gingivaTexture;
};

