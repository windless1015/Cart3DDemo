
#include "foxlinerenderer.h"

#include <QDebug>
#include <QVector2D>
#include <QMatrix4x4>

FoxLineRenderer::FoxLineRenderer()
    : m_visiblity(true),m_lineWidth(1.0f),m_lineColor(QVector4D(1.0f,1.0f,1.0f,1.0f)),m_scaleFactor(1.0f)
{
    m_movePlace = QVector3D(0, 0, 0);
}

void FoxLineRenderer::setLineWidth(const float& width)
{
    m_lineWidth = width;
}

void FoxLineRenderer::setLineColor(float r, float g, float b, float alpha)
{
    m_lineColor = QVector4D(r, g, b, alpha);
}

void FoxLineRenderer::setScale(const float& scale)
{
    m_scaleFactor = scale;
}

void FoxLineRenderer::setTransformation(const float& x, const float& y)
{
    m_movePlace += QVector3D(x, y, 0);

}

void FoxLineRenderer::setVector(const QVector<QVector2D>& points)
{
    for (auto& point : points) {
        m_controlPoints.push_back(QVector3D(point.x(), point.y(), 0));
    }
}

QVector<QVector3D>& FoxLineRenderer::getVector()
{
    // TODO: 在此处插入 return 语句
    return m_controlPoints;
}

void FoxLineRenderer::setVector(const QVector<QVector3D>& controlPoints)
{
    m_controlPoints = controlPoints;
}

void FoxLineRenderer::initialize()
{
    initializeOpenGLFunctions();
    //m_VAO.create();
    if (!m_VAO.isCreated()) {
        m_VAO.create();
    }
    m_VAO.bind();

    m_VBO.create();
    m_VBO.bind();
    m_VBO.allocate(m_controlPoints.constData(), m_controlPoints.size() * sizeof(QVector3D));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), nullptr);

    m_VAO.release();
    m_VBO.release();
}

void FoxLineRenderer::render()
{
    if (!m_visiblity) return;
    glLineWidth(m_lineWidth);
    glColor4f(m_lineColor.x(),m_lineColor.y(),m_lineColor.z(),m_lineColor.w());

    glPushMatrix();
    glTranslatef(m_movePlace.x(), m_movePlace.y(), 0);
    // 缩放矩阵
    glScalef(m_scaleFactor, m_scaleFactor, 1.0f);

    m_VAO.bind();
    glDrawArrays(GL_LINES, 0, m_controlPoints.size());

    //// 加粗中间十字的线条
    //int poinsNumber = m_controlPoints.size();
    //glLineWidth(3.0f);
    //int first = poinsNumber / 2;
    //glDrawArrays(GL_LINES, first, 4);

    //// 绘制边框
    //glLineWidth(1.0f);
    //glColor4f(0.0f, 1.0f, 1.0f, 1.0);
    //glDrawArrays(GL_LINES, 0, 4);
    //glDrawArrays(GL_LINES, poinsNumber-4, 4);

    m_VAO.release();

    // 恢复原始矩阵
    glPopMatrix();

}
