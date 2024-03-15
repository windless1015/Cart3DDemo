#pragma once

#include <QWidget>
#include <QVector>
/**
 * @brief 这是一个2D的坐标窗口, 负责显示横截面曲线
 *  交互: 
 *      点击时如果是在样条曲线上就会生成一个点, 在点击第二个点时 则会将两点之间绘制一条测量线
 *      同时生成的点还会影像到三维空间的坐标，会在三维空间中生成对应的坐标点
 *  
 *  点
 *  网格参考线
 *  曲线
 * .
 */

class Fox2DCrossSectionWidget  :  public QWidget
{
	Q_OBJECT

public:
	Fox2DCrossSectionWidget(QWidget* parent=nullptr);
	~Fox2DCrossSectionWidget();

	// 通过不断的绘制顶点组成曲线
	void drawCrossSectionLine(const QVector<QPointF>& points);

signals:
	// 将点击的坐标点传递出去
	void sendMousePressPoint(const QPoint& point);

protected:
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void resizeEvent(QResizeEvent* event);

private:
	// 绘制网格参考线
	void drawGuides(QPainter& painter);
	// 绘制测量文本
	void drawText(const QString& text);
	// 绘制测量点和测量线
	void drawPointAndLine(QPainter& painter);
	// 绘制横截面线条
	void drawCrossSectionLine(QPainter* painter);


private:

	double calcPainterWidthOfPerPixel(double scaleValue, int painterWidth, int widgetWidth);
	void updatePainterWidthOfPerPixel();
	int painterWidth2DrawWidth(int painterWidth);
	int drawWidth2PainterWidth(int drawWidth);

	void onWheelValueChanged(QPoint mousePos, QPoint step);
	// 计算鼠标位置在画布中的相对位置
	// 鼠标 (x,y) - 当前画布的位置(x,y) 得到鼠标与画布之间的位置
	QPoint mousePoint2PaperPoint(QPoint point);
	// 绘制的矩形居中
	void centenThePainter();

	// 移动顶点
	void moveMeasurePointAndLine(const QPointF& point);
	// 对比两个点找到一个大约相等的点, 且容差值为tolerance
	bool pointsApproximatelyEqual(const QPointF& p1, const QPointF& p2, qreal tolerance);
	// 并且获取这个点
	QPointF findApproximatelyEqualPoint(const QVector<QPointF>& points, const QPointF& targetPoint, qreal tolerance);
	// 选中点的索引
	int indexOfPointInVector(const QVector<QPointF>& points, const QPointF& targetPoint, qreal tolerance);

private:
	QVector<QPointF> m_measurePoint; // 测量点
	QVector<QPointF> m_crossSectionLine; // 横截面线条
	double  m_scale;
	// 记录鼠标按下的位置
	QPoint m_lastMousePos; 
	// 顶点索引
	int m_selectPoint;

	// 画布的X Y 宽 高
	int m_painterX;
	int m_painterY;
	int m_painterWidth;
	int m_painterHeight;
	// 记录其实坐标
	int m_orginDifX;
	int m_orginDifY;

	// 鼠标事件
	bool m_isMouseLeftButton;
	bool m_isMouseRightButton;
	// 用于计算像素和画布的比例
	double m_painterWidthOfPerPixel;
	// 设置最大和最小比例
	const double SCALE_VALUE_MAX = 30.0;
	const double SCALE_VALUE_MIN = 0.5;

	QRect m_drawPainterRect;

};
