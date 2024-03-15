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

      
    /// -------------------�˵��¼�-------------------
    // ��ȡ�ļ���
    void openMeshFolderPath(const QString& path);
    // ��ȡ�ļ�
    void openMeshFilePath(const QString& path);
    void openMeshFilePath(const QString& upper, const QString& lower);
    void openMeshFilePath(const QVector<QString>& tooth, const QString& gum);
    // ����ʹ������
    void setUseTexture(bool useTexture);
    // ����ģ��
    void hiddenMesh();
    // ��ʾģ��
    void showMesh();
    // �и�
    void cuttingMesh();
    // ��ʾС��
    void showSphereAndLine();
    // ���ó�����ģ�͵�͸����
    void setActorAlpha(float alpha);

    // ���ڵ�OpenGL�¼�
protected:
    // ��ʼ��
    void initializeGL() override;
    // ���´��ڴ�С
    void resizeGL(int w, int h) override;
    // ����
    void paintGL() override;

    // ���ڵĽ����¼�
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
    // ����λ��
    QPoint m_leftMoveMousePos; 
    QPoint m_middleMoveMousePos;
    // �Ƿ��ǵ�һ��������
    bool m_firstMouse;
    bool m_isPressMouseLeft;
    bool m_isPressMouseMiddle;
    // �����Ƿ�ʹ�ò���
    bool m_useTexturel;
    // �����λ��
    QVector3D m_meshPosition;
    // ��� �ƹ� ��ɫ��
    FoxCamera* m_camera;
    FoxLighting* m_lighting;
    FoxShaderProgram* m_shaderProgram;
    // ģ�;��� ��ͼ���� ͶӰ����
    QMatrix4x4 m_model;
    QMatrix4x4 m_view;
    QMatrix4x4 m_projection;
    QVector3D m_viewPos;
    float m_zoom;
    QQuaternion m_rotateQuat; // ��Ԫ��
    QVector3D m_rotateAxis; // ��ת��
    float m_angle; // �Ƕ�
    // ����ģ��
    std::shared_ptr<FoxMeshModel> m_toothMeshModel;
    // ����ģ��
    std::shared_ptr<FoxMeshModel> m_gingivaMeshModel;

    // ��������
    QOpenGLTexture* m_toothTexture;
    // ��������
    QOpenGLTexture* m_gingivaTexture;
};

