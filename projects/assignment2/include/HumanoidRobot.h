#pragma once
#include "composite.h"

//Huamnoid robot class which is composed of objects with the component interface defined in composite.h
class HumanoidRobot {
public:
    //default constructor
    HumanoidRobot(Vector3 position = Vector3(0, 0, 0)) : m_position(position), m_rotation({ 0,0,0 }) {}
    //draws all components in children hash map
    void draw(char mode, bool grayScale);
    //sets the angle if the object is being drawn with a rotation
    void setAngle(GLdouble angle, char axis);
    //can get the off set angle of object in x y and z dimension
    GLdouble getAngle(char dimension);
    //add child, this is how I add various bodyparts
    void addChild(BodyPart part, std::unique_ptr<Component> child);
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
    std::unordered_map<BodyPart, std::unique_ptr<Component>> m_children;
};
