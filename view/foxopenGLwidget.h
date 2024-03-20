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


#include "QMessageBox"

// test
class FoxRenderer;
class FoxPipeSource;
//======

class FoxCamera;
class FoxLighting;
class FoxMeshModel;
class FoxShaderProgram;
class FoxLineRenderer;
class FoxOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
    FoxOpenGLWidget(QWidget* parent);
    ~FoxOpenGLWidget();    

      
    /// -------------------菜单事件-------------------
    // 读取文件夹
    void openMeshFolderPath(const QString& path);

    //读取附件文件,并移动到指定位置
    void FoxOpenGLWidget::openAttachmentFilePath(const QString& path, QVector3D& qv3d);

    // 读取文件
    void openMeshFilePath(const QString& path);
    void openMeshFilePath(const QString& upper, const QString& lower);
    // 设置使用纹理
    void openMeshFilePath(const QVector<QString>& tooth, const QString& gum);
    void setUseTexture(bool useTexture);
    // 隐藏模型
    void hiddenMesh();
    // 显示模型
    void showMesh();
    // 切割
    void cuttingMesh();
    // 显示小球
    void showSphereAndLine();
    // 设置场景中模型的透明度
    void setActorAlpha(float alpha);

    //wxn
    /**
     * @brief 因为qt的鼠标事件获取的点所在的坐标轴，原点在左上角，而且y轴方向朝下,而我们计算旋转轴时所用的坐标轴，原点在旋转中心，也就是视口中心，y轴方向朝上
     * @param p_ab 用于拟合平面的点集
     * @return 
     */
    void translate_point(QPoint& p_ab);
    void setPressPosition(QPoint p_ab);


    void generateGridVertices(int rows, int cols);

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
    void mouseReleaseEvent(QMouseEvent* event) override;


    //---------------------- test
    QVector<QVector3D> buildSpiralPath(float r1, float r2, float h1, float h2,
        float turns, int points);
    QVector<QVector3D> buildSpiralPath(QVector3D r1, QVector3D r2, float h1, float h2,
        float turns, int points);
    QVector<QVector3D> buildCircle(float radius, int steps);

    QVector<QPointF> m_points;

    QPointF calculateCircleCenter(const QPointF& p1, const QPointF& p2, const QPointF& p3)
    {
        float x1 = p1.x(), y1 = p1.y();
        float x2 = p2.x(), y2 = p2.y();
        float x3 = p3.x(), y3 = p3.y();

        float ma = (y2 - y1) / (x2 - x1);
        float mb = (y3 - y2) / (x3 - x2);

        float centerX = (ma * mb * (y1 - y3) + mb * (x1 + x2) - ma * (x2 + x3)) / (2 * (mb - ma));
        float centerY = -1 * (centerX - (x1 + x2) / 2) / ma + (y1 + y2) / 2;

        return QPointF(centerX, centerY);
    }


private:
    //---------test------------
    std::shared_ptr<FoxRenderer> m_renderer;
    std::vector<std::shared_ptr<FoxLineRenderer>> m_lineRenderer;

    std::shared_ptr<FoxPipeSource> m_foxPipeSource;
    QVector<QVector3D> m_path;
    QVector<QVector3D> m_circle;
    //------------------------

    bool m_meshIsVisible;
    // 鼠标的位置
    QPoint m_leftMoveMousePos; 
    QPoint m_middleMoveMousePos;
    // 是否是第一次鼠标操作
    bool m_firstMouse;
    bool m_isPressMouseLeft;
    bool m_isPressMouseMiddle;
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
    QVector3D m_viewPos;
    float m_zoom;
    QQuaternion m_rotateQuat; // 四元数
    QVector3D m_rotateAxis; // 旋转轴
    float m_angle; // 角度
    // 牙齿模型
    std::shared_ptr<FoxMeshModel> m_toothMeshModel;
    // 牙龈模型
    std::shared_ptr<FoxMeshModel> m_gingivaMeshModel;

    // 牙齿纹理
    QOpenGLTexture* m_toothTexture;
    // 牙龈纹理
    QOpenGLTexture* m_gingivaTexture;
    //鼠标位置
    QPoint mousePos;
    //
    QVector3D rotationAxis;
    QQuaternion rotationQuat;

    //
    QMatrix4x4 modelUse;
    QMatrix4x4 modelSave;
    QPoint press_position;


    QOpenGLShaderProgram* gridProgram;
    QVector<QVector2D> gridVertices; // Store grid vertices
};

