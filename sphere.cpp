#include "sphere.h"
#include <math.h>
#include <QWidget>
#include <QVector3D>
#include <stdlib.h>

Sphere::Sphere(const QVector3D &_center, float _radius, const QVector3D &_color)
    :center(_center), radius(_radius), color(_color) {}

bool Sphere::hit(const Ray &r, float tmin, float tmax, HitRecord &record) const
{
    QVector3D temp = r.origin() - center;

    //TODO:  This is stupid - must be better way to call static function than using "temp" here
    double a = temp.dotProduct( r.direction(), r.direction());
    double b = 2*temp.dotProduct(r.direction(), temp);
    double c = temp.dotProduct(temp, temp) - radius*radius;

    double discriminant = b*b - 4*a*c;

    //first check to see if ray intersects sphere
    if (discriminant >0)
    {
        discriminant = sqrt(discriminant);
        double t = ((-1)*b - discriminant)/(2*a);

        //now check for valid interval
        if (t < tmin)
            t = ((-1)*b + discriminant)/(2*a);
        if (t < tmin || t > tmax)
            return false;

        // we have a valid hit
        record.t = t;
        QVector3D intersectionPoint = r.origin() + t*r.direction();
        record.intersectionPoint = intersectionPoint.normalized();
        QVector3D normal = r.origin() + t*r.direction() - center;
        record.normal = normal.normalized();
        record.color = color;
        //cout << "t: " << record.t << endl;
        //cout << "normal: " <<  record.normal.x() << record.normal.y() << record.normal.z() << endl;
        //cout << "intersectionPoint: " << record.intersectionPoint.x() << record.intersectionPoint.y() << record.intersectionPoint.z() << endl;
        //cout << "color: " << record.color.x() << record.color.y() << record.color.z() << endl;
        return true;
    }
    return false;
}

//TODO:  Implement this
bool Sphere::shadowHit(const Ray &r, float tmin, float tmax, float time) const
{
    return false;
}

Sphere::~Sphere()
{

}

