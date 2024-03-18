#include "fox2dcrosssectionwidget.h"

// qt
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <qmath.h>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QRect>
#include <QPainterPath>
#include <QPainterPathStroker>


Fox2DCrossSectionWidget::Fox2DCrossSectionWidget(QWidget* parent)
{
 
    m_scale = 1.0f;

    m_painterX = 0;
    m_painterY = 0;
    m_painterWidth = 1000;
    m_painterHeight = 1000;

    m_isMouseLeftButton = false;
    m_isMouseRightButton = false;
    updatePainterWidthOfPerPixel();
    setWindowOpacity(0.7);


}

Fox2DCrossSectionWidget::~Fox2DCrossSectionWidget()
{
}

void Fox2DCrossSectionWidget::drawCrossSectionLine(const QVector<QPointF>& points)
{
    m_crossSectionLine = points;
    update();
}

void Fox2DCrossSectionWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(0,0,width(),height(),QColor(0,0,0));
    drawGuides(painter);
    drawPointAndLine(painter);
    drawCrossSectionLine(&painter);
}

void Fox2DCrossSectionWidget::mousePressEvent(QMouseEvent* event)
{

    // 左键标记顶点
    // 右键移动画布
    if (event->button() == Qt::LeftButton) {
        QPoint point = event->localPos().toPoint();
        // 判断点是否在画布中
        if (!m_drawPainterRect.contains(point)) return;

        // 判断测量点的数量是否小于2
        if (m_measurePoint.size() < 2) {
            // 判断鼠标点击的点是否是路径上的点
            if (!m_enlargedPath.contains(point)) return;
            // 将点保存起来
            m_measurePoint.push_back(point);
        }
        else
        {
            // 查找对应的点
            int index = indexOfPointInVector(m_measurePoint, point, 15);
            m_selectPoint = index;
            m_isMouseLeftButton = true;
        }
        // 更新
        update();

    }
    else if(event->button()==Qt::RightButton)
    {
        m_lastMousePos = event->pos();
        
        m_orginDifX = m_lastMousePos.x() - m_painterX;
        m_orginDifY = m_lastMousePos.y() - m_painterY;

        m_isMouseRightButton = true;

    }

}

void Fox2DCrossSectionWidget::mouseMoveEvent(QMouseEvent* event)
{
    // 点击左键触发
    if (m_isMouseLeftButton) {
        QPointF point = event->pos();
        moveMeasurePoint(point);
    }

    // 点击右键触发
    if (m_isMouseRightButton) {
        m_painterX = event->pos().x() - m_orginDifX;
        m_painterY = event->pos().y() - m_orginDifY;
    }
    update();

}

void Fox2DCrossSectionWidget::wheelEvent(QWheelEvent* event)
{
    // 向前滚动放大
    // 向后滚动缩小
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;
    if (!numPixels.isNull()) {
        //onWheelValueChanged(event->pos(), numPixels);
    }
    else if (!numDegrees.isNull()) {
        QPoint numSteps = numDegrees / 15;
       // onWheelValueChanged(event->pos(), numSteps);
    }
    event->accept();
    update();
}

void Fox2DCrossSectionWidget::mouseReleaseEvent(QMouseEvent* event)
{
    m_isMouseLeftButton = false;
    m_isMouseRightButton = false;
}

void Fox2DCrossSectionWidget::resizeEvent(QResizeEvent* event)
{
    updatePainterWidthOfPerPixel();
    centenThePainter();
}

void Fox2DCrossSectionWidget::drawGuides(QPainter& painter)
{
    int draw_width = painterWidth2DrawWidth(m_painterWidth);
    int draw_height = painterWidth2DrawWidth(m_painterHeight);

    painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap));
    m_drawPainterRect.setX(m_painterX);
    m_drawPainterRect.setY(m_painterY);
    m_drawPainterRect.setWidth(draw_width);
    m_drawPainterRect.setHeight(draw_height);
    painter.drawRect(m_drawPainterRect);



    double step_width = static_cast<double>(draw_width) / 100.0;

    int start_x = m_painterX + qRound(step_width / 2);
    int start_y = m_painterY + qRound(step_width / 2);

    // 绘制网格线条
    int lineSize = 101;
    for (int i = 0; i < lineSize; i++) {
        if(i%5==0){
            painter.setPen(QPen(Qt::white, 3, Qt::SolidLine, Qt::RoundCap));
        }
        else
        {
            painter.setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap));
        }
        int draw_lien_x1 = start_x + qRound(i * step_width);
        int draw_lien_y1 = start_y + qRound(0 * step_width);
        int draw_lien_x2 = start_x + qRound(i * step_width);
        int draw_lien_y2 = start_y + qRound(lineSize * step_width);
        painter.drawLine(draw_lien_x1, draw_lien_y1, draw_lien_x2, draw_lien_y2);
    }
    
    for (int i = 0; i < lineSize; i++) {
        if (i % 5 == 0) {
            painter.setPen(QPen(Qt::white, 3, Qt::SolidLine, Qt::RoundCap));
        }
        else
        {
            painter.setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::RoundCap));
        }
        int draw_lien_x1 = start_x + qRound(0 * step_width);
        int draw_lien_y1 = start_y + qRound(i * step_width);
        int draw_lien_x2 = start_x + qRound(lineSize * step_width);
        int draw_lien_y2 = start_y + qRound(i * step_width);
        painter.drawLine(draw_lien_x1, draw_lien_y1, draw_lien_x2, draw_lien_y2);
    }


}

void Fox2DCrossSectionWidget::drawText(const QString& text)
{



}

void Fox2DCrossSectionWidget::drawPointAndLine(QPainter& painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::green, 10,Qt::SolidLine,Qt::RoundCap));
    for (auto& point : m_measurePoint) {
        painter.drawPoint(point.x(), point.y());
        //painter.drawEllipse(point, 5, 5);
    }

    painter.setPen(QPen(Qt::yellow, 2, Qt::SolidLine));
    if (m_measurePoint.size() == 2) {
        painter.drawLine(m_measurePoint[0], m_measurePoint[1]);
    }

}

void Fox2DCrossSectionWidget::drawCrossSectionLine(QPainter* painter)
{
    int draw_width = painterWidth2DrawWidth(m_painterWidth);
    // 计算宽度对应100的比
    double step_width = static_cast<double>(draw_width) / 100.0;

    int start_x = m_painterX + qRound(step_width / 2);
    int start_y = m_painterY + qRound(step_width / 2);

    painter->setPen(QPen(Qt::blue, 5));
    // 整个网格的中心点
    int origin_x = start_x + qRound(50 * step_width);
    int origin_y = start_y + qRound(50 * step_width);

    m_crossSectionLine.clear();
    m_crossSectionLine.push_back(QPoint(origin_x - 100, origin_y - 50));
    m_crossSectionLine.push_back(QPoint(origin_x - 50, origin_y - 100));
    m_crossSectionLine.push_back(QPoint(origin_x - 50, origin_y - 100));
    m_crossSectionLine.push_back(QPoint(origin_x + 50, origin_y + 100));
    m_crossSectionLine.push_back(QPoint(origin_x + 50, origin_y + 100));
    m_crossSectionLine.push_back(QPoint(origin_x + 150, origin_y - 100));
    

    painter->drawPoint(QPoint(origin_x, origin_y));

    painter->setPen(QPen(Qt::blue, 2));
    // 绘制的默认坐标在左上角(0,0)位置
    m_drawCrossSectionLine.moveTo(m_crossSectionLine[0]); // 起始位置
    for(int i=0;i<m_crossSectionLine.size();i++){
        m_drawCrossSectionLine.lineTo(m_crossSectionLine[i]);
    }

    // 添加路径描边起 用于增加线条的判断
    QPainterPathStroker storker;
    storker.setWidth(17);
    m_enlargedPath = storker.createStroke(m_drawCrossSectionLine);

    //painter->drawLines(m_crossSectionLine);
    painter->drawPath(m_drawCrossSectionLine);
}


double Fox2DCrossSectionWidget::calcPainterWidthOfPerPixel(double scaleValue, int painterWidth, int widgetWidth)
{

    int painterWidthOfFinalShow = m_painterWidth;
    int scaledWidgetWidth = qRound(static_cast<double>(widgetWidth) * scaleValue);
    double painterWidthOfPerPixel = static_cast<double>(painterWidthOfFinalShow) / static_cast<double>(scaledWidgetWidth);
    if (painterWidthOfPerPixel < 0.0005) painterWidthOfPerPixel = 0.0005;
    return painterWidthOfPerPixel;
}

void Fox2DCrossSectionWidget::updatePainterWidthOfPerPixel()
{
    if (this->height() >= this->width()) {
        m_painterWidthOfPerPixel = calcPainterWidthOfPerPixel(m_scale, m_painterWidth, this->width());
    }
    else
    {
        m_painterWidthOfPerPixel = calcPainterWidthOfPerPixel(m_scale, m_painterWidth, this->height());
    }

}

int Fox2DCrossSectionWidget::painterWidth2DrawWidth(int painterWidth)
{
    double drawWidth = static_cast<double>(painterWidth) / m_painterWidthOfPerPixel;
    return qRound(drawWidth);
}

int Fox2DCrossSectionWidget::drawWidth2PainterWidth(int drawWidth)
{
    double paperWidth = static_cast<double>(drawWidth) * m_painterWidthOfPerPixel;
    return static_cast<int>(qRound(paperWidth));
}

void Fox2DCrossSectionWidget::onWheelValueChanged(QPoint mousePos, QPoint step)
{
    
    if (m_drawPainterRect.contains(mousePos)) {
        // 找到光标所对应到画布坐标系统的位置点，记为p0
        QPoint p0 = mousePoint2PaperPoint(mousePos);
        int temp_paper_point_x = drawWidth2PainterWidth(p0.x());
        int temp_paper_point_y = drawWidth2PainterWidth(p0.y());

        // 第二步进行缩放
        int step_value = step.y();
        m_scale += static_cast<double>(step_value) / 20.0;
        if (m_scale > SCALE_VALUE_MAX) m_scale = SCALE_VALUE_MAX;
        if (m_scale < SCALE_VALUE_MIN) m_scale = SCALE_VALUE_MIN;
        updatePainterWidthOfPerPixel();

        // 获取P1的位置
        int temp_draw_point_x = painterWidth2DrawWidth(temp_paper_point_x);
        int temp_draw_point_y = painterWidth2DrawWidth(temp_paper_point_y);
        QPoint p1(temp_draw_point_x, temp_draw_point_y);

        // P1 减去P2 得到对应的偏移量
        QPoint should_move_length = p1 - p0;
        // 将对应的偏移量设置到对应的位置
        m_painterX -= should_move_length.x();
        m_painterY -= should_move_length.y();

        update();

    }
    else
    {
        int old_width = m_drawPainterRect.width();
        int old_height = m_drawPainterRect.height();

        //resize
        int step_value = step.y();
        m_scale += static_cast<double>(step_value) / 20.0;
        if (m_scale > SCALE_VALUE_MAX) m_scale = SCALE_VALUE_MAX;
        if (m_scale < SCALE_VALUE_MIN) m_scale = SCALE_VALUE_MIN;
        updatePainterWidthOfPerPixel();

        int new_width = painterWidth2DrawWidth(m_painterWidth);
        int new_height = painterWidth2DrawWidth(m_painterHeight);

        int adjusted_height = new_height - old_height;
        int adjusted_width = new_width - old_width;

        m_painterX -= adjusted_width / 2;
        m_painterY -= adjusted_height / 2;

        update();
    }
}

/// <summary>
///  用于计算鼠标与画布之间的坐标
/// </summary>
/// <param name="point">传入鼠标的位置</param>
/// <returns>返回计算后的对应坐标</returns>
QPoint Fox2DCrossSectionWidget::mousePoint2PaperPoint(QPoint point)
{
    QPoint ret;
    ret.setX(point.x() - m_painterX);
    ret.setY(point.y() - m_painterY);
    return ret;
}


/// <summary>
/// 用于将矩形绘制在窗口中心
/// </summary>
void Fox2DCrossSectionWidget::centenThePainter()
{
    // 设置放大的比例
    m_scale = 15;
    updatePainterWidthOfPerPixel();
    // 计算窗口中心原点位置
    int adjust_distance_x = (this->width() - painterWidth2DrawWidth(m_painterWidth)) / 2;
    int adjust_distance_y = (this->height() - painterWidth2DrawWidth(m_painterHeight)) / 2;
    // 设置中心位置
    m_painterX = adjust_distance_x;
    m_painterY = adjust_distance_y;
    update();

}

/// <summary>
///  移动点
/// </summary>
/// <param name="point"></param>
void Fox2DCrossSectionWidget::moveMeasurePoint(const QPointF& point)
{

    // 移动顶点时 判断点是否在m_drawCrossSectionLine上
    if (m_selectPoint == -1) return;
    if (m_enlargedPath.contains(point)) {
        // qDebug() << point << "in path"<<" index :"<<m_selectPoint;
        m_measurePoint[m_selectPoint] = point;
    }

}

bool Fox2DCrossSectionWidget::pointsApproximatelyEqual(const QPointF& p1, const QPointF& p2, qreal tolerance)
{
    // 判断两个距离 然后判断是否在容差值范围内
    qreal distance = QLineF(p1, p2).length();
    return distance <= tolerance;
}

QPointF Fox2DCrossSectionWidget::findApproximatelyEqualPoint(const QVector<QPointF>& points, const QPointF& targetPoint, qreal tolerance)
{
    // 遍历
    for (const QPointF& point : points)
    {
        // 找出这个点是否在该范围内
        if (pointsApproximatelyEqual(point, targetPoint, tolerance))
        {
            return point;
        }
    }
    return QPointF();
}


int Fox2DCrossSectionWidget::indexOfPointInVector(const QVector<QPointF>& points, const QPointF& targetPoint, qreal tolerance)
{
    // 查找到了返回对应所以没找到返回-1
    for (int i = 0; i < points.size(); ++i)
    {
        if (pointsApproximatelyEqual(points[i], targetPoint, tolerance))
        {
            return i;
        }
    }
    return -1;
}
