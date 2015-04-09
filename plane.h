#ifndef PLANE_H
#define PLANE_H

#include <QWidget>
#include "shape.h"
#include "ray.h"

class Plane : public Shape
{
public:
    Plane(const QVector3D& _normal, float _d, const QVector3D& _color);
    //BBox boundingBox() const;
    bool hit(const Ray &r, float tmin, float tmax, HitRecord &record) const;
    bool shadowHit(const Ray &r, float tmin, float tmax, float time) const;

    QVector3D normal;
    float d;
    QVector3D color;

    ~Plane();
};


#endif // PLANE_H
