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
    // ���ö�������
    void setVertex(std::vector<float> vertex);
    // ��������
    void keyboardPressInput(QKeyEvent* event);

    /// -------------------�˵��¼�-------------------
    // ��ȡ�ļ���
    void openMeshFolderPath(const QString& path);
    // ��ȡ�ļ�
    void openMeshFilePath(const QString& path);
    // ����ʹ������
    void setUseTexture(bool useTexture);

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


private:
    std::vector<float> m_vertex;
    QVector3D m_lightPos;
    //Cart3D::OpenTriMesh m_mesh;
    // ����λ��
    QPoint m_lastMousePos; 
    // �Ƿ��ǵ�һ��������
    bool m_firstMouse;
    // ��ʱ��
    QElapsedTimer m_elapsedTimer;
    float m_deltatime;
    float m_lastFrame;
    // �����Ƿ�ʹ�ò���
    bool m_useTexturel;
    // �����λ��
    QVector3D m_meshPosition;
    // ���
    FoxCamera* m_camera;
    // �ƹ�
    FoxLighting* m_lighting;
    // ��ɫ��
    FoxShaderProgram* m_shaderProgram;

    // ����ģ��
    std::shared_ptr<FoxMeshModel> m_toothMeshModel;
    // ����ģ��
    std::shared_ptr<FoxMeshModel> m_gingivaMeshModel;

    // ��������
    QOpenGLTexture* m_toothTexture;
    // ��������
    QOpenGLTexture* m_gingivaTexture;
};

