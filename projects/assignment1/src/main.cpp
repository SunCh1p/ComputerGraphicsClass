#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "composite.h"
#define WIN_X 100
#define WIN_Y 100
#define WIN_H 720
#define WIN_W 1280

Scene global_scene(Vector3(0,0,0));

float angle = 0.0f;

//callback function for glutDisplayFunc
void renderScene(){
    //clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //reset transformations
    glLoadIdentity();
    //set the camera
    gluLookAt(	0.0f, 0.0f, 10.0f,
			0.0f, 0.0f,  0.0f,
			0.0f, 1.0f,  0.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
		glVertex3f(-2.0f,-2.0f, 0.0f);
		glVertex3f( 2.0f, 0.0f, 0.0);
		glVertex3f( 0.0f, 2.0f, 0.0);
	glEnd();

    angle+=0.1f;
    glutSwapBuffers();
}

/*function taken from http://www.lighthouse3d.com/tutorials/glut-tutorial/preparing-the-window-for-a-reshape/*/
void changeSize(int w, int h){
    // Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
    // Reset Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void processKeys(unsigned char key, int x, int y){
    switch(key){
        case 'p':
            //implementing displaying vertex mode
            std::cout << "Vertex Mode" << std::endl;
            break;
        case 'w':
            //implement displaying wireframe mode
            std::cout << "Wireframe mode" << std::endl;
            break;
        case 's':
            //implement displaying solid mode
            std::cout << "Solid Mode" << std::endl;
            break;
        case 'c':
            //implement clearing screen and only showing background
            std::cout << "Clearing screen" << std::endl;
            break;
        case 'a':
            //implement toggling axis display
            std::cout << "toggling axis" << std::endl;
            break;
        case 't':
            //implement speaking functionality
            std::cout << "Robot speaking" << std::endl;
            break;
        case 27:
            exit(0);
            break;
    }
}

int main(int argc, char** argv){
    /*Initialize glut and create window*/
        //initialize glut
        glutInit(&argc, argv);
        //set window position
        glutInitWindowPosition(WIN_X, WIN_Y);
        //set window size
        glutInitWindowSize(WIN_W, WIN_H);
        //set display mode
        glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
        //create the window
        glutCreateWindow("Assignment 1 - Connor Blaha | 811054403");

    /*register callbacks*/
        glutDisplayFunc(renderScene);
        glutReshapeFunc(changeSize);
        //allows you to register a callback function when application is idle
        glutIdleFunc(renderScene);
        //allows you to process keyboard events
        glutKeyboardFunc(processKeys);

    /*enter glut event processing cycle*/
        //enter event loop
        glutMainLoop();

    return 0;
}