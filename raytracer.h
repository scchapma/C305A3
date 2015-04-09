#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QWidget>
#include <glwidget.h>
#include <vector>
#include "shape.h"
#include "camera.h"

class RayTracer
{
public:
    RayTracer();
    Camera initCamera();
    bool rayTrace(HitRecord &rec, int i, int j, vector<Shape*> shapes);
    void jitter(QVector2D* samples, int sampleSize);
    void initRender();
    void render(QImage &myimage, int width, int height);
    ~RayTracer();
};

#endif

