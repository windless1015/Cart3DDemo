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

class FoxCamera;
class FoxLighting;
class FoxMeshModel;
class FoxShaderProgram;
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
    // ����ʹ������
    void setUseTexture(bool useTexture);
    // ����ģ��
    void hiddenMesh();
    // ��ʾģ��
    void showMesh();
    // �и�
    void cuttingMesh();
    // ��ʾС��
    void showSphere();

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

private:
    //---------test------------
    std::shared_ptr<FoxRenderer> m_renderer;
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

