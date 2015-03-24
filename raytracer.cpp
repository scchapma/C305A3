// -----------------------------------------------------------
// raytracer.cpp
// 2004 - Jacco Bikker - jacco@bik5.com - www.bik5.com -   <><
// -----------------------------------------------------------

#include "raytracer.h"
#include "scene.h"
#include "common.h"
#include "iostream"

namespace Raytracer {

Ray::Ray( vector3& a_Origin, vector3& a_Dir ) :
    m_Origin( a_Origin ),
    m_Direction( a_Dir )
{
}

Engine::Engine()
{
    m_Scene = new Scene();
}

Engine::~Engine()
{
    delete m_Scene;
}

// -----------------------------------------------------------
// Engine::SetTarget
// Sets the render target canvas
// -----------------------------------------------------------
void Engine::SetTarget( Pixel* a_Dest, int a_Width, int a_Height )
{
    // set pixel buffer address & size
    m_Dest = a_Dest;
    m_Width = a_Width;
    m_Height = a_Height;
}

// -----------------------------------------------------------
// Engine::Raytrace
// Naive ray tracing: Intersects the ray with every primitive
// in the scene to determine the closest intersection
// -----------------------------------------------------------

//Primitive* Engine::Raytrace( Ray& a_Ray, Color& a_Acc, int a_Depth, float a_RIndex, float& a_Dist )
Primitive* Engine::Raytrace( Ray& a_Ray, float& a_Dist, bool& intersect_flag )
{
    // trace primary ray
    a_Dist = 1000000.0f;
    vector3 pi;
    Primitive* prim = 0;
    int result = 0;
    intersect_flag = false;

    /*
    // find the nearest intersection
    for ( int s = 0; s < m_Scene->GetNrPrimitives(); s++ )
    {
        //cout << "Value of s is : " << s << endl;
        Primitive* pr = m_Scene->GetPrimitive( s );
        int res;
        res = pr->Intersect( a_Ray, a_Dist );
        //cout << "res: " << res << endl;
        //if (res = pr->Intersect( a_Ray, a_Dist ))
        if (res == 1)
        {
            prim = pr;
            result = res; // 0 = miss, 1 = hit, -1 = hit from inside primitive
        }
    }
    */

    //TODO: Hard-coded for one object - uncover for loop for multiple objects
    Primitive* pr = m_Scene->GetPrimitive(0);
    int res;
    res = pr->Intersect( a_Ray, a_Dist );
    if (res == 1)
    {
        prim = pr;
        result = res; // 0 = miss, 1 = hit, -1 = hit from inside primitive
    }

    // no hit, terminate ray
    if (!prim) return 0;

    // handle intersection
    if(result == 1)
    {
        intersect_flag = true;
    }else
    {
        intersect_flag = false;
    }

    /*
    if (prim->IsLight())
    {
        // we hit a light, stop tracing
        a_Acc = Color( 1, 1, 1 );
    }
    else
    {
        // determine color at point of intersection
        pi = a_Ray.GetOrigin() + a_Ray.GetDirection() * a_Dist;
        // trace lights
        for ( int l = 0; l < m_Scene->GetNrPrimitives(); l++ )
        {
            Primitive* p = m_Scene->GetPrimitive( l );
            if (p->IsLight())
            {
                Primitive* light = p;
                // calculate diffuse shading
                vector3 L = ((Sphere*)light)->GetCentre() - pi;
                NORMALIZE( L );
                vector3 N = prim->GetNormal( pi );
                if (prim->GetMaterial()->GetDiffuse() > 0)
                {
                    float dot = DOT( N, L );
                    if (dot > 0)
                    {
                        float diff = dot * prim->GetMaterial()->GetDiffuse();
                        // add diffuse component to ray color
                        //a_Acc += diff * prim->GetMaterial()->GetColor() * light->GetMaterial()->GetColor();
                    }
                }
            }
        }
    }
    */

    // return pointer to primitive hit by primary ray
    return prim;
}


// -----------------------------------------------------------
// Engine::InitRender
// Initializes the renderer, by resetting the line / tile
// counters and precalculating some values
// -----------------------------------------------------------
void Engine::InitRender()
{
    // set first line to draw to
    m_CurrLine = 20;
    // set pixel buffer address of first pixel
    m_PPos = 20 * m_Width;
    // screen plane in world space coordinates
    m_WX1 = -4, m_WX2 = 4, m_WY1 = m_SY = 3, m_WY2 = -3;
    // calculate deltas for interpolation
    m_DX = (m_WX2 - m_WX1) / m_Width;
    m_DY = (m_WY2 - m_WY1) / m_Height;
    m_SY += 20 * m_DY;
    // allocate space to store pointers to primitives for previous line
    m_LastRow = new Primitive*[m_Width];
    //memset( m_LastRow, 0, m_Width * 4 );
}

// -----------------------------------------------------------
// Engine::Render
// Fires rays in the scene one scanline at a time, from left
// to right
// -----------------------------------------------------------

/*
bool Engine::Render(QImage* myimage)
{
    int renderWidth = 1344;
    int renderHeight = 936;

    //int renderWidth = (*myimage).width;
    //int renderHeight = (*myimage).height;

    QVector3D CameraPoint(renderWidth/2, renderHeight/2, -1);
    QVector3D CircleCenter(renderWidth/2, renderHeight/2, 10);

    double CircleRadius = 1000;

    for(int j = 0; j < renderHeight; ++j)
        for(int i=0; i < renderWidth; ++ i)
        {
            QVector3D Origin = CameraPoint;
            QVector3D ImagePlanePosition(i, j, 0);
            QVector3D Direction = ImagePlanePosition - Origin;

            QVector3D Z10Position = Origin + 11*Direction;
            QVector3D DistanceToCenter = Z10Position - CircleCenter;
            double length = DistanceToCenter.length();
            if (length < CircleRadius)
            {
                (*myimage).setPixel(i, j, qRgb(255, 255, 255));
            } else
            {
                (*myimage).setPixel(i, j, qRgb(0,0,0));
            }

        }
}
*/


bool Engine::Render(QImage* myimage)
{

    int hitCounter = 0;
    int missCounter = 0;

    int renderWidth = 1344;
    int renderHeight = 936;

    //int renderWidth = (*myimage).width;
    //int renderHeight = (*myimage).height;    

    // render scene
    vector3 o(renderWidth/2, renderHeight/2, -50);
    //vector3 o(3*renderWidth/4, renderHeight/4, -100);
    //vector3 dir(renderWidth/2, renderHeight/2, -1);
    vector3 dir(0, 0, 100);

    // reset last found primitive pointer
    Primitive* lastprim = 0;
    // render remaining lines

    int lowery = 200;
    int uppery = 700;
    int lowerx = 300;
    int upperx = 1000;

    //for ( int y = m_CurrLine; y < (m_Height - 20); y++ )
    //for ( int y = 0; y < renderHeight; y++ )
    for (int y = lowery; y < uppery; y++ )
    {
        //m_SX = m_WX1;
        // render pixels for current line
        //for ( int x = 0; x < renderWidth; x++ )
        for (int x = lowerx; x < upperx; x++)
        {
            cout << "Value of y is : " << y << endl;
            cout << "Value of x is : " << x << endl;

            // fire primary ray
            //Color acc( 0, 0, 0 );
            //vector3 dir = vector3( m_SX, m_SY, 0 ) - o;
            vector3 imagePlanePosition = vector3(x, y, 0);
            //vector3 dir = imagePlanePosition - o;

            NORMALIZE( dir );
            //Ray r( o, dir );
            Ray r( imagePlanePosition, dir );
            float dist;
            bool flag;
            //Primitive* prim = Raytrace( r, acc, 1, 1.0f, dist );
            Primitive* prim = Raytrace( r, dist, flag );
            cout << "flag: " << flag << endl;
            if (flag)
            {
                hitCounter++;
                (*myimage).setPixel(x, y, qRgb(255, 255, 255));
            } else
            {
                missCounter++;
                (*myimage).setPixel(x, y, qRgb(0,0,0));
            }
            cout << "hitCounter: " << hitCounter << endl;
            cout << "missCounter: " << missCounter << endl;

            /*
            int red = (int)(acc.r * 256);
            int green = (int)(acc.g * 256);
            int blue = (int)(acc.b * 256);
            if (red > 255) red = 255;
            if (green > 255) green = 255;
            if (blue > 255) blue = 255;
            m_Dest[m_PPos++] = (red << 16) + (green << 8) + blue;
            */

            //m_SX += m_DX;
        }
        //m_SY += m_DY;
        // see if we've been working to long already    
    }
    // all done
    return true;
}


/*
bool Engine::Render()
{
    // render scene
    vector3 o( 0, 0, -5 );
    // initialize timer
    //int msecs = GetTickCount();
    // reset last found primitive pointer
    Primitive* lastprim = 0;
    // render remaining lines
    for ( int y = m_CurrLine; y < (m_Height - 20); y++ )
    {
        m_SX = m_WX1;
        // render pixels for current line
        for ( int x = 0; x < m_Width; x++ )
        {
            // fire primary ray
            Color acc( 0, 0, 0 );
            vector3 dir = vector3( m_SX, m_SY, 0 ) - o;
            NORMALIZE( dir );
            Ray r( o, dir );
            float dist;
            Primitive* prim = Raytrace( r, acc, 1, 1.0f, dist );
            int red = (int)(acc.r * 256);
            int green = (int)(acc.g * 256);
            int blue = (int)(acc.b * 256);
            if (red > 255) red = 255;
            if (green > 255) green = 255;
            if (blue > 255) blue = 255;
            m_Dest[m_PPos++] = (red << 16) + (green << 8) + blue;
            m_SX += m_DX;
        }
        m_SY += m_DY;
        // see if we've been working to long already
        //if ((GetTickCount() - msecs) > 100)
        //{
            // return control to windows so the screen gets updated
            //m_CurrLine = y + 1;
            //return false;
        //}
    }
    // all done
    return true;
}
*/

}; // namespace Raytracer
