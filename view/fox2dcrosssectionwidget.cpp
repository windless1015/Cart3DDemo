#include "fox2dcrosssectionwidget.h"

// C++
#include <algorithm>

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

    m_isMouseLeftButton = false;
    m_isMouseRightButton = false;

    setWindowOpacity(0.7);
    testLoadData();

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
    //painter.scale(m_scale,m_scale);

    //painter.fillRect(0, 0,this->width(),this->height(),Qt::white);
    drawGuides(painter);
    drawCrossSectionLine(&painter);
    drawPointAndLine(painter);
    drawText(painter);
}

void Fox2DCrossSectionWidget::mousePressEvent(QMouseEvent* event)
{

    if (event->button() == Qt::LeftButton) {
        QPoint point = event->localPos().toPoint();
        if(m_pathPercent.size()<2){
            if (!m_enlargedPath.contains(point)) return;
            //  ��ȡ�������·�����ϵİٷֱ�
            qreal pathPoint = findClosestPoint(point);
            // �жϰٷֱȶ�Ӧ·���ϵ��Ǹ���
            //QPointF linePoint = m_drawCrossSectionLine.pointAtPercent(pathPoint);
            // �����Ӧ�ĵ�
            //m_measurePoint.push_back(linePoint);
            m_pathPercent.push_back(pathPoint);
        }
        else
        {
            //int index = indexOfPointInVector(m_measurePoint, point, 15);
            //qDebug() << index;
            //m_selectPoint = index;
            int index = indexOfPointInVector(m_pathPercent, point, 15);
            qDebug() << index;
            m_selectPoint = index;
            m_isMouseLeftButton = true;
        }
    }

    if (event->button() == Qt::RightButton) {
        m_orginPos = event->pos() - m_guidesPos;
        m_isMouseRightButton = true;
    }

    update();

}

void Fox2DCrossSectionWidget::mouseMoveEvent(QMouseEvent* event)
{
    // ����������
    if (m_isMouseLeftButton) {
        QPoint point = event->localPos().toPoint();
        moveMeasurePoint(point);
    }
    // ����Ҽ�����
    if (m_isMouseRightButton) {
        m_guidesPos = event->pos() - m_orginPos;
    }
    update();

}

void Fox2DCrossSectionWidget::wheelEvent(QWheelEvent* event)
{
    // ��ǰ�����Ŵ�
    // ��������С
    //QPoint numPixels = event->pixelDelta();
    //QPoint numDegrees = event->angleDelta() / 8;
    //if (!numPixels.isNull()) {
    //    qDebug() <<"numDegrees" << numDegrees;
    //}
    //else if (!numDegrees.isNull()) {
    //    QPoint numSteps = numDegrees / 15;
    //    qDebug() << "numSteps" << numSteps;
    //    if (m_scale < 0.1) m_scale = 0.1;
    //    m_scale += (numSteps.y() * 0.1);
    //}
    //event->accept();
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta() / 8;

    if (!numPixels.isNull()) {
        onWheelValueChanged(event->pos(), numPixels);
    }
    else if (!numDegrees.isNull()) {
        QPoint numSteps = numDegrees / 15;
        onWheelValueChanged(event->pos(), numSteps);
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
    updatePaperWidthOfPerPixel();
    centenThePaper();
}

void Fox2DCrossSectionWidget::painterCenterCoordinate(QPainter& painter)
{
    int x = this->width() / 2;
    int y = this->height() / 2;
    int w = this->width();
    int h = this->height();

    painter.setWindow(-x, y, w,-h);


}

void Fox2DCrossSectionWidget::setRect()
{

}

void Fox2DCrossSectionWidget::drawGuides(QPainter& painter)
{
    int draw_width = paperWidth2DrawWidth(m_guidesWH.width());
    int draw_height = paperWidth2DrawWidth(m_guidesWH.height());
    QColor editor_paper_bg_color_(27, 27, 27);
    m_guides.setX(m_guidesPos.x());
    m_guides.setY(m_guidesPos.y());
    m_guides.setWidth(draw_width);
    m_guides.setHeight(draw_height);
    painter.setBrush(Qt::gray);
    painter.drawRect(m_guides);
    //for (int i = 0; i < lineSize; i++) {
    //    if(i%5==0){
    //        painter.setPen(QPen(Qt::gray, 0.5, Qt::SolidLine, Qt::RoundCap));
    //    }
    //    else
    //    {
    //        painter.setPen(QPen(Qt::gray, 0.1, Qt::SolidLine, Qt::RoundCap));
    //    }
    //    
    //    painter.drawLine(i* interval, this->width(), i* interval, -this->width());
    //    painter.drawLine(-i * interval, this->width(), -i * interval, -this->width());
    //}


    //for (int i = 0; i < lineSize; i++) {
    //    if (i % 5 == 0) {
    //        painter.setPen(QPen(Qt::gray, 0.5, Qt::SolidLine, Qt::RoundCap));
    //    }
    //    else
    //    {
    //        painter.setPen(QPen(Qt::gray, 0.1, Qt::SolidLine, Qt::RoundCap));
    //    }
    //    painter.drawLine(this->height(), i*interval, -this->height(), i * interval);
    //    painter.drawLine(this->height(), -i * interval, -this->height(), -i * interval);
    //}

    double step_width = static_cast<double>(draw_width) / 100;

    int start_x = m_guidesPos.x() + qRound(step_width / 2);
    int start_y = m_guidesPos.y() + qRound(step_width / 2);

    int realityX = start_x+(m_guides.x() - start_x);
    int realityY = start_y+(m_guides.y() - start_y);

    //painter.setPen(QPen(Qt::red, 5));
    //painter.drawPoint(x+start_x, y+start_y);

    painter.setPen(QPen(Qt::white, 1));
    //for (int y = 0; y < 100; y++) {
    //    for (int x = 0; x < 100; x++) {
    //        int draw_point_x = start_x + qRound(x * step_width);
    //        int draw_point_y = start_y + qRound(y * step_width);
    //        // ����ˮƽ��
    //        painter.drawLine(draw_point_x, draw_point_y, draw_point_x + qRound(step_width), draw_point_y);
    //        // ���ƴ�ֱ��
    //        painter.drawLine(draw_point_x, draw_point_y, draw_point_x, draw_point_y + qRound(step_width));
    //    }
    //}
    for (int y = 0; y < 100; y++) {
        for (int x = 0; x < 100; x++) {
            int draw_point_x = realityX + qRound(x * step_width);
            int draw_point_y = realityY + qRound(y * step_width);
            if (y % 10 == 0) {
                painter.setPen(QPen(Qt::white, 3));
            }
            else {
                painter.setPen(QPen(Qt::white, 1));
            }
            // ����ˮƽ��
            painter.drawLine(draw_point_x, draw_point_y, draw_point_x + qRound(step_width), draw_point_y);
        }
    }

    for (int y = 0; y < 100; y++) {
        for (int x = 0; x < 100; x++) {
            int draw_point_x = realityX + qRound(x * step_width);
            int draw_point_y = realityY + qRound(y * step_width);
            if (x % 10 == 0) {
                painter.setPen(QPen(Qt::white, 3));
            }
            else {
                painter.setPen(QPen(Qt::white, 1));
            }
            // ���ƴ�ֱ��
            painter.drawLine(draw_point_x, draw_point_y, draw_point_x, draw_point_y + qRound(step_width));
        }
    }

    //for (int i = m_guides.left(); i < m_guides.right(); i+=boldLineInterval)
    //{
    //    if ((i - m_guides.left()) % gridSize == 0 && (i - m_guides.left()) / gridSize % boldLineInterval == 0)
    //    {
    //        pen.setWidth(2);
    //        painter.setPen(pen);
    //    }
    //    else
    //    {
    //        pen.setWidth(1);
    //        painter.setPen(pen);
    //    }
    //    painter.drawLine(i, m_guides.top(), i, m_guides.bottom());
    //}

    //for (int i = m_guides.top(); i < m_guides.bottom(); i+=boldLineInterval)
    //{
    //    if ((i - m_guides.top()) % gridSize == 0 && (i - m_guides.top()) / gridSize % boldLineInterval == 0)
    //    {
    //        pen.setWidth(2);
    //        painter.setPen(pen);
    //    }
    //    else
    //    {
    //        pen.setWidth(1);
    //        painter.setPen(pen);
    //    }
    //    if (m_scale < 1.0) {
    //        painter.drawLine(m_guides.left(), i, m_guides.right(), i);
    //    }else{
    //        painter.drawLine(m_guides.left(), i*m_scale, m_guides.right(), i*m_scale);
    //    }
    //}
}

void Fox2DCrossSectionWidget::drawText(QPainter& painter)
{
    if (m_pathPercent.size() == 2) {
        QPointF p1 = m_drawCrossSectionLine.pointAtPercent(m_pathPercent.at(0));
        QPointF p2 = m_drawCrossSectionLine.pointAtPercent(m_pathPercent.at(1));

        QFont font("����", m_scale+2,QFont::Bold);
        painter.setFont(font);
        qreal distance = QLineF(p1, p2).length();
        // �������ֵĽǶ�
        qreal angle = qRadiansToDegrees(qAtan2(p2.y() - p1.y(), p2.x() - p1.x()));
        // ���浱ǰ����ϵ״̬
        painter.save();
        // ƽ������ϵ��������ʼ��
        painter.translate((p1 + p2) / 2);
        // �������ֵߵ�������
        if (p2.x() < p1.x()) {
            angle += 180;
        }
        // ��ת����ϵʹ������ֱ��ƽ��
        painter.rotate(angle);
        // ��������
        painter.drawText(QPointF(- distance / 6, -5), "Hello");
        // �ָ�����ϵ״̬
        painter.restore();
    }
    
}

void Fox2DCrossSectionWidget::drawPointAndLine(QPainter& painter)
{
    // ���Ƶ�
    //painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap));

    painter.setBrush(Qt::red);

    if (m_pathPercent.size() == 0) return;
    QPointF point1 = m_drawCrossSectionLine.pointAtPercent(m_pathPercent.at(0));
    painter.drawEllipse(point1, 5, 5);

    if (m_pathPercent.size() == 1) return;
    QPointF point2 = m_drawCrossSectionLine.pointAtPercent(m_pathPercent.at(1));
    painter.drawEllipse(point2, 5, 5);


    // ͨ���ٷֱȽ�������Ƴ���
    if (m_pathPercent.size() == 2) {
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
        QPointF point1 = m_drawCrossSectionLine.pointAtPercent(m_pathPercent.at(0));
        QPointF point2 = m_drawCrossSectionLine.pointAtPercent(m_pathPercent.at(1));
        //painter.drawLine(m_measurePoint[0], m_measurePoint[1]);
        painter.drawLine(point1, point2);
    }


}

void Fox2DCrossSectionWidget::drawCrossSectionLine(QPainter* painter)
{

    int draw_width = paperWidth2DrawWidth(m_guidesWH.width());
    double step_width = static_cast<double>(draw_width) / 100;

    int start_x = m_guidesPos.x() + qRound(step_width / 2);
    int start_y = m_guidesPos.y() + qRound(step_width / 2);

    int realityX = start_x + (m_guides.x() - start_x);
    int realityY = start_y + (m_guides.y() - start_y);


    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);
    QVector<QPointF> filteredVertices = vertexYAxisFilter(m_crossSectionLine, 0.2);
    int x0 = realityX + qRound(filteredVertices[0].x() * step_width);
    int y0 = realityY + qRound((filteredVertices[0].y() + 40) * step_width);

    m_drawCrossSectionLine.clear();

    m_drawCrossSectionLine.moveTo(x0, y0);
    for (auto& point : filteredVertices) {
        //qDebug() << point;
        int x1 = realityX + qRound(point.x() * step_width);
        int y1 = realityY + qRound((point.y()+40) * step_width);
        m_drawCrossSectionLine.lineTo(QPointF(x1, y1));
        //painter->drawPoint(x1, y1);
    }

    QPainterPathStroker stroke;
    stroke.setWidth(5);
    m_enlargedPath = stroke.createStroke(m_drawCrossSectionLine);

    painter->drawPath(m_drawCrossSectionLine);
}

void Fox2DCrossSectionWidget::testLoadData()
{
    m_crossSectionLine.clear();
    m_drawCrossSectionLine.clear();
    //===============================
    //  ���� ��Ҫ��ֱ�Ӷ�ȡ����txt�ļ��ڵĶ���������
    // �任����
    qreal transformMatrix[3][3] = {
    {1.65, 0, 0},
    {0, -1.65, 0},
    {0, 0, 0}
    };
    // �����ļ�·��
    QString filePath = ".\\caseData\\CrossSectionTestData\\output.txt";
    // �����ļ�����
    QFile file(filePath);
    // ���ļ�
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file: " << file.errorString();
    }
    // �����ı���
    QTextStream in(&file);
    // ��ȡ�ļ�����
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        // ȷ��ÿ����3�����֣�x��y��z��
        if (parts.size() == 3)
        {
            qreal x = parts[0].toDouble();
            qreal y = parts[1].toDouble();
            qreal z = parts[2].toDouble();
            // ����ά������ת����2ά����
            qreal x1 = x * transformMatrix[0][0] + y * transformMatrix[0][1] + z * transformMatrix[0][2];
            qreal y1 = x * transformMatrix[1][0] + y * transformMatrix[1][1] + z * transformMatrix[1][2];
            QPointF point = QPointF(x1, y1);
            m_crossSectionLine.push_back(point);
        }
    }
    // �ر��ļ�
    file.close();
    //===============================

    

   // ������
    //QVector<QPointF> filteredVertices = vertexYAxisFilter(m_crossSectionLine, 0.2);

    //int draw_width = paperWidth2DrawWidth(m_guidesWH.width());
    //double step_width = static_cast<double>(draw_width) / 100;
    //int start_x = m_guidesPos.x() + qRound(step_width / 2);
    //int start_y = m_guidesPos.y() + qRound(step_width / 2);

    //int realityX = start_x + (m_guides.x() - start_x);
    //int realityY = start_y + (m_guides.y() - start_y);
    //// ������ԭ��Ϊ��ʼ��
    //double orginX = (50 / filteredVertices[0].x()) + 50;
    //double orginY = (50 / filteredVertices[0].y()) + 50;
    //int draw_point_x_orginX = realityX + qRound(orginX * step_width);
    //int draw_point_y_orginY = realityY + qRound(orginY * step_width);


    //m_drawCrossSectionLine.moveTo(QPointF(draw_point_x_orginX, draw_point_y_orginY)); // ��ʼλ��
    //for (int i = 0; i < filteredVertices.size(); i++) {
    //    double pointX = (50 / filteredVertices[i].x()) + 50;
    //    double pointY = (50 / filteredVertices[i].y()) + 50;
    //    int draw_point_x= realityX + qRound(pointX * step_width);
    //    int draw_point_y= realityY + qRound(pointY * step_width);
        //qDebug() << "x:" << draw_point_x << "y:" << draw_point_y;
        //m_drawCrossSectionLine.lineTo(filteredVertices[i]);
        //m_drawCrossSectionLine.lineTo(QPointF(draw_point_x, draw_point_y));
    //}



}

double Fox2DCrossSectionWidget::calcPaperWidthOfPerPixel(double scaleValue, int paperWidth, int widgetWidth)
{
    int paper_width_of_final_show =
        paperWidth;//+ static_cast<int>(static_cast<double>(paper_width )* 0.2);
    int scaled_widget_width = qRound(static_cast<double>(widgetWidth) * scaleValue);

    double paper_width_of_per_pixel =
        static_cast<double>(paper_width_of_final_show) /
        static_cast<double>(scaled_widget_width);

    //limit readable per-pixel value
    if (paper_width_of_per_pixel < 0.0005) paper_width_of_per_pixel = 0.0005;
    return paper_width_of_per_pixel;
}

void Fox2DCrossSectionWidget::updatePaperWidthOfPerPixel()
{
    if (this->height() >= this->width()) {
        m_guidesWidthOfPerPixel = calcPaperWidthOfPerPixel(m_scale, m_guidesWH.width(), this->width());
    }
    else {
        m_guidesWidthOfPerPixel = calcPaperWidthOfPerPixel(m_scale, m_guidesWH.width(), this->height());
    }
}

int Fox2DCrossSectionWidget::paperWidth2DrawWidth(int paperWidth)
{
    double draw_width = static_cast<double>(paperWidth) / m_guidesWidthOfPerPixel;
    return qRound(draw_width);
}

int Fox2DCrossSectionWidget::drawWidth2PaperWidth(int drawWidth)
{
    double paper_width = static_cast<double>(drawWidth) * m_guidesWidthOfPerPixel;
    return static_cast<int>(qRound(paper_width));
}

void Fox2DCrossSectionWidget::onWheelValueChanged(QPoint mousePos, QPoint step)
{
    if (m_guides.contains(mousePos)) {
        QPoint before_resize_mouse_point_at_paper = mousePoint2PaperPoint(mousePos);
        int temp_paper_point_x = drawWidth2PaperWidth(before_resize_mouse_point_at_paper.x());
        int temp_paper_point_y = drawWidth2PaperWidth(before_resize_mouse_point_at_paper.y());

        //resize
        int step_value = step.y();
        
        m_scale += static_cast<double>(step_value) / 20.0;
        if (m_scale > SCALE_VALUE_MAX) m_scale = SCALE_VALUE_MAX;
        if (m_scale < SCALE_VALUE_MIN) m_scale = SCALE_VALUE_MIN;
        updatePaperWidthOfPerPixel();

        int temp_draw_point_x = paperWidth2DrawWidth(temp_paper_point_x);
        int temp_draw_point_y = paperWidth2DrawWidth(temp_paper_point_y);
        QPoint after_resize_mouse_point_at_paper(temp_draw_point_x, temp_draw_point_y);


        QPoint should_move_length = after_resize_mouse_point_at_paper - before_resize_mouse_point_at_paper;

        m_guidesPos.setX(m_guidesPos.x() - should_move_length.x());
        m_guidesPos.setY(m_guidesPos.y() - should_move_length.y());


        update();

    }
    else { //else using center resize
        int old_width = m_guides.width();
        int old_height = m_guides.height();

        //resize
        int step_value = step.y();
        m_scale += static_cast<double>(step_value) / 20.0;
        if (m_scale > SCALE_VALUE_MAX) m_scale = SCALE_VALUE_MAX;
        if (m_scale < SCALE_VALUE_MIN) m_scale = SCALE_VALUE_MIN;
        updatePaperWidthOfPerPixel();

        int new_width = paperWidth2DrawWidth(m_guidesWH.width());
        int new_height = paperWidth2DrawWidth(m_guidesWH.height());

        int adjusted_height = new_height - old_height;
        int adjusted_width = new_width - old_width;

        m_guidesPos.setX(m_guidesPos.x() -(adjusted_width / 2));
        m_guidesPos.setY(m_guidesPos.y() - (adjusted_height / 2));

        update();
    }

}

QPoint Fox2DCrossSectionWidget::mousePoint2PaperPoint(QPoint point)
{
    QPoint ret;
    ret.setX(point.x() - m_guidesPos.x());
    ret.setY(point.y() - m_guidesPos.y());
    return ret;
}

void Fox2DCrossSectionWidget::centenThePaper()
{
    m_scale = 7;
    updatePaperWidthOfPerPixel();
    int adjust_distance_x = (this->width() - paperWidth2DrawWidth(m_guidesWH.width())) / 2;
    int adjust_distance_y = (this->height() - paperWidth2DrawWidth(m_guidesWH.height())) / 2;

    m_guidesPos.setX(adjust_distance_x);
    m_guidesPos.setY(adjust_distance_y);
    update();
}

//QPainterPath Fox2DCrossSectionWidget::scaleCrossSectionLine(QPainterPath& path, int sx, int sy)
//{
//    QPointF center = m_drawCrossSectionLine.boundingRect().center();
//    QTransform transform;
//    transform.translate(center.x(), center.y());
//    transform.scale(sx, sy);
//    //transform.translate(-center.x()+m_guides.center().x(), -center.y()+m_guides.center().y());
//    transform.translate(-center.x() , -center.y());
//    return transform.map(m_drawCrossSectionLine);
//
//}

/// <summary>
///  �ƶ���
/// </summary>
/// <param name="point"></param>
void Fox2DCrossSectionWidget::moveMeasurePoint(const QPointF& point)
{

    // �ƶ�����ʱ �жϵ��Ƿ���m_drawCrossSectionLine��
    if (m_selectPoint == -1) return;
    qreal closestPercent = findClosestPoint(point);
    // �޸Ķ�Ӧ�İٷְ�
    m_pathPercent[m_selectPoint] = closestPercent;
}

bool Fox2DCrossSectionWidget::pointsApproximatelyEqual(const QPointF& p1, const QPointF& p2, qreal tolerance)
{
    // �ж��������� Ȼ���ж��Ƿ����ݲ�ֵ��Χ��
    qreal distance = QLineF(p1, p2).length();
    return distance <= tolerance;
}



int Fox2DCrossSectionWidget::indexOfPointInVector(const QVector<QPointF>& points, const QPointF& targetPoint, qreal tolerance)
{
    // ���ҵ��˷��ض�Ӧ����û�ҵ�����-1
    for (int i = 0; i < points.size(); ++i)
    {
        if (pointsApproximatelyEqual(points[i], targetPoint, tolerance))
        {
            return i;
        }
    }
    return -1;
}

/// <summary>
///  ͨ�����������Ա�,�ж϶�Ӧ������������ϵĵ�
/// </summary>
/// <param name="pos">������������</param>
/// <returns>���ض�Ӧ·���ϵİٷֱ�</returns>
qreal Fox2DCrossSectionWidget::findClosestPoint(const QPointF& pos)
{
    qreal minDistance = std::numeric_limits<qreal>::max();
    qreal closestPercent = 0.0;
    // ����·���ϵ����е�
    for (qreal percent = 0.0; percent <= 1.0; percent += 0.001) {
        QPointF pathPoint = m_drawCrossSectionLine.pointAtPercent(percent);
        // ���������֮��ľ���
        qreal distance = QLineF(pathPoint, pos).length();
        if (distance < minDistance) {
            minDistance = distance;
            closestPercent = percent;
        }
    }

    return closestPercent;
}

bool Fox2DCrossSectionWidget::comparePoints(const QPointF& point1, const QPointF& point2)
{
    return point1.x() < point2.x();
}

QVector<QPointF> Fox2DCrossSectionWidget::vertexYAxisFilter(const QVector<QPointF>& vertexData, qreal maxYDifference)
{
    // ����һ�ݱ�֤��Ӱ��ԭ��������
    QVector<QPointF> data = vertexData;

    //�����ȴ�����������x��Ϊ��С����������
    std::sort(data.begin(), data.end(), comparePoints);

    // ������� ����һЩͻȻ�����ܴ�Ķ���
    QVector<QPointF> filteredVertices;
    for (int i = 0; i < data.size() - 1; ++i) {
        qreal diff = qAbs(data.at(i).y() - data.at(i + 1).y());
        if (diff > maxYDifference)
        {
            data.erase(data.begin() + i);
            continue;
        }
        if (diff < 0.00058) {
            data.erase(data.begin() + i);
            continue;
        }

        QPointF point = data.at(i);
        point = QPointF(point.x() * -1, point.y() * -1);
        filteredVertices.append(point);
    }

    return filteredVertices;
}

QPoint Fox2DCrossSectionWidget::posToCoordinatePoint(const QPoint& pos)
{
    return QPoint(pos.x() - (this->width() / 2), (this->height() / 2) - pos.y()) / m_scale;
}

int Fox2DCrossSectionWidget::indexOfPointInVector(const QVector<qreal>& pathpercent, const QPoint& pos, qreal tolerance)
{
    // ���ҵ��˷��ض�Ӧ����û�ҵ�����-1
    for (int i = 0; i < pathpercent.size(); ++i)
    {
        // ���ٷֱ�ת��Ϊ������
        QPointF point = m_drawCrossSectionLine.pointAtPercent(pathpercent[i]);
        if (pointsApproximatelyEqual(point, pos, tolerance))
        {
            return i;
        }
    }
    return -1;
}
