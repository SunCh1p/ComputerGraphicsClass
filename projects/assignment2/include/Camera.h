#pragma once
#include <numbers>
#include "util.h"
//class for camera
class Camera {
public:
    //constructor
    Camera() : m_eye(Vector3(0, 0, 0)), m_center(Vector3(0, 5, 0)), m_up(Vector3(0, 1, 0)) {}
    //mutator methods
    //sets position of camera
    void setPosition(Vector3 position);
    //set position camera is looking at
    void setTarget(Vector3 targetPosition);
    //defines what up is for the camera
    void setUp(Vector3 newUp);
    //changes perspective to either orthographic or perspective projection
    void changePerspective(char perspectiveFlag);
    //used to zoom camera in
    void zoomCamera(GLdouble dir);
    //Resource used for implementing camera rotation around what it's looking at
    //basically we use cylindrical coordinates to achieve camera orbit
    //https://tutorial.math.lamar.edu/Classes/CalcIII/CylindricalCoords.aspx
    //camera rotation around x axis
    void rotateAroundXAxis(GLdouble angle);
    //camera rotation around y axis
    void rotateAroundYAxis(GLdouble angle);
    //camera rotation around z axis
    void rotateAroundZAxis(GLdouble angle);
    //accessor methods
    //gets the position of the camera
    Vector3 getPosition() const;
    //gets the target position for which the camera looks at(m_center)
    Vector3 getTarget() const;
    //gets the up vector for camera
    Vector3 getUp() const;
    //sets camera
    void setCamera() const;
private:
    //camera position
    Vector3 m_eye;
    //what the camera is looking at
    Vector3 m_center;
    //which direction is up for the camera
    Vector3 m_up;
};