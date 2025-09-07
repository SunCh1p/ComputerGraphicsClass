#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <GL/glut.h>

//TODO create vector3 class
struct Vector3{
    GLdouble x, y, z;
    Vector3(GLdouble X, GLdouble Y, GLdouble Z) : x(X), y(Y), z(Z){}
    Vector3 operator+(const Vector3& other){
        return Vector3(x+other.x, y+other.y, z+other.z);
    }
    bool operator==(Vector3 other){
        return x==other.x&&y==other.y&&z==other.z;
    }
    bool operator!=(Vector3 other){
        return !(*this == other);
    }
};

enum class BodyPart{
    Head,
    Torso,
    LeftLeg,
    RightLeg,
    LeftArm,
    RightArm,
    Default
};

//Using Composite Design pattern
//abstract component used for defining scenes and things that can exist within scenes
class Component{
    public:
        Component(Vector3 position = Vector3(0,0,0)): m_position(position) {}
        //must be overwritten
        virtual void draw(Vector3 parentPosition) const = 0;
        //optional to override
        virtual void addChild(BodyPart part ,std::unique_ptr<Component> child){}
        virtual void addChild(std::unique_ptr<Component> child){}

    protected:
        //coordinates relative to parent where parent is (0,0,0)
        Vector3 m_position;
  
};

//composite classes
class Scene : public Component{
    public:
        Scene(Vector3 position = Vector3(0,0,0)): Component(position){}
        void draw(Vector3 parentPosition = {0,0,0}) const override{
            //get position in world
            Vector3 globalPosition = parentPosition + m_position;
            //draw all m_children relative to current position
            for(auto& it: m_children){
                it->draw(globalPosition);
            }
        }
        void addChild(std::unique_ptr<Component> child) override{
            //move unique ptr into container
            m_children.push_back(std::move(child));
        }
    private:
        std::vector<std::unique_ptr<Component>> m_children;
};

class HumanoidRobot : public Component{
    public:
        HumanoidRobot(Vector3 position = Vector3(0,0,0)): Component(position){}
        void draw(Vector3 parentPosition = {0,0,0}) const override{
            //get position in world
            Vector3 globalPosition = parentPosition + m_position;
            //draw all m_children relative to current position
            for(auto& it: m_children){
                it.second->draw(globalPosition);
            }
        }
        void addChild(BodyPart part ,std::unique_ptr<Component> child) override{
            //move unique ptr into container
            m_children[part] = std::move(child);
        }

    private:
        //all m_children of humanoid robot
        std::unordered_map<BodyPart, std::unique_ptr<Component>> m_children;
};

//Cube(a leaf class)
class Cube : public Component{
    public:
        Cube(GLdouble size, Vector3 position = Vector3(0,0,0)): m_size(size), Component(position) {}
        void draw(Vector3 parentPosition) const override{
            //push a new matrix
            glPushMatrix();
                //apply color(Everything is red for now)
                glColor3d(1,0,0);
                //set the position
                Vector3 globalPosition = parentPosition+m_position;
                glTranslated(globalPosition.x, globalPosition.y, globalPosition.z);
                //draw the cube(Solid for now)
                glutWireCube(m_size);
            //reset to state before function
            glPopMatrix();
        }
    private:
        GLdouble m_size;
};

//axes(a leaf class)
class Axes : public Component{
    public:
        Axes(Vector3 position = Vector3(0,0,0)) : Component(position){}
        void draw(Vector3 parentPosition) const override{
            //get global position
            Vector3 globalPosition = parentPosition+m_position;
            //push a new matrix
            glPushMatrix();
            //draw x red relative to parents position
            glBegin(GL_LINES);
            glColor3f(1,0,0);
            glVertex3f(globalPosition.x, globalPosition.y, globalPosition.z);
            glVertex3f(globalPosition.x+20, globalPosition.y, globalPosition.z);
            //draw y green
            glColor3f(0,1,0);
            glVertex3f(globalPosition.x, globalPosition.y, globalPosition.z);
            glVertex3f(globalPosition.x, globalPosition.y+20, globalPosition.z);
            //draw z blue
            glColor3f(0,0,1);
            glVertex3f(globalPosition.x, globalPosition.y, globalPosition.z);
            glVertex3f(globalPosition.x, globalPosition.y, globalPosition.z+20);
            glEnd();
            //reset to state before function
            glPopMatrix();
        }
};

//class for camera
class CameraController{

};