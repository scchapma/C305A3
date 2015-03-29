//-------------------------------------------------------------------------------------------
//   Painting with Flowsnakes
// fsnake program modified to use open gl vertex arrays  Brian Wyvill October 2012
// added save/restore and postscript driver November 2012
// fixed memory management November 2012 delete works properly now.
// added progress bar to show memory usage.
//-------------------------------------------------------------------------------------------
#include <QVector3D>
#include <math.h>

#include "glwidget.h"
#include "common.h"
#include "raytracer.h"
#include "scene.h"
#include "surface.h"

#include <vector>
#include <iostream>
#include "rgb.h"
//#include "Image.h"
#include "shape.h"
#include "sphere.h"
#include "ray.h"

Raytracer::Engine* tracer = 0;

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{

}

GLWidget::~GLWidget()
{    

}

void GLWidget::clear()
{
     updateGL();
}

void GLWidget::initializeGL()
{
    //Background color will be white
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glShadeModel( GL_FLAT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glPointSize(5);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    displayImage();
}

/* 2D */
void GLWidget::resizeGL( int w, int h )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0,GLdouble(w),0,GLdouble(h),-10.0,10.0);
    glFlush();
    glMatrixMode(GL_MODELVIEW);
    glViewport( 0, 0, (GLint)w, (GLint)h );
    //glViewport( 0, 0, (GLint)(w/2), (GLint)(h/2) );
    cerr << "gl new size "<< w SEP h NL;
    renderWidth = w;
    renderHeight = h;
}

// no mouse events in this demo
void GLWidget::mousePressEvent( QMouseEvent * )
{
}

void GLWidget::mouseReleaseEvent( QMouseEvent *)
{
}

void GLWidget::mouseMoveEvent ( QMouseEvent * )
{
}

// wheel event
void GLWidget::wheelEvent(QWheelEvent *)
{
}

void GLWidget::openImage(QString fileBuf)
{     
    QImage myImage;
    myImage.load(fileBuf);
    prepareImageDisplay(&myImage);
}

void GLWidget::prepareImageDisplay(QImage* myimage)
{   
    glimage = QGLWidget::convertToGLFormat( *myimage );  // flipped 32bit RGBA stored as mi
    updateGL();    
}

void GLWidget::displayImage()
{
    if (glimage.width()==0) {
        cerr << "Null Image\n";
        return;
    } else {
        glRasterPos2i(0,0);
        glDrawPixels(glimage.width(), glimage.height(), GL_RGBA, GL_UNSIGNED_BYTE, glimage.bits());
        glFlush();
    }
}

void GLWidget::saveImage( QString fileBuf )
{
    // there is no conversion  back toQImage
    // hence the need to keep qtimage as well as glimage
    qtimage.save ( fileBuf );   // note it is the qtimage in the right format for saving
}

void GLWidget::makeImage( )
{   
    HitRecord rec;
    bool is_a_hit;
    float tmax;
    QVector3D dir (0, 0, -1);

    //geometry
    vector<Shape*> shapes;
    shapes.push_back(new Sphere (QVector3D(250, 250, -1000), 150, QVector3D(139, 0, 139)));
    shapes.push_back(new Sphere (QVector3D(100, 100, -1000), 50, QVector3D(255, 215, 0)));

    //hard code light position - QVector3d
    QVector3D lightPosition (-100, -150, 300);
    float diffuseFactor;
    float diffuseCoefficient, specularCoefficient;
    float intensityFactor = 1.5;
    QVector3D incidentLightRay;
    QVector3D surfaceNormal;

    QImage myimage(renderWidth, renderHeight, QImage::Format_RGB32);
    //cerr << "renderWidth and renderHeight: "<< renderWidth SEP renderHeight NL;

    for (int i = 0; i < renderWidth; i++)
        for (int j = 0; j < renderHeight; j++)
        {
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
            if (is_a_hit)
            {
                //add diffuse component
                incidentLightRay = (rec.intersectionPoint - lightPosition).normalized();
                surfaceNormal = rec.normal;
                diffuseFactor = surfaceNormal.dotProduct(incidentLightRay, surfaceNormal);
                diffuseFactor *= (-1);
                rec.color *= diffuseFactor;
                if(rec.color.x() < 0) rec.color.setX(0);
                if(rec.color.y() < 0) rec.color.setY(0);
                if(rec.color.z() < 0) rec.color.setZ(0);
                if(rec.color.x() > 255) rec.color.setX(255);
                if(rec.color.y() > 255) rec.color.setY(255);
                if(rec.color.z() > 255) rec.color.setZ(255);
                //myimage.setPixel(i, j, qRgb(rec.color.x(), rec.color.y(), rec.color.z()));

                //add specular component
                float myDot = - incidentLightRay.dotProduct(incidentLightRay, surfaceNormal);
                float myLen = 2.0f * myDot;

                QVector3D tempNormal = myLen * surfaceNormal;
                QVector3D reflectVector = (tempNormal + incidentLightRay).normalized();

                float mySpec = 0.0;
                float tempDot = - reflectVector.dotProduct(reflectVector, incidentLightRay);
                if (tempDot > 0.0) mySpec = tempDot;

                mySpec = powf(mySpec, 20);

                QVector3D specularColor (255, 255, 255);
                specularColor *= mySpec;
                rec.color += specularColor;
                if(rec.color.x() < 0) rec.color.setX(0);
                if(rec.color.y() < 0) rec.color.setY(0);
                if(rec.color.z() < 0) rec.color.setZ(0);
                if(rec.color.x() > 255) rec.color.setX(255);
                if(rec.color.y() > 255) rec.color.setY(255);
                if(rec.color.z() > 255) rec.color.setZ(255);
                myimage.setPixel(i, j, qRgb(rec.color.x(), rec.color.y(), rec.color.z()));

            }
            else
                myimage.setPixel(i, j, qRgb(60,60,60));
        }

    //tracer = new Raytracer::Engine();
    //tracer->GetScene()->InitScene();

    //render scene here
    //call ray trace elsewhere (traverse objects)
    //tracer->Render(&myimage);

    qtimage=myimage.copy(0, 0,  myimage.width(), myimage.height());
    prepareImageDisplay(&myimage);
}

void GLWidget::about()
{
    QString vnum;
    QString mess, notes;
    QString title="Images in Qt and Opengl ";

    vnum.setNum ( MYVERSION );
    mess="Qt OpenGl image demo Release Version: ";
    mess = mess+vnum;
    notes = "\n\n News: Every QImage is now on stack, there is no way for memory leak. -- Lucky";
    mess = mess+notes;
    QMessageBox::information( this, title, mess, QMessageBox::Ok );
}

void GLWidget::help()
{
    QString vnum;
    QString mess, notes;
    QString title="qtglimages";

    vnum.setNum ( MYVERSION);
    mess="Simple Image Handling in Qt/Opengl by Brian Wyvill Release Version: ";
    mess = mess+vnum;
    notes = "\n\n Save and Load images for display.  Also Make an image such as output from a ray tracer. ";
    mess = mess+notes;
    QMessageBox::information( this, title, mess, QMessageBox::Ok );
}

