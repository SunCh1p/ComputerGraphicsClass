#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
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
/***FUNCTIONS ASSOCIATED WITH MENU FUNCTIONALITY */
/*functions for handling camera orbit around object*/
void orbitAroundX(int option){
    GLdouble angle = 30;
    for(int i = 0; i < option+1; i++, angle+=30){
        if(i == option){
            camera.rotateAroundXAxis(angle);
        }
    }
    camera.setCamera();
}
void orbitAroundY(int option){
    GLdouble angle = 30;
    for(int i = 0; i < option+1; i++, angle+=30){
        if(i == option){
            camera.rotateAroundYAxis(angle);
        }
    }
    camera.setCamera();
}
void orbitAroundZ(int option){
    GLdouble angle = 30;
    for(int i = 0; i < option+1; i++, angle+=30){
        if(i == option){
            camera.rotateAroundYAxis(angle);
        }
    }
    camera.setCamera();
}
/*functions for handling object rotation*/
void rotateAroundX(int option){
    GLdouble angle = 30;
    for(int i = 0; i < option+1; i++, angle+=30){
        if(i == option){
            robot.setAngle(angle,'x');
        }
    }
}
void rotateAroundY(int option){
    GLdouble angle = 30;
    for(int i = 0; i < option+1; i++, angle+=30){
        if(i == option){
            robot.setAngle(angle,'y');
        }
    }
}
void rotateAroundZ(int option){
    GLdouble angle = 30;
    for(int i = 0; i < option+1; i++, angle+=30){
        if(i == option){
            robot.setAngle(angle, 'z');
        }
    }
}
void processOrbitMenu(int option){
}

void processRotationMenu(int option){
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
    robot.colorBodyPart(BodyPart::Head, option);
}
void processTorsoColorChange(int option){
    robot.colorBodyPart(BodyPart::Torso, option);
}
void processLeftLegColorChange(int option){
    robot.colorBodyPart(BodyPart::LeftLeg, option);
}
void processLeftArmColorChange(int option){
    robot.colorBodyPart(BodyPart::LeftArm, option);
}
void processRightLegColorChange(int option){
    robot.colorBodyPart(BodyPart::RightLeg, option);
}
void processRightArmColorChange(int option){
    robot.colorBodyPart(BodyPart::RightArm, option);
}

void processMenuEvents(int option){
    std::cout << "Main menu" << std::endl;
}
void addDegEntries(){
    int optionSelection = 0;
    int angle = 30;
    for(optionSelection; optionSelection < 12; optionSelection++, angle+=30){
        glutAddMenuEntry((std::to_string(angle) + " deg").c_str(), optionSelection);
    }
}
void addColorEntry(){
    glutAddMenuEntry("Red", 0);
    glutAddMenuEntry("Green", 1);
    glutAddMenuEntry("Blue", 2);
}
void createGlutMenus(){
    int menu, orbitMenu, rotationMenu, projectionMenu, colorMenu;
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
    //add submenus for rotatingobject
    x = glutCreateMenu(rotateAroundX);
    addDegEntries();
    y = glutCreateMenu(rotateAroundY);
    addDegEntries();
    z = glutCreateMenu(rotateAroundZ);
    addDegEntries();
    //sub menu for rotating object
    rotationMenu = glutCreateMenu(processRotationMenu);
    glutAddSubMenu("RotateAroundX", x);
    glutAddSubMenu("RotateAroundY", y);
    glutAddSubMenu("RotateAroundZ", z);
    //create the menu and tell glut that processMenuEvents will handle the events
    menu = glutCreateMenu(processMenuEvents);
    //add entries to the menu
    //add entries to our menu
	glutAddSubMenu("Orbit Camera", orbitMenu);
    glutAddSubMenu("Rotate Humanoid", rotationMenu);
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
        glEnable(GL_DEPTH_TEST);
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

    /*enter glut event processing cycle*/
        //enter event loop
        glutMainLoop();

    return 0;
}