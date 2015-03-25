#ifndef SPHERE_H
#define SPHERE_H

#include <QWidget>
#include "shape.h"
#include "ray.h"
#include "rgb.h"

class Sphere : public Shape
{
public:
    Sphere(const QVector3D& _center, float _radius, const rgb& _color);
    //BBox boundingBox() const;
    bool hit(const Ray &r, float tmin, float tmax, float time, HitRecord &record) const;
    bool shadowHit(const Ray &r, float tmin, float tmax, float time) const;

    QVector3D center;
    float radius;
    rgb color;

    ~Sphere();


};

#endif // SPHERE_H
