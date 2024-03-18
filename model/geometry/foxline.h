#pragma once


#include <qvector3d.h>
#include <qvector2d.h>
/**
 * @brief FoxLine类来构造具有参数形式的直线直线= p + aV(直线上一个点和一个方向矢量).
 * ================================================
 * @{
 */
class FoxLine
{
public:

    FoxLine() : m_direction(QVector3D(0, 0, 0)), m_point(QVector3D(0, 0, 0)) {}
    FoxLine(const QVector3D& v, const QVector3D& p) : m_direction(v), m_point(p) {}
    FoxLine(const QVector2D& v, const QVector2D& p) { set(v, p); }
    FoxLine(float slope, float intercept) {}
    ~FoxLine() {};

    void set(const QVector3D& v, const QVector3D& p)
    {
        this->m_direction = v;
        this->m_point = p;
    }

    void set(const QVector2D& v, const QVector2D& p) {
        this->m_direction = QVector3D(v.x(), v.y(), 0);
        this->m_point = QVector3D(p.x(), p.y(), 0);
    }

    void set(float slope, float intercept)
    {
        this->m_direction = QVector3D(1, slope, 0);
        this->m_point = QVector3D(0, intercept, 0);
    }
    void setPoint(QVector3D& p) { m_point = p; }
    void setDirection(const QVector3D& v) { m_direction = v; }
    const QVector3D& getPoint() const { return m_point; }
    const QVector3D& getDirection() const { return m_direction; }
    void printSelf() {}

    //求与另一条直线相交的点
    QVector3D intersect(const FoxLine& line) const {
        const QVector3D v2 = line.getDirection();
        const QVector3D p2 = line.getPoint();
        QVector3D result = QVector3D(NAN, NAN, NAN);    // default with NaN

        // find v3 = (p2 - p1) x V2
        QVector3D v3 = QVector3D::crossProduct((p2 - m_point), v2);

        // find v4 = V1 x V2
        QVector3D v4 = QVector3D::crossProduct(m_direction, v2);

        // find (V1xV2) . (V1xV2)
        float dot = QVector3D::dotProduct(v4, v4);

        // if both V1 and V2 are same direction, return NaN point
        if (dot == 0)
            return result;

        // find a = ((p2-p1)xV2).(V1xV2) / (V1xV2).(V1xV2)
        float alpha = QVector3D::dotProduct(v3, v4) / dot;

        result = m_point + (alpha * m_direction);
        return result;

    }
    bool isIntersected(const FoxLine& line) {
        QVector3D v = QVector3D::crossProduct(m_direction, line.getDirection());
        if (v.x() == 0 && v.y() == 0 && v.z() == 0)
            return false;
        else
            return true;
    }

private:
    QVector3D m_direction; // 方向
    QVector3D m_point; // 顶点坐标
};
/**
 * ================================================.
 * @}.
 */
