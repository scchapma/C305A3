#ifndef SHAPE_H
#define SHAPE_H

#include <QWidget>
#include <ray.h>
//#include <rgb.h>

class Ray;
class rgb;

struct HitRecord
{
    float t;
    QVector3D normal;
    QVector3D intersectionPoint;
    QVector3D color;

public:
    void clamp();
};

class Shape
{
public:
    Shape();
    ~Shape();
    virtual bool hit(const Ray& r, float tmin, float tmax, HitRecord& record) const = 0;
    virtual bool shadowHit(const Ray& r, float tmin, float tmax, float time) const = 0;    
};


#endif // SHAPE_H
