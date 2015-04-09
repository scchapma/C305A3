#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include "ray.h"
#include "color.h"

class Camera
{
public:
    Camera();
    Camera(const Camera& orig)
    {
        center = orig.center;
        corner = orig.corner;
        across = orig.across;
        up = orig.up;

        W = orig.W;
        U = orig.U;
        V = orig.V;

        u0 = orig.u0;
        u1 = orig.u1;
        v0 = orig.v0;
        v1 = orig.v1;
        d = orig.d;
    }

    Camera(QVector3D c, QVector3D gaze, QVector3D vup, float left, float right, float bottom, float top, float distance)
        :center(c), u0(left), u1(right), v0(bottom), v1(top), d(distance)
    {
        W = -gaze.normalized();
        U = gaze.crossProduct(vup, -gaze).normalized();
        V = W.crossProduct(W, U);
        //cout << "center.x: " << center.x() << endl;
        //cout << "center.y: " << center.y() << endl;
        //cout << "center.z: " << center.z() << endl;
        //corner = center + u0*U + v0*V - d*W;
        corner = center - 672*U - 468*V - d*W;
        across = (u1-u0)*U;
        //cout << "across.x: " << across.x() << endl;
        //cout << "across.y: " << across.y() << endl;
        //cout << "across.z: " << across.z() << endl;
        up = (v0-v1)*V;
        //cout << "up.x: " << up.x() << endl;
        //cout << "up.y: " << up.y() << endl;
        //cout << "up.z: " << up.z() << endl;
    }

    Ray getRay(float a, float b, float height)
    {
        //cout << "a: " << a << "b: " << b << endl;
        QVector3D origin = center;
        //QVector3D target = corner + across*a + up*(height - b);
        QVector3D target = corner + U*a + V*b;
        //cout << "target.x: " << target.x() << endl;
        //cout << "target.y: " << target.y() << endl;
        //cout << "target.z: " << target.z() << endl;
        return Ray(origin, (target - origin).normalized());
    }

    ~Camera();

    QVector3D center, corner, across, up;
    QVector3D U, V, W;
    float u0, u1, v0, v1;
    float d;
};

#endif // CAMERA_H

