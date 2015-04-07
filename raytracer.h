#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QWidget>
#include <glwidget.h>

class RayTracer
{
public:
    RayTracer();
    void rayTrace();
    void initRender();
    void render(QImage &myimage);
    ~RayTracer();
};

#endif

