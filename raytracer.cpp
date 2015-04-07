#include "raytracer.h"

#include <vector>
#include "shape.h"
#include "sphere.h"
#include <stdlib.h>

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

    /*
    Ray r(QVector3D(i, j, 0), dir);

    //loop over list of Shapes
    for (int k = 0; k < (int)shapes.size(); k++)
        if (shapes[k]->hit(r, .00001f, tmax, rec))
        {
            tmax = rec.t;
            is_a_hit = true;
        }
    */

    float t = 0;
    QVector3D normal (0, 0, 0);
    QVector3D intersectionPoint (0, 0, 0);
    QVector3D color (0, 0, 0);

    //add sampling
    QVector2D samples[9];
    int a, b, c;

    for(a = 0; a < 3; a++){
        for(b = 0; b < 3; b++)
        {
            float x = ((double)a + drand48()) / 3;
            float y = ((double)b + drand48()) / 3;
            (samples[a*3 + b]).setX(x);
            (samples[a*3 + b]).setY(y);
            //cout << "x: " << (samples[a*3 + b]).x() << endl;
            //cout << "y: " << (samples[a*3 + b]).y() << endl;
        }
    }

    for(c = 0; c < 9; c++){
        tmax = 100000.0f;
        //is_a_hit = false;
        //Ray r(QVector3D(i + samples[c].x(), j + samples[c].y(), 0), dir);
        QVector3D origin(i + samples[c].x() - 0.5, j + samples[c].y() - 0.5, 0);
        Ray r(origin, dir);
        for (int k = 0; k < (int)shapes.size(); k++)
        {
            if (shapes[k]->hit(r, .00001f, tmax, rec))
            {
                tmax = rec.t;
                is_a_hit = true;
            }
        }
        t += rec.t;
        normal += rec.normal;
        intersectionPoint += rec.intersectionPoint;
        color += rec.color;
        //cout << "t: " << t << endl;
        //cout << "normal: " <<  normal.x() << normal.y() << normal.z() << endl;
        //cout << "intersectionPoint: " << intersectionPoint.x() << intersectionPoint.y() << intersectionPoint.z() << endl;
        //cout << "color: " << color.x() << color.y() << color.z() << endl;
    }

    rec.t = t/9;
    rec.normal = normal/9;
    rec.intersectionPoint = intersectionPoint/9;
    rec.color = color/9;

    rec.normal = rec.normal.normalized();
    //cout << "final t: " << rec.t << endl;
    //cout << "final normal: " <<  rec.normal.x() << rec.normal.y() << rec.normal.z() << endl;
    //cout << "final intersectionPoint: " << rec.intersectionPoint.x() << rec.intersectionPoint.y() << rec.intersectionPoint.z() << endl;
    //cout << "final color: " << rec.color.x() << rec.color.y() << rec.color.z() << endl;

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
    shapes.push_back(new Sphere (QVector3D(600, 600, -500), 500, QVector3D(139, 0, 139)));
    //shapes.push_back(new Sphere (QVector3D(675, 450, -1000), 300, QVector3D(255, 0, 0)));
    shapes.push_back(new Sphere (QVector3D(150, 150, -1100), 100, QVector3D(255, 215, 0)));
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
    //for (int i = 675; i < 676; i++)
    //    for (int j = 450; j < 451; j++)
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
                myimage.setPixel(i, j, qRgb(160,160,160));
        }
}

RayTracer::~RayTracer()
{

}



