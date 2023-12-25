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
class FoxOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
    FoxOpenGLWidget(QWidget* parent);
    ~FoxOpenGLWidget();
    // ���ö�������
    void setVertex(std::vector<float> vertex);
    // ��������
    void keyboardPressInput(QKeyEvent* event);
    // ��ȡ�ļ���
    void openMeshFolderPath(QString path);

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


private:
    std::vector<float> m_vertex;
    QVector3D m_lightPos;
    Cart3D::OpenTriMesh m_mesh;
    QPoint m_lastMousePos;
    bool m_firstMouse;
    // ��ʱ��
    QElapsedTimer m_elapsedTimer;
    float m_deltatime;
    float m_lastFrame;
    // ��ɫ������
    QOpenGLShaderProgram *m_shaderProgram;
    // �����λ��
    QVector3D m_meshPosition;
    // ���
    FoxCamera* m_camera;
    // �ƹ�
    FoxLighting* m_lighting;

    // ����ģ��
    std::shared_ptr<FoxMeshModel> m_toothMeshModel;
    // ����ģ��
    std::shared_ptr<FoxMeshModel> m_gingivaMeshModel;

    // ��������
    QOpenGLTexture* m_toothTexture;
    // ��������
    QOpenGLTexture* m_gingivaTexture;
};

