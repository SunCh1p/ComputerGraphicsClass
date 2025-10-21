#pragma once
#include "DrawComponent.h"

//Huamnoid robot class which is composed of objects with the component interface defined in composite.h
class HumanoidRobot {
public:
    //default constructor
    HumanoidRobot(Vector3 position = Vector3(0, 0, 0)) : m_position(position), m_rotation({ 0,0,0 }) {}
    //move constructor
    HumanoidRobot(HumanoidRobot&&) = default;
    //move assignment operator
    HumanoidRobot& operator=(HumanoidRobot&&) = default;
    //draws all components in children hash map
    void draw(char mode);
    //sets the angle if the object is being drawn with a rotation
    void setAngle(GLdouble angle, char axis);
    //sets the position of the robot
    void setPos(Vector3 pos);
    //gets the position of the robot
    Vector3 getPos();
    //gets the angle of the robot relative to a dimension
    GLdouble getAngle(char dimension);
    //add child, this is how I add various bodyparts
    void addChild(BodyPart part, std::unique_ptr<DrawInterface> child);
    //used to select and color a specific body part within the humanoid robot class
    void colorBodyPart(BodyPart part, int option);
    //used to rotate a specific body part, used for animation
    void rotateBodyPart(BodyPart part, char dimension, GLdouble angle);
    //gets the angle of a bodypart
    GLdouble getAngleBodyPart(BodyPart part, char dimension);
private:
    //position of the object
    Vector3 m_position;
    //rotation of the object
    Vector3 m_rotation;
    //map of all children to be drawn
    std::unordered_map<BodyPart, std::unique_ptr<DrawInterface>> m_children;
};
