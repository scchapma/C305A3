#include "shape.h"

void HitRecord::clamp()
{
    if(this->color.x() < 0) this->color.setX(0);
    if(this->color.y() < 0) this->color.setY(0);
    if(this->color.z() < 0) this->color.setZ(0);
    if(this->color.x() > 255) this->color.setX(255);
    if(this->color.y() > 255) this->color.setY(255);
    if(this->color.z() > 255) this->color.setZ(255);
}

Shape::Shape()
{

}

Shape::~Shape()
{

}

