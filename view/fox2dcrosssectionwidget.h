#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
class FoxLineRenderer;
// 显示横截面窗口主要显示线条
class Fox2DCrossSectionWidget  : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	Fox2DCrossSectionWidget(QWidget* parent=nullptr);
	~Fox2DCrossSectionWidget();


// opnengl
protected:
    // 初始化
    void initializeGL() override;
    // 更新窗口大小
    void resizeGL(int w, int h) override;
    // 绘制
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
    bool m_firstMouse; //是否是第一次点击
    bool m_mouseRigthButton; // 是否是右键
    bool m_mouseLeftButton; // 是否点击左键
    QPointF m_mouseLeftClickPos; // 点击左键
    QPoint m_textPos;
};
