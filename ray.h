#ifndef RAY_H
#define RAY_H

#include <QWidget>
#include <glwidget.h>

class Ray
{
public:
    Ray();
    Ray(const QVector3D& a, const QVector3D& b)
    {data[0] = a; data[1] = b;}
    Ray(const Ray& r) {*this = r;}
    QVector3D origin() const {return data[0];}
    QVector3D direction() const{return data[1];}
    QVector3D pointAtParameter (float t) const
    {return data[0] + t*data[1];}

    QVector3D data[2];
    ~Ray();
};

/*
inline ostream &operator<<(ostream &os, const Ray &r){
    os << "(" << r.origin() << ") + t(" << r.direction() << ")";
    return os;
}
*/

#endif // RAY_H
