#pragma once
#pragma once
#include <GL/glut.h>
#include <cmath>
//Vector3 struct, will turn into a class in the future
//used to have a convenient and easy way to represent vectors
//inspired by the best solution example in the assignment
struct Vector3 {
    GLdouble x, y, z;
    Vector3() : x(0), y(0), z(0) {}
    Vector3(GLdouble X, GLdouble Y, GLdouble Z) : x(X), y(Y), z(Z) {}
    GLdouble getMagnitude() {
        return std::sqrt(x * x + y * y + z * z);
    }
    void Normalize() {
        //get the magnitude
        GLdouble magnitude = getMagnitude();
        if (magnitude > 0) {
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
        }

    }

    Vector3 operator*(double scalar) {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    double DotProduct(Vector3& other) {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 operator+(const Vector3& other) {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    bool operator==(Vector3 other) {
        return x == other.x && y == other.y && z == other.z;
    }
    bool operator!=(Vector3 other) {
        return !(*this == other);
    }
};

//used by HumanoidRobot class to map a bodypart scoped enum to a object with component interface
enum class BodyPart {
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
void drawLine(const Vector3& point1, const Vector3& point2);

//doesn't actually draw a quad, but it's useful for understanding what is going on
//this gives opengl 4 vertices for whatever operation it is going to do
void drawFace(const Vector3& topLeftPoint, const Vector3& topRightPoint, const Vector3& bottomLeftPoint, const Vector3& bottomRightPoint);
