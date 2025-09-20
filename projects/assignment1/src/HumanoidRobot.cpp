#include "HumanoidRobot.h"

void HumanoidRobot::draw(char mode, bool grayScale) {
    glPushMatrix();
    //rotate object
    glRotated(m_rotation.x, 1.0, 0.0, 0.0);
    glRotated(m_rotation.y, 0.0, 1.0, 0.0);
    glRotated(m_rotation.z, 0.0, 0.0, 1.0);
    //draw all m_children relative to current position as well as passing drawing mode and black and white mode to them
    for (auto& it : m_children) {
        it.second->draw(grayScale, m_position, mode);
    }
    glPopMatrix();
}

void HumanoidRobot::setAngle(GLdouble angle, char axis) {
    //used to set offset angle for purposes of object rotation for corresponding axis(i call it dimension in other comments)
    if (axis == 'x') {
        m_rotation.x = m_rotation.x + angle;
        if (m_rotation.x > 360.1) {
            m_rotation.x -= 360;
        }
    }
    else if (axis == 'y') {
        m_rotation.y = m_rotation.y + angle;
        if (m_rotation.y > 360.1) {
            m_rotation.y -= 360;
        }
    }
    else {
        m_rotation.z = m_rotation.z + angle;
        if (m_rotation.z > 360.1) {
            m_rotation.z -= 360;
        }
    }
}

GLdouble HumanoidRobot::getAngle(char dimension) {
    //gets offset angle in specified dimension
    if (dimension == 'x') {
        return m_rotation.x;
    }
    else if (dimension == 'y') {
        return m_rotation.y;
    }
    else {
        return m_rotation.z;
    }
}

void HumanoidRobot::addChild(BodyPart part, std::unique_ptr<Component> child) {
    //move unique ptr into container
    m_children[part] = std::move(child);
}

void HumanoidRobot::colorBodyPart(BodyPart part, int option) {
    Vector3 color = { 0,0,0 };
    if (option == 0) {
        //set color to red
        color = { 1,0,0 };
    }
    else if (option == 1) {
        //set color to green
        color = { 0,1,0 };
    }
    else if(option == 2){
        //set color to blue
        color = { 0,0,1 };
    }
    else if (option == 3){
        //set color to yelloiw
        color = {1,1,0};
    }
    //check if part exists
    if (m_children.find(part) != m_children.end()) {
        //if so color the bodypart
        m_children[part]->setColor(color);
    }
}

void HumanoidRobot::rotateBodyPart(BodyPart part, char dimension, GLdouble angle) {
    //check if body part exists
    auto it = m_children.find(part);
    if (it != m_children.end()) {
        //call child's rotate function
        it->second->setAngle(angle, dimension);
    }
}

GLdouble HumanoidRobot::getAngleBodyPart(BodyPart part, char dimension) {
    //check if body part exists
    auto it = m_children.find(part);
    if (it != m_children.end()) {
        //call child's rotate function
        return it->second->getAngle(dimension);
    }
}