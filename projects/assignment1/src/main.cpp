#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "composite.h"
#define WIN_X 100
#define WIN_Y 100
#define WIN_H 720
#define WIN_W 1280
//Variables in the scene
char draw_mode = 'w'; //default to wireframe mode
bool draw_axis = true; //default to draw axis being true
Axes axe(Vector3(0,0,0)); //axis to draw
HumanoidRobot robot(Vector3(0,0,0)); //robot to draw
Camera camera; //camera to look at scene

//callback function for glutDisplayFunc
void renderScene(){
    //clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //reset transformations
    glLoadIdentity();
    //set the camera
    camera.setCamera();
    //draw axis if enabled
    if(draw_axis){
        axe.draw();
    }
    //draw robot
    robot.draw(draw_mode);
    //swap buffers
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
            draw_mode = 'p';
            break;
        case 'w':
            draw_mode = 'w';
            break;
        case 's':
            draw_mode = 's';
            break;
        case 'c':
            //implement clearing screen and only showing background
            draw_mode = 'c';
            draw_axis = false;
            break;
        case 'a':
            draw_axis = !draw_axis;
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

void initScene(){
    //set the camera position
    camera.setPosition(Vector3(1.5,5,30));
    camera.setTarget(Vector3(0,0,0));
    //give robot a head
    auto tmpPtr = std::make_unique<Box>(1,7,1,1,1,1);
    robot.addChild(BodyPart::Head, std::move(tmpPtr));
    //give robot a torso
    tmpPtr = std::make_unique<Box>(0,6,1,3,3,1);
    robot.addChild(BodyPart::Torso, std::move(tmpPtr));
    //give robot a left arm
    tmpPtr = std::make_unique<Box>(-1,6,1,1,3,1);
    robot.addChild(BodyPart::LeftArm, std::move(tmpPtr));
    //give robot a right arm
    tmpPtr = std::make_unique<Box>(3,6,1,1,3,1);
    robot.addChild(BodyPart::RightArm, std::move(tmpPtr));
    //give robot a left leg
    tmpPtr = std::make_unique<Box>(0,3,1,1,3,1);
    robot.addChild(BodyPart::LeftLeg, std::move(tmpPtr));
    // //give robot a right leg
    tmpPtr = std::make_unique<Box>(2,3,1,1,3,1);
    robot.addChild(BodyPart::RightLeg, std::move(tmpPtr));
}

void orbitAroundX(int option){
    switch(option){
        case 0:
            camera.rotateAroundXAxis(30.0);
            break;
        case 1:
            camera.rotateAroundXAxis(60.0);
            break;
        case 2:
            camera.rotateAroundXAxis(90.0);
            break;
        case 3:
            camera.rotateAroundXAxis(120.0);
            break;
        case 4:
            camera.rotateAroundXAxis(150.0);
            break;
        case 5:
            camera.rotateAroundXAxis(180.0);
            break;
        case 6:
            camera.rotateAroundXAxis(210.0);
            break;
        case 7:
            camera.rotateAroundXAxis(240.0);
            break;
        case 8:
            camera.rotateAroundXAxis(270.0);
            break;
        case 9:
            camera.rotateAroundXAxis(300.0);
            break;
        case 10:
            camera.rotateAroundXAxis(330.0);
            break;
        case 11:
            camera.rotateAroundXAxis(360.0);
            break;
    }
    camera.setCamera();

}
void orbitAroundY(int option){
    switch(option){
        case 0:
            camera.rotateAroundYAxis(30.0);
            break;
        case 1:
            camera.rotateAroundYAxis(60.0);
            break;
        case 2:
            camera.rotateAroundYAxis(90.0);
            break;
        case 3:
            camera.rotateAroundYAxis(120.0);
            break;
        case 4:
            camera.rotateAroundYAxis(150.0);
            break;
        case 5:
            camera.rotateAroundYAxis(180.0);
            break;
        case 6:
            camera.rotateAroundYAxis(210.0);
            break;
        case 7:
            camera.rotateAroundYAxis(240.0);
            break;
        case 8:
            camera.rotateAroundYAxis(270.0);
            break;
        case 9:
            camera.rotateAroundYAxis(300.0);
            break;
        case 10:
            camera.rotateAroundYAxis(330.0);
            break;
        case 11:
            camera.rotateAroundYAxis(360.0);
            break;
    }
    camera.setCamera();
}
void orbitAroundZ(int option){
    switch(option){
        case 0:
            camera.rotateAroundZAxis(30.0);
            break;
        case 1:
            camera.rotateAroundZAxis(60.0);
            break;
        case 2:
            camera.rotateAroundZAxis(90.0);
            break;
        case 3:
            camera.rotateAroundZAxis(120.0);
            break;
        case 4:
            camera.rotateAroundZAxis(150.0);
            break;
        case 5:
            camera.rotateAroundZAxis(180.0);
            break;
        case 6:
            camera.rotateAroundZAxis(210.0);
            break;
        case 7:
            camera.rotateAroundZAxis(240.0);
            break;
        case 8:
            camera.rotateAroundZAxis(270.0);
            break;
        case 9:
            camera.rotateAroundZAxis(300.0);
            break;
        case 10:
            camera.rotateAroundZAxis(330.0);
            break;
        case 11:
            camera.rotateAroundZAxis(360.0);
            break;
    }
    camera.setCamera();
}
void processOrbitMenu(int option){

}
void processProjectionMenu(int option){
    if(option == 0){
        std::cout << "orthographic projection" << std::endl;
    } else {
        std::cout << "perspection projection" << std::endl;
    }
}
void processPartToColor(int option){

}
void processHeadColorChange(int option){

}
void processTorsoColorChange(int option){

}
void processLeftLegColorChange(int option){

}
void processLeftArmColorChange(int option){

}
void processRightLegColorChange(int option){

}
void processRightArmColorChange(int option){

}
void processMenuEvents(int option){
    std::cout << "Main menu" << std::endl;
}
void addDegEntries(){
    glutAddMenuEntry("30 deg", 0);
    glutAddMenuEntry("60 deg", 1);
    glutAddMenuEntry("90 deg", 2);
    glutAddMenuEntry("120 deg", 3);
    glutAddMenuEntry("150 deg", 4);
    glutAddMenuEntry("180 deg", 5);
    glutAddMenuEntry("210 deg", 6);
    glutAddMenuEntry("240 deg", 7);
    glutAddMenuEntry("270 deg", 8);
    glutAddMenuEntry("300 deg", 9);
    glutAddMenuEntry("330 deg", 10);
    glutAddMenuEntry("360 deg", 11);
}
void addColorEntry(){
    glutAddMenuEntry("Red", 0);
    glutAddMenuEntry("Green", 1);
    glutAddMenuEntry("Blue", 2);
}
void createGlutMenus(){
    int menu, orbitMenu, projectionMenu, colorMenu;
    int x, y, z;
    int head, torso, leftLeg, leftArm, rightLeg, rightArm;
    //create sub menu for x orbiting
    x = glutCreateMenu(orbitAroundX);
    addDegEntries();
    //create sub menu for y orbiting
    y = glutCreateMenu(orbitAroundY);
    addDegEntries();
    //create sub menu for z orbiting
    z = glutCreateMenu(orbitAroundZ);
    addDegEntries();
    //submenu for orbit
    orbitMenu = glutCreateMenu(processOrbitMenu);
    glutAddSubMenu("orbit about x", x);
    glutAddSubMenu("orbit about y", y);
    glutAddSubMenu("orbit about z", z);
    //submenu for projection
    projectionMenu = glutCreateMenu(processProjectionMenu);
    glutAddMenuEntry("Orthographic Projection", 0);
    glutAddMenuEntry("Perspective Projection", 1);
    //sub menus for coloring body parts
    head = glutCreateMenu(processHeadColorChange);
    addColorEntry();
    torso = glutCreateMenu(processTorsoColorChange);
    addColorEntry();
    leftArm = glutCreateMenu(processLeftArmColorChange);
    addColorEntry();
    rightArm = glutCreateMenu(processRightArmColorChange);
    addColorEntry();
    leftLeg = glutCreateMenu(processLeftLegColorChange);
    addColorEntry();
    rightLeg = glutCreateMenu(processRightLegColorChange);
    addColorEntry();
    //sub menu for selecting bodypart to color
    colorMenu = glutCreateMenu(processPartToColor);
    glutAddSubMenu("Head", head);
    glutAddSubMenu("Torso", torso);
    glutAddSubMenu("LeftArm", leftArm);
    glutAddSubMenu("RightArm", rightArm);
    glutAddSubMenu("LeftLeg", leftLeg);
    glutAddSubMenu("RightLeg", rightLeg);
    //create the menu and tell glut that processMenuEvents will handle the events
    menu = glutCreateMenu(processMenuEvents);
    //add entries to the menu
    //add entries to our menu
	glutAddSubMenu("Orbit Camera", orbitMenu);
	glutAddSubMenu("Change Projection View", projectionMenu);
	glutAddSubMenu("Change Color of Body Part", colorMenu);
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
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
        //initialize scene
        initScene();
        //create the right click menu
        createGlutMenus();

    /*register callbacks*/
        glutDisplayFunc(renderScene);
        glutReshapeFunc(changeSize);
        //allows you to register a callback function when application is idle
        glutIdleFunc(renderScene);
        //allows you to process keyboard events
        glutKeyboardFunc(processKeys);

    // std::cout << "Instruction: Enter a key" << std::endl;
    // std::cout << "p: enter vertex mode" << std::endl;
    // std::cout << "w: enter wireframe mode" << std::endl;
    // std::cout << "s: enter solid mode" << std::endl;
    // std::cout << "c: clear screen" << std::endl;
    // std::cout << "a: toggle axis" << std::endl;
    // std::cout << "t: make the robot speak" << std::endl; 

    /*enter glut event processing cycle*/
        //enter event loop
        glutMainLoop();

    return 0;
}