#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

//Our scene is made up of the following custom objects
#include "HumanoidRobot.h"
#include "Camera.h"
#include "Box.h"
#include "Axes.h"
#include "AudioController.h"
#include "Plane.h"
#include "DanceManager.h"

//Define the dimensions of the window to be drawn
#define WIN_X 100
#define WIN_Y 100
#define WIN_H 720
#define WIN_W 1280

//Variables and objects in the scene, modified in the various callbacks
char draw_mode = 's'; //draw_mode specifies what type of draw mode we will have
bool clear_screen_toggle = false;
bool draw_axis = true; //draw_axis is true if the user wants to view the axis
bool music_toggle = false; // used for toggling music
bool switchFPVtoESV = false; //controlls whether first person view is enabled or not
bool rmv = false; //controlls whether rear mirror view is enabeld or not
bool esv = false; //controls whether entire scene view is enabled or not

//variables for controlling camera movement
float deltaAngle = 0.0f; //change in angle between x and z axis
float deltaMove = 0; //determines if camera moves forward or backwards


//variables associating with dance animation in animation callback
bool danceUnique = false; //used for toggling dancing animations for individual robots
bool danceSync = false; //used for toggling dancing animations for all robots in sync
bool resetDance = false; //used for checkign whether we need to reset dance or not

//Things within the scene
Axes axe(Vector3(0, 0, 0)); //axis to draw
std::vector<HumanoidRobot> robots; //list of robots
Camera camera; //camera to look at scene
AudioController audioController; //object for managing audio control
Plane plane; //plane object for drawing a plane in the scene
DanceManager danceManager; //object responsible for handling dance logic

/*function taken from http://www.lighthouse3d.com/tutorials/glut-tutorial/preparing-the-window-for-a-reshape/*/
void changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    float ratio = 1.0 * w / h;
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    // Reset Matrix
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void processKeys(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        //toggle wireframe mode
        draw_mode = 'w';
        break;
    case 's':
        //toggle solid mode
        draw_mode = 's';
        break;
    case 'c':
        //toggle clear screen
        clear_screen_toggle = !clear_screen_toggle;
        break;
    case 'a':
        //toggle whether to draw axe or not
        draw_axis = !draw_axis;
        break;
    case 'm':
        //toggle music
        music_toggle = !music_toggle;
        //if music_toggle is true, play the dance music
        if (music_toggle) { audioController.playSoundInLoop(Audio::DANCEMUSIC); }
        //otherwise cancel sounds
        else { audioController.cancelSounds(); }
        break;
    case 'd':
        //toggle dancing mode
        danceUnique = !danceUnique;
        if (danceUnique == true) {
            if (danceSync == true) {
                resetDance = true;
                danceSync = false;
            }
        }
        if (danceUnique==false && resetDance==false) {
            resetDance = true;
            danceSync = false;
        }
        break;
    case 'r':
        //toggle sync dancing mode
        danceSync = !danceSync;
        if (danceSync == true) {
            if (danceUnique == true) {
                resetDance = true;
                danceUnique = false;
            }
        }
        if (danceSync == false && resetDance == false) {
            resetDance = true;
            danceUnique = false;
        }
        break;
    case 'y':
        danceManager.setSyncDance(0);
        break;
    case 'u':
        danceManager.setSyncDance(1);
        break;
    case 'i':
        danceManager.setSyncDance(2);
        break;
    case 'o':
        danceManager.setSyncDance(3);
        break;
    case 'p':
        danceManager.setSyncDance(4);
        break;
    case 27:
        exit(0);
        break;
    }
}

void initScene() {
    //initialize the music
    audioController.registerSound(Audio::DANCEMUSIC, L"dance1.wav");
    //generate seed for rand()
    srand(static_cast<unsigned int>(time(nullptr)));
    //generate list of random positions in grid for robot to generate in
    int gridSize = 5;
    int numOfRobots = 5;
    std::vector<std::vector<bool>> grid(gridSize, std::vector<bool>(gridSize, false));
    int robotsGenerated = 0;
    while (robotsGenerated < numOfRobots) {
        int x = rand() % gridSize;
        int y = rand() % gridSize;
        if (!grid[x][y]) {
            grid[x][y] = true;
            robotsGenerated++;
        }
    }
    //Translate those positions to coordinates such that they generate around the scene without intersecting eachother
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            if (grid[row][col]) {
                //generate robot and give it limbs
                HumanoidRobot newRobot({ (row-2) * 7.0, 4.5, (col-2) * 7.0 });

                //push it into list of robots
                robots.push_back(std::move(newRobot));
            }
        }
    }
    //give each robot in the list of robots 4 limbs, torso, and a head
    for (auto& robot : robots) {
        //give robot a head
        auto tmpPtr = std::make_unique<Box>(-0.5, 2.5, 0.5, 1, 0.99, 1, Vector3(0.5, -1, -0.5));
        robot.addChild(BodyPart::Head, std::move(tmpPtr));
        robot.colorBodyPart(BodyPart::Head, 3);//set the color of head to yellow
        //give robot a torso
        tmpPtr = std::make_unique<Box>(-1.5, 1.5, 0.5, 2.99, 2.99, 0.99, Vector3(1.5, -1.5, -0.5));
        robot.addChild(BodyPart::Torso, std::move(tmpPtr));
        robot.colorBodyPart(BodyPart::Torso, 0);//set color of torso to red
        //give robot a left arm
        tmpPtr = std::make_unique<Box>(-2.5, 1.5, 0.5, 0.99, 2.99, 0.99, Vector3(0.5,-0.5,-0.5));
        robot.addChild(BodyPart::LeftArm, std::move(tmpPtr));
        robot.colorBodyPart(BodyPart::LeftArm, 3);//set left arm color to yellow
        //give robot a right arm
        tmpPtr = std::make_unique<Box>(1.5, 1.5, 0.5, 0.99, 2.99, 0.99, Vector3(0.5,-0.5,-0.5));
        robot.addChild(BodyPart::RightArm, std::move(tmpPtr));
        robot.colorBodyPart(BodyPart::RightArm, 3);//set right arm color to yellow
        //give robot a left leg
        tmpPtr = std::make_unique<Box>(-1.5, -1.5, 0.5, 0.99, 2.99, 0.99, Vector3(0.5, -0.5, -0.5));
        robot.addChild(BodyPart::LeftLeg, std::move(tmpPtr));
        robot.colorBodyPart(BodyPart::LeftLeg, 2);//set color of left leg to blue
        //give robot a right leg
        tmpPtr = std::make_unique<Box>(0.5, -1.5, 0.5, 0.99, 2.99, 0.99, Vector3(0.5, -0.5, -0.5));
        robot.addChild(BodyPart::RightLeg, std::move(tmpPtr));
        robot.colorBodyPart(BodyPart::RightLeg, 2);//set color of right leg to blue
    }
    //register robots with dance manager
    danceManager.registerRobots(robots);
    //set default dances
    danceManager.setDefaultDances();
    danceManager.setSyncDance(0);
}

//helper function to help reduce repeated code
void drawScene() {
    //draw the plane
    plane.draw();
    //draw the axis if enabled
    if (draw_axis) {
        axe.draw();
    }
    //draw robots
    for (auto& robot : robots) {
        robot.draw(draw_mode);
    }
    //draw camera cube
    camera.draw(draw_mode);
}

//callback function for glutDisplayFunc
void renderScene() {
    //handle movement
    if (deltaMove) {
        camera.computePos(deltaMove);
    }
    if (deltaAngle) {
        camera.computeDir(deltaAngle);
    }
    //clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (!clear_screen_toggle) {
        //set fpv/esv for main vamera viewport
        glViewport(0, 0, WIN_W, WIN_H); //specify how much of the screen this viewport will take up
        glMatrixMode(GL_PROJECTION); 
        glLoadIdentity();
        gluPerspective(45.0f, 1.0*WIN_W/WIN_H, 0.1f, 100.0f);//set aspect ratio using projection matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        if (switchFPVtoESV) {
            camera.setCameraESV(); //sets camera to entire scene view
        }
        else {
            camera.setCameraFPV(); // sets camera to first person view
        }
        //draw scene for main camera
        drawScene();
        //set up rear mirror view if its flag is enabled
        if (rmv) {
            int width = WIN_W / 2;
            int height = WIN_H / 2;
            glEnable(GL_SCISSOR_TEST); //used so that we can clear a buffer for only a specific part of the screen
            glScissor(0, WIN_H - height, width, height);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glViewport(0, WIN_H - height, width, height); //set viewport for top left quarter
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0f, 1.0 * WIN_W / WIN_H, 0.1f, 100.0f); //set aspect ratio
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            camera.setCameraRMV(); //set camera to rear viewport mode
            drawScene(); //draw the scene
            glDisable(GL_SCISSOR_TEST);
        }
        //set up entire scene view if it its flag is enabled
        if (esv) {
            int width = WIN_W / 2;
            int height = WIN_H / 2;
            glEnable(GL_SCISSOR_TEST);
            glScissor(0+width, WIN_H - height, width, height);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glViewport(0+width, WIN_H - height, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0f, 1.0 * WIN_W / WIN_H, 0.1f, 100.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            camera.setCameraESV();
            drawScene();
            glDisable(GL_SCISSOR_TEST);
        }
    }
    //swap buffers
    glutSwapBuffers();
}

void pressKey(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
        case GLUT_KEY_UP: deltaMove = 1.0f; break;
        case GLUT_KEY_DOWN: deltaMove = -1.0f; break;
        case GLUT_KEY_F1: rmv = !rmv; break;
        case GLUT_KEY_F2: esv = !esv; break;
        case GLUT_KEY_F3: switchFPVtoESV = !switchFPVtoESV; break;
    }
}

void releaseKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT: deltaAngle = 0.0f; break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN: deltaMove = 0; break;
    }
}

void animation(int value) {
    //reset robots position if needed
    if (resetDance) {
        danceManager.restoreDefault(); //restores default positions of all robots
        resetDance = false;
    }

    if (danceUnique) {
        danceManager.danceAllUnique();
    }
    else if (danceSync) {
        danceManager.danceAllSync();
    }
    glutPostRedisplay();
    ////call again for the future
    glutTimerFunc(16, animation, 0);
}

void printInstructions() {
    std::cout << "Keyboard Instructions: " << std::endl;
    std::cout << "Press 'F1' to toggle rear camera view on/off" << std::endl;
    std::cout << "Press 'F2' to toggle entire scene view camera on/off" << std::endl;
    std::cout << "Press 'F3' to switch between first person view and entire scene view" << std::endl;
    std::cout << "Press 'UP' to move camera forward" << std::endl;
    std::cout << "Press 'Down' to move camera backward" << std::endl;
    std::cout << "Press 'Left' to rotate camera to the left" << std::endl;
    std::cout << "Press 'right' to rotate camera to the right" << std::endl;
    std::cout << "Press 'w' to draw robot in wireframe mode" << std::endl;
    std::cout << "Press 's' to draw robot in solid mode" << std::endl;
    std::cout << "Press 'c' to clear the screen of all drawings" << std::endl;
    std::cout << "Press 'a' to toggle drawing the axe" << std::endl;
    std::cout << "Press 'm' to toggle music" << std::endl;
    std::cout << "Press 'd' to toggle the robot dancing" << std::endl;
    std::cout << "Press 'r' to make the robots dance in sync" << std::endl;
    std::cout << "Press 'esc' to exit the program" << std::endl << std::endl;

    std::cout << "Bonus Feature, easily swap between unison dances(only visible when robots dance in sync): " << std::endl;
    std::cout << "Press 'y' to make the unison dance: dance 1" << std::endl;
    std::cout << "Press 'u' to make the unison dance: dance 2" << std::endl;
    std::cout << "Press 'i' to make the unison dance: dance 3" << std::endl;
    std::cout << "Press 'o' to make the unison dance: dance 4" << std::endl;
    std::cout << "Press 'p' to make the unison dance: dance 5" << std::endl;
}

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

    //register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutTimerFunc(10, animation, 0);
    glutKeyboardFunc(processKeys);

    //handle movement callbacks
    glutSpecialFunc(pressKey);
    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(releaseKey);

    //print instructions for the program
    printInstructions();

    //enter event loop
    glutMainLoop();
    return 0;
}