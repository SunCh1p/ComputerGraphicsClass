#pragma once
#include <unordered_set>
#include <memory>
//Using Composite Design pattern
//abstract component
class Component{
    public:
        Component();
        virtual void draw() const = 0;
        virtual void drawVertex() const = 0;

    protected:
        //coordinates relative to parent where parent is (0,0,0)
        int m_xcoord, m_ycoord, m_zcoord;
        //scaling values
        int m_xscale, m_yscale, m_zscale;
        //rotation coordinates
        int m_xrot, m_yrot, m_zrot;   
};

//composite class
class HumanoidRobot : public Component{
    public:

    private:
        std::unique_ptr<Component> m_head;
        std::unique_ptr<Component> m_torso;
        std::unique_ptr<Component> m_leftLeg;
        std::unique_ptr<Component> m_rightLeg;
        std::unique_ptr<Component> m_leftArm;
        std::unique_ptr<Component> m_rightArm;
};

