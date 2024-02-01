#pragma once

#include "foxline.h"

#include <qvector3d.h>

/**
* @brief FoxPlane 类 ，用于具有法向量(a,b,c)和点(x0,y0,z0)的3D平面Ax + by + cz + d = 0，其中d = -(ax0 + by0 + cz0)
* ================================================
* @{
*/
class FoxPlane
{
public:
    // ctor/dtor
    FoxPlane() :m_normal(QVector3D(0, 0, 1)), m_d(0), m_normalLength(1), m_distance(0) {}

    //平面方程的 / 4系数
    FoxPlane(float a, float b, float c, float d) { set(a, b, c, d); }

    // 平面上的一个点和法向量
    FoxPlane(const QVector3D& normal, const QVector3D& point) {
        set(normal, point);
    }
    ~FoxPlane() {}

    void set(float a, float b, float c, float d) {
        m_normal= QVector3D(a,b,c);
        m_normal.setX(a);
        m_normal.setY(b);
        m_normal.setZ(c);
        this->m_d = d;

        // compute distance
        m_normalLength = sqrtf(a * a + b * b + c * c);
        m_distance = -m_d / m_normalLength;
    };
    // set with  a point on the plane and normal
    void set(const QVector3D& normal, const QVector3D& point) {
        this->m_normal = normal;
        m_normalLength = normal.length();
        m_d = -QVector3D::dotProduct(m_normal,point);         // -(a*x0 + b*y0 + c*z0)
        m_distance = -m_d / m_normalLength;
    };
    const QVector3D& getNormal() const { return m_normal; }
    float getD() const { return  m_d; }                        // return 4th coefficient
    float getNormalLength() const { return  m_normalLength; }  // return length of normal
    float getDistance() const { return  m_distance; };         // return distance from the origin

    // 从该点返回的距离
    float getDistance(const QVector3D& point) {
        float dot = QVector3D::dotProduct(m_normal, point);
        return (dot + m_d) / m_normalLength;
    }

    void normalize() {
        float lengthInv = 1.0f / m_normalLength;
        m_normal *= lengthInv;
        m_normalLength = 1.0f;
        m_d *= lengthInv;
        m_distance = -m_d;
    };

    QVector3D intersect(const FoxLine& line) const {
        // from line = p + t * v
        QVector3D p = line.getPoint();        // (x0, y0, z0)
        QVector3D v = line.getDirection();    // (x,  y,  z)

        // dot products
        float dot1 = QVector3D::dotProduct(m_normal, p);         // a*x0 + b*y0 + c*z0
        float dot2 = QVector3D::dotProduct(m_normal, v);         // a*x + b*y + c*z

        // if denominator=0, no intersect
        if (dot2 == 0)
            return QVector3D(NAN, NAN, NAN);

        // find t = -(a*x0 + b*y0 + c*z0 + d) / (a*x + b*y + c*z)
        float t = -(dot1 + m_d) / dot2;

        // find intersection point
        return p + (v * t);
    };

    FoxLine intersect(const FoxPlane& rhs) const {
        // find direction vector of the intersection line
        QVector3D v = QVector3D::crossProduct(m_normal, rhs.getNormal());

        // if |direction| = 0, 2 planes are parallel (no intersect)
        // return a line with NaN
        if (v.x() == 0 && v.y() == 0 && v.z() == 0)
            return FoxLine(QVector3D(NAN, NAN, NAN), QVector3D(NAN, NAN, NAN));

        // find a point on the line, which is also on both planes
        // choose simple plane where d=0: ax + by + cz = 0
        float dot = QVector3D::dotProduct(v, v);                       // V dot V
        QVector3D n1 = rhs.getD() * m_normal;           // d2 * N1
        QVector3D n2 = -m_d * rhs.getNormal();          //-d1 * N2
        QVector3D p = QVector3D::crossProduct((n1 + n2), v) / dot;       // (d2*N1-d1*N2) X V / V dot V

        return FoxLine(v, p);
    };

    bool isIntersected(const FoxLine& line) const {
        // direction vector of line
        QVector3D v = line.getDirection();

        // dot product with normal of the plane
        float dot = QVector3D::dotProduct(m_normal, v);  // a*Vx + b*Vy + c*Vz

        if (dot == 0)
            return false;
        else
            return true;
    };
    bool isIntersected(const FoxPlane& plane) const {
        // check if 2 plane normals are same direction
        QVector3D cross = QVector3D::crossProduct(m_normal, plane.getNormal());
        if (cross.x() == 0 && cross.y() == 0 && cross.z() == 0)
            return false;
        else
            return true;
    };


private:
    QVector3D m_normal;     // normal vector of a plane
    float m_d;            // coefficient of constant term: d = -(a*x0 + b*y0 + c*z0)
    float m_normalLength; // length of normal vector
    float m_distance;     // distance from origin to plane
};
/**
 * ================================================.
 * @}.
 */
