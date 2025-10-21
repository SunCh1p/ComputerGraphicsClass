#include "Axes.h"

void Axes::draw(char mode) const {
    glPushMatrix();
    //translate position
    glTranslated(m_position.x, m_position.y, m_position.z);
    glBegin(GL_LINES);
    //draw x red relative to parents position
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0 + 100, 0, 0);
    //draw y green
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0 + 100, 0);
    //draw z blue
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 0 + 100);
    glEnd();
    //reset to state before function
    glPopMatrix();
}