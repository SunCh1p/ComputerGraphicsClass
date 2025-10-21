#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <GL/glut.h>
#include "Util.h"

/*Using Composite Design pattern as inspiration but it doesn't strictly adhere,
    In the composite design pattern there is an abstract component which declares a common interface,
    a composite which also has a common interface, and a leaf node which has a common interface as well but no children.
*/
//interface in which all body parts will use
class DrawInterface {
public:
    DrawInterface(Vector3 position = Vector3(0, 0, 0), Vector3 color = Vector3(0, 1, 0), Vector3 rotation = Vector3(0, 0, 0)) : m_position(position), m_color(color), m_rotation(rotation) {}
    //must be overwritten, how an object that inherits draw interface draws itself
    virtual void draw(char mode) const = 0;
    //optional to override
    virtual void setColor(Vector3 color) { m_color = color; }
    //optional overrides for setting and getting angle in each dimension
    virtual void setAngle(GLdouble angle, char dimension) {}
    virtual GLdouble getAngle(char dimension) { return 0.0; }
protected:
    //coordinates relative to parent where parent is (0,0,0)
    Vector3 m_position;
    Vector3 m_color;
    Vector3 m_rotation;
};