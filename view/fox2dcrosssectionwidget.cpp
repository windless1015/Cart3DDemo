#include "fox2dcrosssectionwidget.h"

#include "../rendering/foxlinerenderer.h"


#include <GL/glu.h>

#include <QDebug>
#include <QVector2D>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QPainter>
#include <QFont>

Fox2DCrossSectionWidget::Fox2DCrossSectionWidget(QWidget*parent)
	: QOpenGLWidget(parent)
{
	// ����͸����
	setWindowOpacity(0.6);
	resize(QSize(220, 340));

	m_lineRenderer = new FoxLineRenderer();
	m_midLine = new FoxLineRenderer();
	m_border = new FoxLineRenderer();
	m_testLine = new FoxLineRenderer();
	m_gridWidth = 10;
	m_scale = 1;
	m_firstMouse = true;
	m_mouseRigthButton = false;
	m_mouseLeftButton = false;
}

Fox2DCrossSectionWidget::~Fox2DCrossSectionWidget()
{
	makeCurrent();
	delete m_lineRenderer;
	delete m_border;
	delete m_midLine;
	delete m_testLine;
}

void Fox2DCrossSectionWidget::initializeGL()
{
	initializeOpenGLFunctions();
	QVector<QVector2D> points;
	QVector<QVector2D> midPoint;
	QVector<QVector2D> borderPoint;
	QVector<QVector2D> testPoint;
	for (int i = 0; i <= 50; ++i) {
		const float pos = 1.0 * (2.0 * i / 50 - 1.0);
		QVector2D transverseLine1 = QVector2D(pos, -1.0f);
		QVector2D transverseLine2 = QVector2D(pos, +1.0f);
		QVector2D verticalLine1 = QVector2D(-1.0f, pos);
		QVector2D verticalLine2 = QVector2D(+1.0f, pos);
		points.push_back(transverseLine1);
		points.push_back(transverseLine2);
		points.push_back(verticalLine1);
		points.push_back(verticalLine2);
	}

	int midNumber = points.size() / 2;
	for (int i = midNumber; i < midNumber + 4; i++) {
		midPoint.push_back(points[i]);
	}

	// �߿�
	for (int i = 0; i < 4; i++) {
		borderPoint.push_back(points[i]);
	}

	for (int i = points.size() - 4; i < points.size(); i++) {
		borderPoint.push_back(points[i]);
	}

	// -----------------------
	// ��������
	testPoint.push_back(QVector2D(0.0, 0.0));
	testPoint.push_back(QVector2D(0.0, 0.5));
	testPoint.push_back(QVector2D(0.0, 0.5));
	testPoint.push_back(QVector2D(0.5, 0.5));
	testPoint.push_back(QVector2D(0.5, 0.5));
	testPoint.push_back(QVector2D(0.5, 0.0));
	testPoint.push_back(QVector2D(0.5, 0.0));
	testPoint.push_back(QVector2D(0.0, 0.0));
	//-----------------------

	m_testLine->setVector(testPoint);
	m_testLine->initialize();
	// �߿�
	m_border->setVector(borderPoint);
	m_border->setLineColor(0.0f, 1.0f, 1.0f, 1.0f);
	m_border->initialize();
	// ������
	m_midLine->setVector(midPoint);
	m_midLine->setLineWidth(3.0f);
	m_midLine->setLineColor(0.4f, 0.4f, 0.4f, 1.0f);
	m_midLine->initialize();
	// ���������������ɫ����ʼ��
	m_lineRenderer->setVector(points); 
	m_lineRenderer->setLineColor(0.4f, 0.4f, 0.4f, 1.0f);
	m_lineRenderer->initialize();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);

}

void Fox2DCrossSectionWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Fox2DCrossSectionWidget::paintGL()
{
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_lineRenderer->render();
	m_midLine->render();
	m_border->render();
	//m_testLine->render();
	glPointSize(7.0f);
	glEnable(GL_POINT_SMOOTH);
	if(m_mouseLeftButton){
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(m_mouseLeftClickPos.x(), m_mouseLeftClickPos.y()); // Բ��
		glEnd();
		QPainter painter(this);
		painter.setFont(QFont("Arial", 10));
		painter.setPen(Qt::black);
		//qDebug() << m_mouseLeftClickPos.x() << " " << m_mouseLeftClickPos.y();
		painter.translate(m_textPos.x() + 10, m_textPos.y()+20);
		//painter.rotate(90);
		QString text = "X:"+QString::number(m_mouseLeftClickPos.x())+" Y: "+QString::number(m_mouseLeftClickPos.y());
		painter.drawText(0, 0, text);
		painter.end();
	}


}

void Fox2DCrossSectionWidget::mousePressEvent(QMouseEvent* event)
{
	event->accept();
	if (event->button() == Qt::RightButton) {
		m_mouseRightClickPos = event->pos();
		m_mouseRigthButton = true;
	}
	if (event->button() == Qt::LeftButton) {
		QPointF pos = event->localPos();
		float x = pos.x() / width() * 2 - 1;
		float y = 1 - pos.y() / height() * 2;
		// ������ĵ�
		m_mouseLeftClickPos.setX(x);
		m_mouseLeftClickPos.setY(y);
		m_textPos = event->pos();
		m_mouseLeftButton = true;
		update();
	}
}

void Fox2DCrossSectionWidget::mouseMoveEvent(QMouseEvent* event)
{
	// ������Ҽ��ƶ�
	if (m_mouseRigthButton) {
		if (m_firstMouse) {
			// ����ǵ�һ�ΰ��¼�¼��ǰ��λ��
			m_mouseRightClickPos = event->pos();
			m_firstMouse = false;
		}
		float xoffset = m_mouseRightClickPos.x() - event->pos().x();
		float yoffset = m_mouseRightClickPos.y() - event->pos().y();
		m_mouseRightClickPos = event->pos();
		float sensitivity = 0.002;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		
		m_lineRenderer->setTransformation(-xoffset, yoffset);
		m_midLine->setTransformation(-xoffset, yoffset);
		m_border->setTransformation(-xoffset, yoffset);
		m_testLine->setTransformation(-xoffset, yoffset);
	}
	update();

}

void Fox2DCrossSectionWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton) {
		m_mouseRightClickPos = QPoint(0,0);
		m_mouseRigthButton = false;
	}
	if (event->button() == Qt::LeftButton) {
		m_mouseLeftButton = false;
	}
}

void Fox2DCrossSectionWidget::wheelEvent(QWheelEvent* event)
{
	// �������ٶ�
	float speed = 1;
	// ��ȡ���ֵķ���ֵ������ǰ�����������Ǹ�
	float yoffset = event->angleDelta().y();
	// �жϹ��ֹ����ķ���
	if (yoffset > 0)
		yoffset = speed;
	if (yoffset < 0)
		yoffset = -speed;
	yoffset *= 0.1;
	// ��ȡ��ǰ�����ű���
	// ����0.1
	m_scale -= yoffset;
	if (m_scale < 0.1)
	{
		m_scale = 0.1;
		return;
	}
	if (m_scale > 4.0f)
	{
		m_scale = 4.0f;
		return;
	}

	m_lineRenderer->setScale(m_scale);
	m_midLine->setScale(m_scale);
	m_border->setScale(m_scale);
	m_testLine->setScale(m_scale);
	update();
}


