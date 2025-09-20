#include "Box.h"

Box::Box(GLdouble frontTopLeftX, GLdouble frontTopLeftY, GLdouble frontTopLeftZ, GLdouble width, GLdouble height, GLdouble length) {
    m_position = Vector3(frontTopLeftX, frontTopLeftY, frontTopLeftZ);
    m_width = width;
    m_height = height;
    m_length = length;
}

void Box::draw(bool grayScale, Vector3 parentPosition, char mode) const{
    //calculate global position of front top left corner
    Vector3 globalPosition = parentPosition + m_position;
    glPushMatrix();
    //set the position of front top left corner
    glTranslated(globalPosition.x, globalPosition.y, globalPosition.z);
    //set the rotation of box
    glRotated(m_rotation.x, 1.0, 0.0, 0.0);
    glRotated(m_rotation.y, 0.0, 1.0, 0.0);
    glRotated(m_rotation.z, 0.0, 0.0, 1.0);
    //set the color, differs depending if it is grayscale or not
    if (grayScale) {
        //https://www.grayscaleimage.com/three-algorithms-for-converting-color-to-grayscale/
        //using luminosity method from this resource to achieve gray scaling
        GLdouble gray = m_color.x * 0.299 + m_color.y * 0.587 + m_color.z * 0.114;
        glColor3d(gray, gray, gray);
    }
    else {
        glColor3d(m_color.x, m_color.y, m_color.z);
    }
    //set the draw mode
    GLenum drawMode = GL_ZERO;
    if (mode == 'p') {
        glBegin(GL_POINTS);
        //draw upper 4 corners
        glVertex3d(0, 0, 0);
        glVertex3d(0, 0, 0 - m_length);
        glVertex3d(0 + m_width, 0, 0);
        glVertex3d(0 + m_width, 0, 0 - m_length);
        //draw upper 4 corners
        glVertex3d(0, 0 - m_height, 0);
        glVertex3d(0, 0 - m_height, 0 - m_length);
        glVertex3d(0 + m_width, 0 - m_height, 0);
        glVertex3d(0 + m_width, 0 - m_height, 0 - m_length);
        glEnd();
    }
    else if (mode == 'w') {
        glBegin(GL_LINES);
        //line going from front top left to back top left
        drawLine(Vector3(0, 0, 0), Vector3(0, 0, 0 - m_length));
        //line going from back top left to back top right
        drawLine(Vector3(0, 0, 0 - m_length), Vector3(0 + m_width, 0, 0 - m_length));
        //line going from back top right to front top right
        drawLine(Vector3(0 + m_width, 0, 0 - m_length), Vector3(0 + m_width, 0, 0));
        //line going from front top right to front top left
        drawLine(Vector3(0 + m_width, 0, 0), Vector3(0, 0, 0));
        //line going from front top left to front bottom left
        drawLine(Vector3(0, 0, 0), Vector3(0, 0 - m_height, 0));
        //line going from front top right to front bottom right
        drawLine(Vector3(0 + m_width, 0, 0), Vector3(0 + m_width, 0 - m_height, 0));
        //line going from back top right to back bottom right
        drawLine(Vector3(0 + m_width, 0, 0 - m_length), Vector3(0 + m_width, 0 - m_height, 0 - m_length));
        //line going from back top left to back bottom left
        drawLine(Vector3(0, 0, 0 - m_length), Vector3(0, 0 - m_height, 0 - m_length));
        //line going from front bottom left to back bottom left
        drawLine(Vector3(0, 0 - m_height, 0), Vector3(0, 0 - m_height, 0 - m_length));
        //line going from back bottom left to back bottom right
        drawLine(Vector3(0, 0 - m_height, 0 - m_length), Vector3(0 + m_width, 0 - m_height, 0 - m_length));
        //line going from back bottom right to front bottom right
        drawLine(Vector3(0 + m_width, 0 - m_height, 0 - m_length), Vector3(0 + m_width, 0 - m_height, 0));
        //line going from front bottom right to front bottom left
        drawLine(Vector3(0 + m_width, 0 - m_height, 0), Vector3(0, 0 - m_height, 0));
        glEnd();
    }
    else if (mode == 's') {
        glBegin(GL_QUADS);
        Vector3 frontTopLeft(0, 0, 0);
        Vector3 frontTopRight(0 + m_width, 0, 0);
        Vector3 backTopLeft(0, 0, 0 - m_length);
        Vector3 backTopRight(0 + m_width, 0, 0 - m_length);
        Vector3 frontBottomLeft(0, 0 - m_height, 0);
        Vector3 frontBottomRight(0 + m_width, 0 - m_height, 0);
        Vector3 backBottomLeft(0, 0 - m_height, 0 - m_length);
        Vector3 backBottomRight(0 + m_width, 0 - m_height, 0 - m_length);
        //draw top face
        drawFace(frontTopLeft, frontTopRight, backTopRight, backTopLeft);
        //draw bottom face
        drawFace(frontBottomLeft, frontBottomRight, backBottomRight, backBottomLeft);
        //draw front face
        drawFace(frontTopLeft, frontTopRight, frontBottomRight, frontBottomLeft);
        //draw left face
        drawFace(frontTopLeft, backTopLeft, backBottomLeft, frontBottomRight);
        //draw back face
        drawFace(backTopLeft, backTopRight, backBottomRight, backBottomLeft);
        //draw right face
        drawFace(frontTopRight, backTopRight, backBottomRight, frontBottomRight);
        glEnd();
    }
    glPopMatrix();
    //otherwise, do nothing
}

void Box::setAngle(GLdouble angle, char dimension) {
    //sets offset angle of object in dimension corresponding to the input parameter 'dimension'
    if (dimension == 'x') {
        m_rotation.x = m_rotation.x + angle;
        if (m_rotation.x > 360.1) {
            m_rotation.x -= 360;
        }
    }
    else if (dimension == 'y') {
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

GLdouble Box::getAngle(char dimension) {
    //gets offset angle of object in dimension corresponding to the input parameter 'dimension'
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