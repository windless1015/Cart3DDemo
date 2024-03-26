#pragma once

#include <QVector3D>
#include <QQuaternion>
#include <QMouseEvent>
#include <QSize>
#include <QtMath>

class Arcball {
public:
    //Arcball(float width, float height) : screenWidth(width), screenHeight(height) {}
    Arcball(){}

    void onMousePressed(const QMouseEvent* event, float screenWidth, float screenHeight) {
        start = mapToSphere(event->pos(), screenWidth, screenHeight);
    }

    void onMouseMoved(const QMouseEvent* event, float screenWidth, float screenHeight) {
        end = mapToSphere(event->pos(), screenWidth, screenHeight);
        rotation = QQuaternion::rotationTo(start, end);
    }

    QQuaternion getRotation() {
        return rotation.normalized();
    }

private:
    QVector3D mapToSphere(const QPoint& point, float screenWidth, float screenHeight) {
        qDebug() << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        qDebug()<< point.x()<<"," << point.y() << ","<< screenWidth << "," << screenHeight;
        /*float x = point.x() - screenWidth / 2;
        float y = -(point.y() - screenHeight / 2);*/
        float x = (point.x() - screenWidth / 2)/ screenWidth / 2;
        float y = -(point.y() - screenHeight / 2)/ screenHeight / 2;
        float z;

        qDebug() << "static:[" << (point.x() - screenWidth / 2)/ screenWidth / 2
            << "," << -(point.y() - screenHeight / 2)/ screenHeight / 2 << "]";
        qDebug() << "middle:["  << x << "," << y  << "]";
        float length = x * x + y * y;
        if (length > 1.0f) {
            float norm = 1.0f / qSqrt(length);
            x *= norm;
            y *= norm;
            z = 0.0f;
        }
        else {
            z = qSqrt(1.0f - length);
        }
        
        qDebug() << "length:[" << length << "],mapToSphere:[" << x << "," << y << "," << z << "]";
        qDebug() << "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
        return QVector3D(x, y, z);
    }

    QVector3D start, end;
    QQuaternion rotation;
    //float screenWidth, screenHeight;
};

/*
*

void FoxOpenGLWidget::translate_point(QPoint& p_ab)
{
    // this->width() 表示视口的宽度，由于视口宽高一样，
    // 所以点(this->width(), this->height() )就是视口的中心点，即旋转中心。
    int x = p_ab.x() - this->width() / 2;
    int y = -(p_ab.y() - this->height() / 2);

    p_ab.setX(x);
    p_ab.setY(y);
}
* 
float xp = (2.0f * x - width) / width;
    float yp = (height - 2.0f * y) / height;
    float zp = 0.0f;

    float distance = xp * xp + yp * yp;
    if (distance > 1.0f) {
        float norm = 1.0f / sqrt(distance);
        xp *= norm;
        yp *= norm;
    }
    else {
        zp = sqrt(1.0f - distance);
    }

    return QVector3D(xp, yp, zp);
*/