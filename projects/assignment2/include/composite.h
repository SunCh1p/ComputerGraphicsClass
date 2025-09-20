#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <GL/glut.h>
#include "util.h"

/*Using Composite Design pattern as inspiration but it doesn't strictly adhere,
    In the composite design pattern there is an abstract component which declares a common interface,
    a composite which also has a common interface, and a leaf node which has a common interface as well but no children.
*/
//interface in which all body parts will use
class Component{
    public:
        Component(Vector3 position = Vector3(0,0,0), Vector3 color=Vector3(0,1,0)): m_position(position), m_color(color){}
        //must be overwritten
        virtual void draw(Vector3 parentPosition, char mode) const = 0;
        //optional to override
        virtual void setColor(Vector3 color){m_color = color;}
    protected:
        //coordinates relative to parent where parent is (0,0,0)
        Vector3 m_position;
        Vector3 m_color;
};
class HumanoidRobot{
    public:
        HumanoidRobot(Vector3 position = Vector3(0,0,0)): m_position(position), m_rotation({0,0,0}){}
        void draw(char mode){
            glPushMatrix();
                glRotated(m_rotation.x, 1.0, 0.0, 0.0);
                glRotated(m_rotation.y, 0.0, 1.0, 0.0);
                glRotated(m_rotation.z, 0.0, 0.0, 1.0);
                //draw all m_children relative to current position
                for(auto& it: m_children){
                    it.second->draw(m_position, mode);
                }
            glPopMatrix();
        }
        void setAngle(GLdouble angle, char axis){
            if(axis == 'x'){
                m_rotation.x = m_rotation.x + angle;
                if(m_rotation.x > 360.1){
                    m_rotation.x -= 360;
                }
            } else if(axis == 'y'){
                m_rotation.y = m_rotation.y+angle;
                if(m_rotation.y > 360.1){
                    m_rotation.y -= 360;
                }
            } else {
                m_rotation.z = m_rotation.z+angle;
                if(m_rotation.z > 360.1){
                    m_rotation.z -= 360;
                }
            }
        }
        void addChild(BodyPart part ,std::unique_ptr<Component> child){
            //move unique ptr into container
            m_children[part] = std::move(child);
        }
        void colorBodyPart(BodyPart part, int option){
            Vector3 color = {0,0,0};
            if(option == 0){
                //set color to red
                color = {1,0,0};
            } else if (option == 1){
                //set color to green
                color = {0,1,0};
            } else {
                //set color to blue
                color = {0,0,1};
            }
            //check if part exists
            if(m_children.find(part) != m_children.end()){
                //if so color the bodypart
                m_children[part]->setColor(color);
            }
        }
    private:
        Vector3 m_position;
        Vector3 m_rotation;
        std::unordered_map<BodyPart, std::unique_ptr<Component>> m_children;
};


//composite classes/non exist atm/
class Box : public Component{
    public:
        Box(GLdouble frontTopLeftX, GLdouble frontTopLeftY, GLdouble frontTopLeftZ, GLdouble width, GLdouble height, GLdouble length){
            m_position = Vector3(frontTopLeftX, frontTopLeftY, frontTopLeftZ);
            m_width = width;
            m_height = height;
            m_length = length;
        }
        void draw(Vector3 parentPosition, char mode) const override{
            //calculate global position of front top left corner
            Vector3 globalPosition = parentPosition+m_position;
            glPushMatrix();
                //set the position of front top left corner
                glTranslated(globalPosition.x, globalPosition.y, globalPosition.z);
                //set the color
                glColor3d(m_color.x, m_color.y, m_color.z);
                //set the draw mode
                GLenum drawMode = GL_ZERO;
                if(mode == 'p'){
                    glBegin(GL_POINTS);
                        //draw upper 4 corners
                        glVertex3d(0, 0, 0);
                        glVertex3d(0, 0, 0-m_length);
                        glVertex3d(0+m_width, 0, 0);
                        glVertex3d(0+m_width, 0, 0-m_length);
                        //draw upper 4 corners
                        glVertex3d(0, 0-m_height, 0);
                        glVertex3d(0, 0-m_height, 0-m_length);
                        glVertex3d(0+m_width, 0-m_height, 0);
                        glVertex3d(0+m_width, 0-m_height, 0-m_length);
                    glEnd();
                } else if(mode == 'w'){
                    glBegin(GL_LINES);
                        //line going from front top left to back top left
                        drawLine(Vector3(0, 0, 0), Vector3(0, 0, 0-m_length));
                        //line going from back top left to back top right
                        drawLine(Vector3(0, 0, 0-m_length), Vector3(0+m_width, 0, 0-m_length));
                        //line going from back top right to front top right
                        drawLine(Vector3(0+m_width, 0, 0-m_length), Vector3(0+m_width, 0, 0));
                        //line going from front top right to front top left
                        drawLine(Vector3(0+m_width, 0, 0), Vector3(0, 0, 0));
                        //line going from front top left to front bottom left
                        drawLine(Vector3(0, 0, 0), Vector3(0, 0-m_height, 0));
                        //line going from front top right to front bottom right
                        drawLine(Vector3(0+m_width, 0, 0), Vector3(0+m_width, 0-m_height, 0));
                        //line going from back top right to back bottom right
                        drawLine(Vector3(0+m_width, 0, 0-m_length), Vector3(0+m_width, 0-m_height, 0-m_length));
                        //line going from back top left to back bottom left
                        drawLine(Vector3(0, 0, 0-m_length), Vector3(0, 0-m_height, 0-m_length));
                        //line going from front bottom left to back bottom left
                        drawLine(Vector3(0, 0-m_height, 0), Vector3(0, 0-m_height, 0-m_length));
                        //line going from back bottom left to back bottom right
                        drawLine(Vector3(0, 0-m_height, 0-m_length), Vector3(0+m_width, 0-m_height, 0-m_length));
                        //line going from back bottom right to front bottom right
                        drawLine(Vector3(0+m_width, 0-m_height, 0-m_length), Vector3(0+m_width, 0-m_height, 0));
                        //line going from front bottom right to front bottom left
                        drawLine(Vector3(0+m_width, 0-m_height, 0), Vector3(0, 0-m_height, 0));
                    glEnd();
                } else if(mode == 's'){
                    glBegin(GL_QUADS);
                        Vector3 frontTopLeft(0, 0, 0);
                        Vector3 frontTopRight(0+m_width, 0, 0);
                        Vector3 backTopLeft(0, 0, 0-m_length);
                        Vector3 backTopRight(0+m_width, 0, 0-m_length);
                        Vector3 frontBottomLeft(0, 0-m_height, 0);
                        Vector3 frontBottomRight(0+m_width, 0-m_height, 0);
                        Vector3 backBottomLeft(0, 0-m_height, 0-m_length);
                        Vector3 backBottomRight(0+m_width, 0-m_height, 0-m_length);
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
    private:
        GLdouble m_width;   //how long it is across x axis in the positive direction
        GLdouble m_height;  //how long it is across y axis in the positive direction
        GLdouble m_length;  //how long it is across z axis in the positive direction
};

//axes(a leaf class)
class Axes : public Component{
    public:
        Axes(Vector3 position = Vector3(0,0,0)) : Component(position){}
        void draw(Vector3 parentPosition = Vector3(0,0,0), char mode='c') const{
            //get global position
            Vector3 globalPosition = parentPosition+m_position;
            //translate position
            glTranslated(globalPosition.x, globalPosition.y, globalPosition.z);
            //push a new matrix
            glPushMatrix();
                glBegin(GL_LINES);
                    //draw x red relative to parents position
                    glColor3f(1,0,0);
                    glVertex3f(0, 0, 0);
                    glVertex3f(0+100, 0, 0);
                    //draw y green
                    glColor3f(0,1,0);
                    glVertex3f(0, 0, 0);
                    glVertex3f(0, 0+100, 0);
                    //draw z blue
                    glColor3f(0,0,1);
                    glVertex3f(0, 0, 0);
                    glVertex3f(0, 0, 0+100);
                glEnd();
            //reset to state before function
            glPopMatrix();
        }
};

//class for camera
class Camera{
    public:
        //constructor
        Camera(): m_eye(Vector3(0,0,0)), m_center(Vector3(0,0,0)), m_up(Vector3(0,1,0)){}
        //mutator methods
        void setPosition(Vector3 position){m_eye = position;}
        void setTarget(Vector3 targetPosition){m_center = targetPosition;}
        void setUp(Vector3 newUp){m_up = newUp;}
        void changePerspective(char perspectiveFlag){
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            if(perspectiveFlag == 'o'){
                glOrtho(-10, 10, -10, 10, 0.1, 50);
            } else {
                glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 50);
            }
            glMatrixMode(GL_MODELVIEW);
            setCamera();
        }
        //Resource used for implementing camera rotation around what it's looking at
        //basically we use cylindrical coordinates to achieve camera orbit
        //https://tutorial.math.lamar.edu/Classes/CalcIII/CylindricalCoords.aspx
        void rotateAroundXAxis(GLdouble angle){
            //compute radius on y z plane
            GLdouble radius = sqrt((m_eye.y-m_center.y)*(m_eye.y-m_center.y) + (m_eye.z-m_center.z)*(m_eye.z-m_center.z));
            //deal with case that radius is zero, if radius is zero, we cannot compute theta, thus orbit cannot occur
            if(radius < 0.0001){
                return;
            }
            //compute theta using atan2 to get theta because reasons I don't understand entirely but basically it can get an angle regardless of quadrant
            GLdouble theta = atan2(m_eye.y-m_center.y, m_eye.z-m_center.z);
            //convert angle to radians
            angle = angle*M_PI/180;
            //add angle to theta
            theta+=angle;
            //compute new y and z and adjust camera
            m_eye.z = m_center.z+radius*cos(theta);
            m_eye.y = m_center.y+radius*sin(theta);
        }
        void rotateAroundYAxis(GLdouble angle){
            //computer radius on z x plane
            GLdouble radius = sqrt((m_eye.x-m_center.x)*(m_eye.x-m_center.x) + (m_eye.z-m_center.z)*(m_eye.z-m_center.z));
            //deal with case that radius is zero, if radius is zero, we cannot compute theta, thus orbit cannot occur
            if(radius < 0.0001){
                return;
            }
            //compute theta using atan2 to get theta because reasons I don't understand entirely but basically it can get an angle regardless of quadrant
            GLdouble theta = atan2(m_eye.x - m_center.x, m_eye.z - m_center.z);
            //convert angle to radians
            angle = angle*M_PI/180;
            //add angle to theta
            theta+=angle;
            //compute new x and z and adjust camera
            m_eye.z = m_center.z+radius*cos(theta);
            m_eye.x = m_center.x+radius*sin(theta);
        }
        void rotateAroundZAxis(GLdouble angle){
            //computer radius on y x plane
            GLdouble radius = sqrt((m_eye.y-m_center.y)*(m_eye.y-m_center.y) + (m_eye.x-m_center.x)*(m_eye.x-m_center.x));
            //deal with case that radius is zero, if radius is zero, we cannot compute theta, thus orbit cannot occur
            if(radius < 0.0001){
                return;
            }
            //compute theta using atan2 to get theta because reasons I don't understand entirely but basically it can get an angle regardless of quadrant
            GLdouble theta = atan2(m_eye.y - m_center.y, m_eye.x - m_center.x);
            //convert angle to radians
            angle = angle*M_PI/180;
            //add angle to theta
            theta+=angle;
            //compute new x and z and adjust camera
            m_eye.x = m_center.x + radius * cos(theta);
            m_eye.y = m_center.y + radius * sin(theta);
        }
        //accessor methods
        Vector3 getPosition() const{return m_eye;}
        Vector3 getTarget() const{return m_center;}
        Vector3 getUp() const{return m_up;}
        void setCamera() const{
            //set the camera
            gluLookAt(	m_eye.x, m_eye.y, m_eye.z,
			m_center.x, m_center.y,  m_center.z,
			m_up.x, m_up.y,  m_up.z);
        }
    private:
        //camera position
        Vector3 m_eye;
        //what the camera is looking at
        Vector3 m_center;
        //which direction is up for the camera
        Vector3 m_up;
        //
};
