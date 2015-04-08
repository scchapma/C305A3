#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QWidget>
#include "shape.h"
#include "ray.h"
#include "color.h"

class Triangle : public Shape
{
public:
    Triangle(const QVector3D& _p0, const QVector3D& _p1, const QVector3D& _p2, const QVector3D& _color);
    bool hit(const Ray &r, float tmin, float tmax, HitRecord &record) const;
    bool shadowHit(const Ray &r, float tmin, float tmax, float time) const;

    QVector3D p0;
    QVector3D p1;
    QVector3D p2;
    QVector3D color;

    ~Triangle();
};

#endif // TRIANGLE_H




