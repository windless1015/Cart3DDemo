#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
class FoxLineRenderer;
// ��ʾ����洰����Ҫ��ʾ����
class Fox2DCrossSectionWidget  : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	Fox2DCrossSectionWidget(QWidget* parent=nullptr);
	~Fox2DCrossSectionWidget();


// opnengl
protected:
    // ��ʼ��
    void initializeGL() override;
    // ���´��ڴ�С
    void resizeGL(int w, int h) override;
    // ����
    void paintGL() override;


// widget
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent* event);

private:
    QPoint m_mouseRightClickPos;
    FoxLineRenderer* m_lineRenderer;
    FoxLineRenderer* m_midLine;
    FoxLineRenderer* m_border;
    FoxLineRenderer* m_testLine;
    int m_gridWidth;
    float m_scale;
    bool m_firstMouse; //�Ƿ��ǵ�һ�ε��
    bool m_mouseRigthButton; // �Ƿ����Ҽ�
    bool m_mouseLeftButton; // �Ƿ������
    QPointF m_mouseLeftClickPos; // ������
    QPoint m_textPos;
};
