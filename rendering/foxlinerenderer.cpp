
#include "foxlinerenderer.h"

#include <QDebug>

FoxLineRenderer::FoxLineRenderer()
    : m_visiblity(true)
{



}

void FoxLineRenderer::setVector(const QVector<QVector3D>& controlPoints)
{

    m_controlPoints = controlPoints;
    // 为了保证闭环将起始的顶点插入一个到尾部
    QVector3D beginPoint = *controlPoints.begin();
    m_controlPoints.push_back(beginPoint);
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
    glLineWidth(5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    m_VAO.bind();
    glDrawArrays(GL_LINE_STRIP, 0, m_controlPoints.size());
    m_VAO.release();
}
