#include "Camera.h"
#include <iostream>

void Camera::computeDir(float deltaAngle) {
    m_camAngle += deltaAngle;
    m_lx = sin(m_camAngle);
    m_lz = -cos(m_camAngle);
}

void Camera::computePos(float deltaMove) {
    m_x += deltaMove * m_lx * 0.1f;
    m_z += deltaMove * m_lz * 0.1f;
}

void Camera::draw(char mode) const{
    glPushMatrix();
        //set ground color to blue
        glColor3d(0, 0, 1);
        glTranslated(m_x, 1.0f, m_z);
        float angle = atan2(m_lx, m_lz) * 180.0f / std::numbers::pi;
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        if (mode == 'w') {
            glutWireCube(1.0f);
        }
        else if (mode == 's') {
            glutSolidCube(1.0f);
        }
    glPopMatrix();
}

void Camera::setCameraFPV() const {
    gluLookAt(m_x, 5.0f, m_z,
        m_x+m_lx, 5.0f, m_z+m_lz,
        m_up.x, m_up.y, m_up.z);
}

void Camera::setCameraRMV() const {
    gluLookAt(m_x, 5.0f, m_z,
        m_x - m_lx, 5.0f, m_z - m_lz,
        m_up.x, m_up.y, m_up.z);
}

void Camera::setCameraESV() const {
    gluLookAt(m_x, 90.0f, m_z,
        m_x + m_lx, 0.0f, m_z + m_lz,
        0.0f, 0.0f, -1.0f);
}