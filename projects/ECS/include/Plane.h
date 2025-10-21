#pragma once
#include "DrawComponent.h"

//axes(a leaf class of component), inherits the interface, useful for hopefully creating a scene of components in the future
class Plane : public DrawInterface {
public:
    Plane(Vector3 position = Vector3(0, 0, 0)) : DrawInterface(position) {}
    //function responsible for drawing the axe
    void draw(char mode = 'c') const;
};
