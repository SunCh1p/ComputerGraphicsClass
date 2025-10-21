#pragma once
#include <numbers>
#include "DrawComponent.h"
#include "Util.h"
//class for camera
class Camera : public DrawInterface {
public:
    //constructor
    Camera() : m_x(0.0f), m_z(10.0f), m_lx(0.0f), m_lz(-1.0f), m_camAngle(0.0f), m_up(Vector3(0, 1, 0)) {}
    void computePos(float deltaMove); //used to figure out position camera is supposed to go to
    void computeDir(float deltaAngle); //used to figure out direction vector in which camera will use to advance position
    void draw(char mode) const override;
    //accessor methods
    void setCameraFPV() const; //sets camera first person view mode
    void setCameraRMV() const; //sets camera using rear view mirror mode
    void setCameraESV() const; //sets camera above everything looking down
private:
    float m_x, m_z; //camera posiition
    float m_lx, m_lz; //what camera is looking at
    float m_camAngle; 
    //which direction is up for the camera
    Vector3 m_up;
};