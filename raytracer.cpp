#include "raytracer.h"

#include <vector>
#include "shape.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"
#include <stdlib.h>

const unsigned short int sampleSize = 1;

const QVector3D c (0, 0, 0);
const QVector3D gaze (0, 0, 0);
const QVector3D vup (0, 1, 0);

RayTracer::RayTracer()
{

}

Camera RayTracer::initCamera()
{
    //QVector3D origin (672, 468, 500);
    QVector3D c (500, 468, 200);
    QVector3D gaze (0, 0, -1);
    QVector3D vup (0, 1, 0);
    const float left = 0.0;
    const float right = 1344.0;
    const float bottom = 936.0;
    const float top = 0.0;
    const float distance = 500.0;
    Camera camera = Camera(c, gaze, vup, left, right, bottom, top, distance);
    return camera;
}

bool RayTracer::rayTrace(HitRecord &rec, int i, int j, vector<Shape*> shapes)
{
    Camera camera = initCamera();
    //cout << "corner.x: " << camera.corner.x() << endl;
    //cout << "corner.y: " << camera.corner.y() << endl;
    //cout << "corner.z: " << camera.corner.z() << endl;

    bool is_a_hit;
    bool sample_hit;
    float tmax;
    //QVector3D dir (0, 0, -1);

    tmax = 100000.0f;
    is_a_hit = false;

    //initialize sampling values
    float t = 0;
    QVector3D normal (0, 0, 0);
    QVector3D intersectionPoint (0, 0, 0);
    QVector3D color (0, 0, 0);

    QVector3D origin (672, 468, 500);
    //QVector3D origin (0, 0, 1);

    //add sampling
    QVector2D samples[sampleSize*sampleSize];

    jitter(samples, sampleSize);

    for(int c = 0; c < sampleSize*sampleSize; c++){
        sample_hit = false;
        tmax = 100000.0f;
        //QVector3D origin(i + samples[c].x() - 0.5, j + samples[c].y() - 0.5, 0);
        //QVector3D dir(QVector3D(i, j, 0) - origin);
        //dir.normalized();
        //cout << "samples[c].x: " << i + samples[c].x() - 0.5 << endl;
        //cout << "samples[c].y: " << j + samples[c].y() - 0.5 << endl;
        //Ray r(origin, dir);
        Ray r = camera.getRay(i + samples[c].x() - 0.5, j + samples[c].y() - 0.5, 0);
        //Ray r = camera.getRay(i, j, 0);

        for (int k = 0; k < (int)shapes.size(); k++)
        {
            if (shapes[k]->hit(r, .00001f, tmax, rec))
            {
                tmax = rec.t;
                is_a_hit = true;
                sample_hit = true;
            }
        }
        t += rec.t;
        normal += rec.normal;
        intersectionPoint += rec.intersectionPoint;
        if(sample_hit) color += rec.color;
        else color += QVector3D(160,160,160);
    }

    rec.t = t/(sampleSize*sampleSize);
    rec.normal = normal/(sampleSize*sampleSize);
    rec.intersectionPoint = intersectionPoint/(sampleSize*sampleSize);
    rec.color = color/(sampleSize*sampleSize);
    rec.clamp();
    rec.normal = rec.normal.normalized();

    return is_a_hit;
}

void RayTracer::jitter(QVector2D* samples, int sampleSize)
{
    for(int a = 0; a < sampleSize; a++){
        for(int b = 0; b < sampleSize; b++)
        {
            float x = ((double)a + drand48()) / sampleSize;
            float y = ((double)b + drand48()) / sampleSize;
            (samples[a*sampleSize + b]).setX(x);
            (samples[a*sampleSize + b]).setY(y);
        }
    }

}

void RayTracer::initRender()
{

}

void RayTracer::render(QImage &myimage, int renderWidth, int renderHeight)
{
    HitRecord rec;
    QVector3D incidentLightRay;
    QVector3D surfaceNormal;

    //geometry
    vector<Shape*> shapes;

    //shapes.push_back(new Sphere (QVector3D(675, 450, -1000), 300, QVector3D(255, 0, 0)));
    shapes.push_back(new Sphere (QVector3D(450, 450, -200), 100, QVector3D(255, 215, 0)));
    //shapes.push_back(new Sphere (QVector3D(100, 100, -1000), 50, QVector3D(0, 0, 255)));
    //shapes.push_back(new Sphere (QVector3D(600, 600, -500), 500, QVector3D(139, 0, 139)));
    shapes.push_back(new Triangle (QVector3D(250, 650, -300), QVector3D(250, 250, -300), QVector3D(650, 250, -300), QVector3D(255, 0, 0)));
    shapes.push_back(new Triangle (QVector3D(650, 250, -300), QVector3D(650, 650, -300), QVector3D(250, 650, -300), QVector3D(255, 0, 0)));
    shapes.push_back(new Triangle (QVector3D(250, 650, -300), QVector3D(650, 650, -300), QVector3D(250, 650, -50), QVector3D(0, 0, 255)));
    shapes.push_back(new Triangle (QVector3D(650, 650, -300), QVector3D(650, 650, -50), QVector3D(250, 650, -50), QVector3D(0, 0, 255)));
    shapes.push_back(new Triangle (QVector3D(250, 250, -50), QVector3D(250, 250, -300), QVector3D(250, 650, -50), QVector3D(0, 255, 0)));
    shapes.push_back(new Triangle (QVector3D(250, 250, -300), QVector3D(250, 650, -300), QVector3D(250, 650, -50), QVector3D(0, 255, 0)));

    QVector3D lightPosition (100, -150, 300);
    //QVector3D lightPosition (0, -150, 300);
    //QVector3D lightPosition (0, 0, 300);

    float diffuseFactor;
    float ambientCoefficient = 0.9;
    float diffuseCoefficient = 0.9;
    float specularCoefficient = 0.9;
    int specPower = 50;

    for (int i = 0; i < renderWidth; i++)
        for (int j = 0; j < renderHeight; j++)
        {
            if (rayTrace(rec, i, j, shapes))
            {
                //add ambient component


                //add diffuse component
                incidentLightRay = (rec.intersectionPoint - lightPosition).normalized();
                surfaceNormal = rec.normal;
                diffuseFactor = surfaceNormal.dotProduct(incidentLightRay, surfaceNormal);
                diffuseFactor *= (-1);                
                rec.color = (diffuseFactor*diffuseCoefficient)*rec.color;

                //clamp
                rec.clamp();                

                //add specular component
                float myDot = - incidentLightRay.dotProduct(incidentLightRay, surfaceNormal);
                float myLen = 2.0f * myDot;

                QVector3D tempNormal = myLen * surfaceNormal;
                QVector3D reflectVector = (tempNormal + incidentLightRay).normalized();

                float mySpec = 0.0;
                float tempDot = - reflectVector.dotProduct(reflectVector, incidentLightRay);
                if (tempDot > 0.0) mySpec = tempDot;

                mySpec = powf(mySpec, specPower);

                QVector3D specularColor (255, 255, 255);
                specularColor = (mySpec*specularCoefficient) * specularColor;

                //add diffuse and specular components
                rec.color += specularColor;

                //clamp
                rec.clamp();

                myimage.setPixel(i, j, qRgb(rec.color.x(), rec.color.y(), rec.color.z()));
            }
            else                
                myimage.setPixel(i, j, qRgb(160,160,160));
        }
}

RayTracer::~RayTracer()
{

}



