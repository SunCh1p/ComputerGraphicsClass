#include "Axes.h"

void Axes::draw(bool grayScale, Vector3 parentPosition, char mode) const {
    //get global position
    Vector3 globalPosition = parentPosition + m_position;
    //translate position
    glTranslated(globalPosition.x, globalPosition.y, globalPosition.z);
    //push a new matrix
    glPushMatrix();
    glBegin(GL_LINES);
    //draw x red relative to parents position
    if (grayScale) {
        //https://www.grayscaleimage.com/three-algorithms-for-converting-color-to-grayscale/
        //gray scaling achieved using luminosity method
        GLdouble gray = 1 * 0.299;
        glColor3f(gray, gray, gray);
    }
    else {
        glColor3f(1, 0, 0);
    }
    glVertex3f(0, 0, 0);
    glVertex3f(0 + 100, 0, 0);
    //draw y green
    if (grayScale) {
        GLdouble gray = 1 * 0.587;
        glColor3f(gray, gray, gray);
    }
    else {
        glColor3f(0, 1, 0);
    }
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0 + 100, 0);
    //draw z blue
    if (grayScale) {
        GLdouble gray = 1 * 0.114;
        glColor3f(gray, gray, gray);
    }
    else {
        glColor3f(0, 0, 1);
    }
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 0 + 100);
    glEnd();
    //reset to state before function
    glPopMatrix();
}