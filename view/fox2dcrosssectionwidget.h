#pragma once

#include <QWidget>
#include <QVector>
#include <QPainterPath>

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


	/**
	 * @brief 下面的函数是重写widget的事件.
	 */
protected:
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void resizeEvent(QResizeEvent* event);


	/**
	 * @brief 下面这些函数是与绘制相关的.
	 */
private:
	// 缩放横截面线条
	QPainterPath scaleCrossSectionLine(QPainterPath& path, int sx, int sy);
	//自定义坐标系 以窗口中心作为坐标系原点
	void painterCenterCoordinate(QPainter& painter);
	// 自定义QRect的坐标系
	void setRect();
	// 绘制网格参考线
	void drawGuides(QPainter& painter);
	// 绘制测量文本
	void drawText(const QString& text);
	// 绘制测量点和测量线
	void drawPointAndLine(QPainter& painter);
	// 绘制横截面线条
	void drawCrossSectionLine(QPainter* painter);
	// 测试数据加载
	void testLoadData();

	// 下面是关于缩放变换网格的操作
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
	 * @brief 下面的函数是如用于搜索顶点和数据处理.
	 */
private:
	// 移动顶点
	void moveMeasurePoint(const QPointF& point);
	// 对比两个点找到一个大约相等的点, 且容差值为tolerance
	bool pointsApproximatelyEqual(const QPointF& p1, const QPointF& p2, qreal tolerance);
	// 选中点的索引
	int indexOfPointInVector(const QVector<QPointF>& points, const QPointF& targetPoint, qreal tolerance);
	// 查找并找到离给定点pos最近的路径点
	qreal findClosestPoint(const QPointF& pos);
	// 用于对顶点进行排序处理
	static bool comparePoints(const QPointF& point1, const QPointF& point2);
	// 函数用于过滤一些数据中Y轴差距特别大的点
	QVector<QPointF> vertexYAxisFilter(const QVector<QPointF>& vertexData,qreal maxYDifference);
	// 将顶点坐标映射到自定义的坐标系中
	QPoint posToCoordinatePoint(const QPoint& pos);


private:
	QVector<QPointF> m_measurePoint; // 测量点
	QVector<QPointF> m_crossSectionLine; // 横截面线条
	QPainterPath m_drawCrossSectionLine; // 绘制横截线
	QPainterPath m_enlargedPath;
	double  m_scale;
	// 记录鼠标按下的位置
	QPoint m_lastMousePos; 
	// 顶点索引
	int m_selectPoint;
	// 鼠标事件
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



