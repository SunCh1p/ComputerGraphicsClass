#pragma once
#include <unordered_map>
#include <memory>
#include <GL/glut.h>

struct Vector3{
    float x, y, z;

    bool operator==(Vector3 other){
        return x==other.x&&y==other.y&&z==other.z;
    }

    bool operator!=(Vector3 other){
        return !(*this == other);
    }
};

//Using Composite Design pattern
//abstract component
class Component{
    public:
        Component(Vector3 position): m_position(position) {}
        virtual void draw(Vector3 parentPosition) const = 0;
        virtual void addChild(BodyPart part ,std::unique_ptr<Component> child) = 0;

    protected:
        //coordinates relative to parent where parent is (0,0,0)
        Vector3 m_position;
  
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

//composite class
class HumanoidRobot : public Component{
    public:
        void draw(Vector3 parentPosition = {0,0,0}) const override{
            for(auto& it: children){
                it.second->draw(m_position);
            }
        }

        void addChild(BodyPart part ,std::unique_ptr<Component> child) override{
            //move unique ptr into container
            children[part] = std::move(child);
        }

    private:
        //all children of humanoid robot
        std::unordered_map<BodyPart, std::unique_ptr<Component>> children;
};

//leaf classes
class Sphere : public Component{
    public:
        void draw(Vector3 parentPosition) const override {
            //Push a new matrix
            glPushMatrix();
            //Apply color
            glColor3d(1,0,0); //red for now until we get a single object working
            //Apply translation


            //Apply Rotation


            //rest to state before function
            glPopMatrix();
        }

    private:


};
