#pragma once
#include "DrawComponent.h"
#include "Util.h"

//Inherits interface from component class defined in composite.h
//idea is basically that multiple of these objects inheriting an interface can exist and all can be drawn by an object owning them
//I only implemented box but this could be exampled to be sphere, pyramid, really anything
class Box : public DrawInterface {
public:
    Box(GLdouble frontTopLeftX, GLdouble frontTopLeftY, GLdouble frontTopLeftZ, GLdouble width, GLdouble height, GLdouble length, Vector3 pivot = Vector3(0,0,0));
    //draws the box object with reference to parent position, can draw in different modes, can be gray scaled as well
    void draw(char mode) const override;
    //sets angle offset of box object in specified dimension
    void setAngle(GLdouble angle, char dimension) override;
    //gets angle offset of box object in specified dimension
    GLdouble getAngle(char dimension) override;

private:
    //how long it is across x axis in the positive direction
    GLdouble m_width;
    //how long it is across y axis in the positive direction
    GLdouble m_height;
    //how long it is across z axis in the positive direction
    GLdouble m_length;
    //used to define a pivot point which box rotates around
    Vector3 m_pivot;

};