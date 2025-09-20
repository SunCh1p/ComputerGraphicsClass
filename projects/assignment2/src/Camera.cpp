#include "Camera.h"
#include <iostream>

//grader please ignore this file, work in progress, hopefully will have his class finished for next assignment

void Camera::setPosition(Vector3 position) { m_eye = position; }

void Camera::setTarget(Vector3 targetPosition) { m_center = targetPosition; }

void Camera::setUp(Vector3 newUp) { m_up = newUp; }

void Camera::changePerspective(char perspectiveFlag) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (perspectiveFlag == 'o') {
        glOrtho(-10, 10, -10, 10, 1, 50);
    }
    else {
        glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 50);
    }
    glMatrixMode(GL_MODELVIEW);
    setCamera();
}

void Camera::rotateAroundXAxis(GLdouble angle) {
    //compute radius on y z plane
    GLdouble radius = sqrt((m_eye.y - m_center.y) * (m_eye.y - m_center.y) + (m_eye.z - m_center.z) * (m_eye.z - m_center.z));
    //deal with case that radius is zero, if radius is zero, we cannot compute theta, thus orbit cannot occur
    if (radius < 0.0001) {
        return;
    }
    //compute theta using atan2 to get theta because reasons I don't understand entirely but basically it can get an angle regardless of octant
    GLdouble theta = atan2(m_eye.y - m_center.y, m_eye.z - m_center.z);
    //convert angle to radians
    angle = angle * std::numbers::pi / 180;
    //add angle to theta
    theta += angle;
    //compute new y and z and adjust camera
    m_eye.z = m_center.z + radius * cos(theta);
    m_eye.y = m_center.y + radius * sin(theta);
}

void Camera::zoomCamera(GLdouble dir) {
    //get the vector from camera position to what it's looking at(center)
    Vector3 direction = m_center - m_eye;
    //normalize the direction so we can get a set unit to move in either a closer or farther direction
    direction.Normalize();
    //dir == 1 means move towards target
    if (dir == 1) {
        //zoom toward target
        //check if zooming in will make camera translate past target, if so, don't let it
        Vector3 newEyePos = m_eye + direction * 0.1;
        //get the direction of newEyePosition to the target
        Vector3 dirOfNewToTarget = m_center - newEyePos;
        //if dot product is zero or negative, vectors don't point in the same direction anymore
        if (direction.DotProduct(dirOfNewToTarget) > 0) {
            //translate camera position
            m_eye = newEyePos;
        }
        else {
            //if too close, output message
            std::cout << "Cannot zoom in any further" << std::endl;
        }
        
    }
    else {
        //can zoom out as far as you want
        Vector3 newEyePos = m_eye + direction * -0.1;
        m_eye = newEyePos;
    }



}

void Camera::rotateAroundYAxis(GLdouble angle) {
    //computer radius on z x plane
    GLdouble radius = sqrt((m_eye.x - m_center.x) * (m_eye.x - m_center.x) + (m_eye.z - m_center.z) * (m_eye.z - m_center.z));
    //deal with case that radius is zero, if radius is zero, we cannot compute theta, thus orbit cannot occur
    if (radius < 0.0001) {
        return;
    }
    //compute theta using atan2 to get theta because reasons I don't understand entirely but basically it can get an angle regardless of quadrant
    GLdouble theta = atan2(m_eye.x - m_center.x, m_eye.z - m_center.z);
    //convert angle to radians
    angle = angle * std::numbers::pi / 180;
    //add angle to theta
    theta += angle;
    //compute new x and z and adjust camera
    m_eye.z = m_center.z + radius * cos(theta);
    m_eye.x = m_center.x + radius * sin(theta);
}

void Camera::rotateAroundZAxis(GLdouble angle) {
    //computer radius on y x plane
    GLdouble radius = sqrt((m_eye.y - m_center.y) * (m_eye.y - m_center.y) + (m_eye.x - m_center.x) * (m_eye.x - m_center.x));
    //deal with case that radius is zero, if radius is zero, we cannot compute theta, thus orbit cannot occur
    if (radius < 0.0001) {
        return;
    }
    //compute theta using atan2 to get theta because reasons I don't understand entirely but basically it can get an angle regardless of quadrant
    GLdouble theta = atan2(m_eye.y - m_center.y, m_eye.x - m_center.x);
    //convert angle to radians
    angle = angle * std::numbers::pi / 180;
    //add angle to theta
    theta += angle;
    //compute new x and z and adjust camera
    m_eye.x = m_center.x + radius * cos(theta);
    m_eye.y = m_center.y + radius * sin(theta);
}

Vector3 Camera::getPosition() const { return m_eye; }

Vector3 Camera::getTarget() const { return m_center; }

Vector3 Camera::getUp() const { return m_up; }

void Camera::setCamera() const {
    //set the camera
    gluLookAt(m_eye.x, m_eye.y, m_eye.z,
        m_center.x, m_center.y, m_center.z,
        m_up.x, m_up.y, m_up.z);
}