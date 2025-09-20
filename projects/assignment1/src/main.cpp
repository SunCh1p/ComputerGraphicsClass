#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

//Our scene is made up of the following custom objects
#include "HumanoidRobot.h"
#include "Camera.h"
#include "Box.h"
#include "Axes.h"
#include "AudioController.h"

//all callbacks for our glut functions are stored in Callbacks.h
#include "Callbacks.h"

//Define the dimensions of the window to be drawn
#define WIN_X 100
#define WIN_Y 100
#define WIN_H 720
#define WIN_W 1280

//Variables and objects in the scene, modified in the various callbacks
char draw_mode = 's'; //draw_mode specifies what type of draw mode we will have

bool gray_scale = false; //gray_scale is false if we are in color mode, true if we are in black and white mode

bool draw_axis = true; //draw_axis is true if the user wants to view the axis

bool music_toggle = false; // used for toggling music

//variables associating with dance animation in animation callback
bool dance = false; //used for toggling dancing animation
GLdouble angle = 0.0; //angle for controlling rotation in dancing animation
bool rotate_clockwise = true; //used to set rotation angle for dancing
int windMillChecker = 0; //robot does the windmill if counter gets passed 200

//axe object
Axes axe(Vector3(0, 0, 0)); //axis to draw

//robot object
HumanoidRobot robot(Vector3(-1.5, 0, 0)); //robot to draw

//camera object
Camera camera; //camera to look at scene

//audio controller object for managing sound
AudioController audioController; //used for all sound related things



int main(int argc, char** argv) {
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
    glEnable(GL_DEPTH_TEST);
    //initialize scene
    initScene();
    //create the right click menu
    createGlutMenus();

    //register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutTimerFunc(10, animation, 0);
    glutKeyboardFunc(processKeys);
    glutMouseFunc(processMouse);

    //print instructions for the program
    printInstructions();

    //enter event loop
    glutMainLoop();

    return 0;
}