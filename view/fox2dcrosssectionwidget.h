#pragma once

#include <QWidget>
#include <QVector>
/**
 * @brief ����һ��2D�����괰��, ������ʾ���������
 *  ����: 
 *      ���ʱ����������������Ͼͻ�����һ����, �ڵ���ڶ�����ʱ ��Ὣ����֮�����һ��������
 *      ͬʱ���ɵĵ㻹��Ӱ����ά�ռ�����꣬������ά�ռ������ɶ�Ӧ�������
 *  
 *  ��
 *  ����ο���
 *  ����
 * .
 */

class Fox2DCrossSectionWidget  :  public QWidget
{
	Q_OBJECT

public:
	Fox2DCrossSectionWidget(QWidget* parent=nullptr);
	~Fox2DCrossSectionWidget();

	// ͨ�����ϵĻ��ƶ����������
	void drawCrossSectionLine(const QVector<QPointF>& points);

signals:
	// �����������㴫�ݳ�ȥ
	void sendMousePressPoint(const QPoint& point);

protected:
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void resizeEvent(QResizeEvent* event);

private:
	// ��������ο���
	void drawGuides(QPainter& painter);
	// ���Ʋ����ı�
	void drawText(const QString& text);
	// ���Ʋ�����Ͳ�����
	void drawPointAndLine(QPainter& painter);
	// ���ƺ��������
	void drawCrossSectionLine(QPainter* painter);


private:

	double calcPainterWidthOfPerPixel(double scaleValue, int painterWidth, int widgetWidth);
	void updatePainterWidthOfPerPixel();
	int painterWidth2DrawWidth(int painterWidth);
	int drawWidth2PainterWidth(int drawWidth);

	void onWheelValueChanged(QPoint mousePos, QPoint step);
	// �������λ���ڻ����е����λ��
	// ��� (x,y) - ��ǰ������λ��(x,y) �õ�����뻭��֮���λ��
	QPoint mousePoint2PaperPoint(QPoint point);
	// ���Ƶľ��ξ���
	void centenThePainter();

	// �ƶ�����
	void moveMeasurePointAndLine(const QPointF& point);
	// �Ա��������ҵ�һ����Լ��ȵĵ�, ���ݲ�ֵΪtolerance
	bool pointsApproximatelyEqual(const QPointF& p1, const QPointF& p2, qreal tolerance);
	// ���һ�ȡ�����
	QPointF findApproximatelyEqualPoint(const QVector<QPointF>& points, const QPointF& targetPoint, qreal tolerance);
	// ѡ�е������
	int indexOfPointInVector(const QVector<QPointF>& points, const QPointF& targetPoint, qreal tolerance);

private:
	QVector<QPointF> m_measurePoint; // ������
	QVector<QPointF> m_crossSectionLine; // ���������
	double  m_scale;
	// ��¼��갴�µ�λ��
	QPoint m_lastMousePos; 
	// ��������
	int m_selectPoint;

	// ������X Y �� ��
	int m_painterX;
	int m_painterY;
	int m_painterWidth;
	int m_painterHeight;
	// ��¼��ʵ����
	int m_orginDifX;
	int m_orginDifY;

	// ����¼�
	bool m_isMouseLeftButton;
	bool m_isMouseRightButton;
	// ���ڼ������غͻ����ı���
	double m_painterWidthOfPerPixel;
	// ����������С����
	const double SCALE_VALUE_MAX = 30.0;
	const double SCALE_VALUE_MIN = 0.5;

	QRect m_drawPainterRect;

};
