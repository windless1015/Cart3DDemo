#pragma once

#include <QWidget>
#include <QVector>
#include <QPainterPath>

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


	/**
	 * @brief ����ĺ�������дwidget���¼�.
	 */
protected:
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void resizeEvent(QResizeEvent* event);


	/**
	 * @brief ������Щ�������������ص�.
	 */
private:
	// ���ź��������
	QPainterPath scaleCrossSectionLine(QPainterPath& path, int sx, int sy);
	//�Զ�������ϵ �Դ���������Ϊ����ϵԭ��
	void painterCenterCoordinate(QPainter& painter);
	// �Զ���QRect������ϵ
	void setRect();
	// ��������ο���
	void drawGuides(QPainter& painter);
	// ���Ʋ����ı�
	void drawText(const QString& text);
	// ���Ʋ�����Ͳ�����
	void drawPointAndLine(QPainter& painter);
	// ���ƺ��������
	void drawCrossSectionLine(QPainter* painter);
	// �������ݼ���
	void testLoadData();

	// �����ǹ������ű任����Ĳ���
	double calcPaperWidthOfPerPixel(double scaleValue,
		int paperWidth,
		int widgetWidth);
	void updatePaperWidthOfPerPixel();

	int paperWidth2DrawWidth(int paperWidth);
	int drawWidth2PaperWidth(int drawWidth);
	void onWheelValueChanged(QPoint mousePos, QPoint step);

	QPoint mousePoint2PaperPoint(QPoint point);
	void centenThePaper();


	/**
	 * @brief ����ĺ�����������������������ݴ���.
	 */
private:
	// �ƶ�����
	void moveMeasurePoint(const QPointF& point);
	// �Ա��������ҵ�һ����Լ��ȵĵ�, ���ݲ�ֵΪtolerance
	bool pointsApproximatelyEqual(const QPointF& p1, const QPointF& p2, qreal tolerance);
	// ѡ�е������
	int indexOfPointInVector(const QVector<QPointF>& points, const QPointF& targetPoint, qreal tolerance);
	// ���Ҳ��ҵ��������pos�����·����
	qreal findClosestPoint(const QPointF& pos);
	// ���ڶԶ������������
	static bool comparePoints(const QPointF& point1, const QPointF& point2);
	// �������ڹ���һЩ������Y�����ر��ĵ�
	QVector<QPointF> vertexYAxisFilter(const QVector<QPointF>& vertexData,qreal maxYDifference);
	// ����������ӳ�䵽�Զ��������ϵ��
	QPoint posToCoordinatePoint(const QPoint& pos);


private:
	QVector<QPointF> m_measurePoint; // ������
	QVector<QPointF> m_crossSectionLine; // ���������
	QPainterPath m_drawCrossSectionLine; // ���ƺ����
	QPainterPath m_enlargedPath;
	double  m_scale;
	// ��¼��갴�µ�λ��
	QPoint m_lastMousePos; 
	// ��������
	int m_selectPoint;
	// ����¼�
	bool m_isMouseLeftButton;
	bool m_isMouseRightButton;
	QRect m_guides;
	QPoint m_guidesPos = QPoint(0, 0);
	QSize m_guidesWH = QSize(1000,1000);
	QPoint m_mouseRightButtonPos;
	QPoint m_orginPos;
	double m_guidesWidthOfPerPixel;
	const double SCALE_VALUE_MAX = 20.0;
	const double SCALE_VALUE_MIN = 0.5;
};



