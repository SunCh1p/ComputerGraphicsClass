#pragma once
#include "composite.h"

//axes(a leaf class of component), inherits the interface, useful for hopefully creating a scene of components in the future
class Axes : public Component {
public:
    Axes(Vector3 position = Vector3(0, 0, 0)) : Component(position) {}
    //function responsible for drawing the axe
    void draw(bool grayScale = false, Vector3 parentPosition = Vector3(0, 0, 0), char mode = 'c') const;
};
