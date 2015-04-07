#include "raytracer.h"

#include <vector>
//#include "color.h"
#include "shape.h"
#include "sphere.h"
//#include "ray.h"

RayTracer::RayTracer()
{

}

bool RayTracer::rayTrace(HitRecord &rec, int i, int j, vector<Shape*> shapes)
{
    bool is_a_hit;
    float tmax;
    QVector3D dir (0, 0, -1);

    tmax = 100000.0f;
    is_a_hit = false;
    Ray r(QVector3D(i, j, 0), dir);

    //loop over list of Shapes
    for (int k = 0; k < (int)shapes.size(); k++)
        if (shapes[k]->hit(r, .00001f, tmax, rec))
        {
            tmax = rec.t;
            is_a_hit = true;
        }
    return is_a_hit;
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
    shapes.push_back(new Sphere (QVector3D(675, 450, -1000), 300, QVector3D(139, 0, 139)));
    //shapes.push_back(new Sphere (QVector3D(675, 450, -1000), 300, QVector3D(255, 0, 0)));
    shapes.push_back(new Sphere (QVector3D(100, 100, -1000), 50, QVector3D(255, 215, 0)));
    //shapes.push_back(new Sphere (QVector3D(100, 100, -1000), 50, QVector3D(0, 0, 255)));

    QVector3D lightPosition (-100, -150, 300);
    //QVector3D lightPosition (0, -150, 300);
    //QVector3D lightPosition (0, 0, 300);

    float diffuseFactor;
    float diffuseCoefficient = 0.9;
    float specularCoefficient = 0.9;
    int specPower = 50;

    for (int i = 0; i < renderWidth; i++)
        for (int j = 0; j < renderHeight; j++)
        {
            if (rayTrace(rec, i, j, shapes))
            {
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
                myimage.setPixel(i, j, qRgb(60,60,60));
        }
}

RayTracer::~RayTracer()
{

}



