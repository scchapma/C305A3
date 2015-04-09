#include "plane.h"
#include <math.h>
#include <QWidget>
#include <QVector3D>
#include <stdlib.h>

Plane::Plane(const QVector3D &_normal, float _d, const QVector3D &_color)
    :normal(_normal), d(_d), color(_color) {}

bool Plane::hit(const Ray &r, float tmin, float tmax, HitRecord &record) const
{
    float n = this->normal.dotProduct(this->normal, r.direction());
    if (n != 0)
    {
        float t = -(this->normal.dotProduct(this->normal, r.origin()) + this->d)/n;
        if (t > tmin)
        {
            if (t < tmax)
            {
                tmax = t;
                record.t = t;
                QVector3D intersectionPoint = r.origin() + t*r.direction();
                record.intersectionPoint = intersectionPoint.normalized();
                //QVector3D normal = r.origin() + t*r.direction() - center;
                //record.normal = normal.normalized();
                record.normal = this->normal;
                record.color = color;
                return true;
            }
        }
    }
    return false;
}

//TODO:  Implement this
bool Plane::shadowHit(const Ray &r, float tmin, float tmax, float time) const
{
    return false;
}

Plane::~Plane()
{

}





