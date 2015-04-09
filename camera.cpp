#include "camera.h"


Camera::Camera()
{

}

Camera::~Camera()
{

}


/*
GLdouble * GLWidget::constructMatrix(GLdouble matrix[])
{
    //Init and normaliz F vector
    Vector3d F;
    F.x = (0 - CameraPos.x);
    F.y = (0 - CameraPos.y);
    F.z = (0 - CameraPos.z);
    F = normalize(F);

    //Init and normalize Up vector
    Vector3d Up;
    Up.x = 0.0;
    Up.y = 1.0;
    Up.z = 0.0;
    Up = normalize(Up);

    //s = F x Up
    Vector3d S;
    S = cross(F, Up);

    //Normalize s
    S = normalize(S);

    //u = s X f
    Vector3d U;
    U = cross(S, F);

    //construct M from S, U, and F
    matrix[0] = S.x;
    matrix[1] = U.x;
    matrix[2] = (-1)*F.x;
    matrix[3] = 0;
    matrix[4] = S.y;
    matrix[5] = U.y;
    matrix[6] = (-1)*F.y;
    matrix[7] = 0;
    matrix[8] = S.z;
    matrix[9] = U.z;
    matrix[10] = (-1)*F.z;
    matrix[11] = 0;
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;

    return matrix;
}

Vector3d GLWidget::normalize (Vector3d input){
    double length = sqrt(input.x*input.x + input.y*input.y + input.z*input.z);
    input.x /= length;
    input.y /= length;
    input.z /= length;
    return input;
}

Vector3d GLWidget::cross (Vector3d input1, Vector3d input2){
    Vector3d result;
    result.x = (input1.y*input2.z - input1.z*input2.y);
    result.y = (input1.z*input2.x - input1.x*input2.z);
    result.z = (input1.x*input2.y - input1.y*input2.x);
    return result;
}
*/
