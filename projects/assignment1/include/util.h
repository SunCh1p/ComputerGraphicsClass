#pragma once
#include <GL/glut.h>

//TODO create vector3 class
struct Vector3{
    GLdouble x, y, z;
    Vector3(GLdouble X, GLdouble Y, GLdouble Z) : x(X), y(Y), z(Z){}
    Vector3 operator+(const Vector3& other){
        return Vector3(x+other.x, y+other.y, z+other.z);
    }
    bool operator==(Vector3 other){
        return x==other.x&&y==other.y&&z==other.z;
    }
    bool operator!=(Vector3 other){
        return !(*this == other);
    }
};

enum class BodyPart{
    Head,
    Torso,
    LeftLeg,
    RightLeg,
    LeftArm,
    RightArm,
    Default
};

//doesn't actually draw a line but it's useful for understanding what is going on
//this just gives opengl vertices to use for whatever primitive mode
void drawLine(const Vector3& point1, const Vector3& point2){
    glVertex3d(point1.x, point1.y, point1.z);
    glVertex3d(point2.x, point2.y, point2.z);
}

//doesn't actually draw a quad, but it's useful for understanding what is going on
//this gives opengl 4 vertices for whatever operation it is going to do
void drawFace(const Vector3& topLeftPoint, const Vector3& topRightPoint, const Vector3& bottomLeftPoint, const Vector3& bottomRightPoint){
    glVertex3d(topLeftPoint.x, topLeftPoint.y, topLeftPoint.z);
    glVertex3d(topRightPoint.x, topRightPoint.y, topRightPoint.z);
    glVertex3d(bottomLeftPoint.x, bottomLeftPoint.y, bottomLeftPoint.z);
    glVertex3d(bottomRightPoint.x, bottomRightPoint.y, bottomRightPoint.z);
}
