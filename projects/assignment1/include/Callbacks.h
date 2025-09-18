#pragma once
#include <GL/glut.h>
#include "HumanoidRobot.h"
#include "Camera.h"
#include "Box.h"
#include "Axes.h"
#include "AudioController.h"
#include <iostream>


//Variables are defined in main.cpp but declared here so callbacks can use them.
extern char draw_mode;
extern bool gray_scale;
extern bool draw_axis;
extern bool music_toggle;
extern bool dance;
extern GLdouble angle;
extern bool rotate_clockwise;
extern int windMillChecker;
extern Axes axe;
extern HumanoidRobot robot;
extern Camera camera;
extern AudioController audioController;

//init scene initializes the music, sets the camera default settings, and builds the humanoid robot
void initScene();

//callback for glutDisplayFunc, it sets the camera, draws the robot and draws the axe
void renderScene();

//callback for glutMouseFunc, toggles grayscale is left mouse click, zooms camera in if scroll wheel moves forward, zooms out if scrolls wheel moves backward
void processMouse(int button, int state, int x, int y);

//callback for glutKeyboardFunc, sets draw mode to either vertex, wire, or solid, can clear screen, can toggle whether axe is drawn or not
//can toggle music, can toggle dance mode, can make robot give evil speech, and can exit program
void processKeys(unsigned char key, int x, int y);

//callback for glutReshapeFunc, reshapes screen if resized
void changeSize(int w, int h);

/*Menu functions*/
//auxiliary function to asist with building menu, adds clickable buttons for submenus relating to colors
void addColorEntry();
//auxliary function to assist with building menu, adds clickable buttons for submenus relating to degrees
void addDegEntries();
//auxliary function to assist with building menu, adds clickable button for orbiting the camera around the x axis
void orbitAroundX(int option);
//auxliary function to assist with building menu, adds clickable button for orbiting the camera around the y axis
void orbitAroundY(int option);
//auxliary function to assist with building menu, adds clickable button for orbiting the camera around the z axis
void orbitAroundZ(int option);
//auxliary function to assist with building menu, adds clickable button for rotating the robot around the x axis
void rotateAroundX(int option);
//auxliary function to assist with building menu, adds clickable button for rotating the robot around the y axis
void rotateAroundY(int option);
//auxliary function to assist with building menu, adds clickable button for rotating the robot around the z axis
void rotateAroundZ(int option);
//auxliary function to assist with building menu, adds clickable button for handling changing camera perspective to orthogonal or perspective mode
void processProjectionMenu(int option);
//auxliary function to assist with building menu, adds clickable button for changing color of head bodypart
void processHeadColorChange(int option);
//auxliary function to assist with building menu, adds clickable button for changing color of torso bodypart
void processTorsoColorChange(int option);
//auxliary function to assist with building menu, adds clickable button for changing color of left leg bodypart
void processLeftLegColorChange(int option);
//auxliary function to assist with building menu, adds clickable button for changing color of left arm bodypart
void processLeftArmColorChange(int option);
//auxliary function to assist with building menu, adds clickable button for changing color of right leg bodypart
void processRightLegColorChange(int option);
//auxliary function to assist with building menu, adds clickable button for changing color of right arm bodypart
void processRightArmColorChange(int option);
//function used to create menus
void createGlutMenus();

//callback for glutTimerFunc, function responsible for handling animation if dancing is toggled on
void animation(int value);

//outputs instructions to screen on how to operate the program
void printInstructions();


