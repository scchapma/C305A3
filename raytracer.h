#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QWidget>
#include <glwidget.h>
#include "shape.h"

class RayTracer
{
public:
    RayTracer();
    bool rayTrace(HitRecord &rec, int i, int j);
    void initRender();
    void render(QImage &myimage, int width, int height);
    ~RayTracer();
};

#endif

