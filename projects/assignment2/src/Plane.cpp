#include "Plane.h"

void Plane::draw(char mode) const{
	glPushMatrix();
		//set ground color to white
		glColor3d(1, 1, 1);
		glBegin(GL_QUADS);
			glVertex3f(-100.0f, 0.0f, -100.0f);
			glVertex3f(-100.0f, 0.0f, 100.0f);
			glVertex3f(100.0f, 0.0f, 100.0f);
			glVertex3f(100.0f, 0.0f, -100.0f);
		glEnd();
	glPopMatrix();
}