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
        corner = center + u0*U + v0*V - d*W;
        across = (u1-u0)*U;
        up = (v0-v1)*V;
    }

    Ray getRay(float a, float b)
    {
        cout << "a: " << a << "b: " << b << endl;
        QVector3D origin = center;
        QVector3D target = corner + across*a + up*b;
        cout << "corner.x: " << corner.x() << endl;
        cout << "corner.y: " << corner.y() << endl;
        cout << "corner.z: " << corner.z() << endl;
        return Ray(origin, (target - origin).normalized());
    }

    ~Camera();

    QVector3D center, corner, across, up;
    QVector3D U, V, W;
    float u0, u1, v0, v1;
    float d;
};

#endif // CAMERA_H

