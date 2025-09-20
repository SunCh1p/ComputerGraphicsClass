#include "Callbacks.h"

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
    glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 50);
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void processKeys(unsigned char key, int x, int y) {
    switch (key) {
    case 'p':
        //toggle point mode
        draw_mode = 'p';
        break;
    case 'w':
        //toggle wireframe mode
        draw_mode = 'w';
        break;
    case 's':
        //toggle solid mode
        draw_mode = 's';
        break;
    case 'c':
        //implement clearing screen and only showing background
        draw_mode = 'c';
        draw_axis = false;
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
        dance = !dance;
        break;
    case 't':
        //Robot gives an evil speech
        audioController.playSound(Audio::SPEAKSOUND);
        break;
    case 27:
        exit(0);
        break;
    }
}

void initScene() {
    //initialize the music
    audioController.registerSound(Audio::DANCEMUSIC, L"dance1.wav");
    //obtained evil ai speech by entering text into this website
    //https://speechify.com/ai-voice-generator/
    audioController.registerSound(Audio::SPEAKSOUND, L"EvilRobotSpeech.wav");
    //set the camera position
    camera.setPosition(Vector3(0, 5, 20));
    camera.setTarget(Vector3(0, 5, 0));
    camera.changePerspective('p');
    //give robot a head
    auto tmpPtr = std::make_unique<Box>(1, 7, 1, 1, 1, 1);
    robot.addChild(BodyPart::Head, std::move(tmpPtr));
    //set the color of head to yellow
    robot.colorBodyPart(BodyPart::Head, 3);

    //give robot a torso
    tmpPtr = std::make_unique<Box>(0, 6, 1, 3, 3, 1);
    robot.addChild(BodyPart::Torso, std::move(tmpPtr));
    //set color of torso to red
    robot.colorBodyPart(BodyPart::Torso, 0);

    //give robot a left arm
    tmpPtr = std::make_unique<Box>(-1, 6, 1, 1, 3, 1);
    robot.addChild(BodyPart::LeftArm, std::move(tmpPtr));
    //set left arm color to yellow
    robot.colorBodyPart(BodyPart::LeftArm, 3);

    //give robot a right arm
    tmpPtr = std::make_unique<Box>(3, 6, 1, 1, 3, 1);
    robot.addChild(BodyPart::RightArm, std::move(tmpPtr));
    //set right arm color to yellow
    robot.colorBodyPart(BodyPart::RightArm, 3);

    //give robot a left leg
    tmpPtr = std::make_unique<Box>(0, 3, 1, 1, 3, 1);
    robot.addChild(BodyPart::LeftLeg, std::move(tmpPtr));
    //set color of left leg to blue
    robot.colorBodyPart(BodyPart::LeftLeg, 2);

    //give robot a right leg
    tmpPtr = std::make_unique<Box>(2, 3, 1, 1, 3, 1);
    robot.addChild(BodyPart::RightLeg, std::move(tmpPtr));
    //set color of right leg to blue
    robot.colorBodyPart(BodyPart::RightLeg, 2);
}


void orbitAroundX(int option) {
    //angle is equal to 30 * option+1
    //basically 30*1 = 30, 30*2 = 60, and so on.. until we get the full 360 degrees.
    //all orbit and rotate functions take advantage of this
    camera.rotateAroundXAxis(30 * (option + 1));
    camera.setCamera();
}
void orbitAroundY(int option) {
    camera.rotateAroundYAxis(30 * (option + 1));
    camera.setCamera();
}
void orbitAroundZ(int option) {
    camera.rotateAroundZAxis(30 * (option + 1));
    camera.setCamera();
}
void rotateAroundX(int option) {
    robot.setAngle(30 * (option + 1), 'x');
}
void rotateAroundY(int option) {
    robot.setAngle(30 * (option + 1), 'y');
}
void rotateAroundZ(int option) {
    robot.setAngle(30 * (option + 1), 'z');
}

void processProjectionMenu(int option) {
    if (option == 0) {
        //option 0 sets to orthographic mode which is set in the camera class
        camera.changePerspective('o');
    }
    else {
        //any other option sets to perspective mode which is set in the camera class
        camera.changePerspective('p');
    }
}

void processHeadColorChange(int option) {
    //all bodypart color change functions call a function in humanoid robot object to change specific body part
    robot.colorBodyPart(BodyPart::Head, option);
}
void processTorsoColorChange(int option) {
    robot.colorBodyPart(BodyPart::Torso, option);
}
void processLeftLegColorChange(int option) {
    robot.colorBodyPart(BodyPart::LeftLeg, option);
}
void processLeftArmColorChange(int option) {
    robot.colorBodyPart(BodyPart::LeftArm, option);
}
void processRightLegColorChange(int option) {
    robot.colorBodyPart(BodyPart::RightLeg, option);
}
void processRightArmColorChange(int option) {
    robot.colorBodyPart(BodyPart::RightArm, option);
}

void addDegEntries() {
    //function adds menu options from 30, 60, 90, to 360 degrees for menu
    int optionSelection = 0;
    int angle = 30;
    for (optionSelection; optionSelection < 12; optionSelection++, angle += 30) {
        glutAddMenuEntry((std::to_string(angle) + " deg").c_str(), optionSelection);
    }
}
void addColorEntry() {
    glutAddMenuEntry("Red", 0);
    glutAddMenuEntry("Green", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Yellow", 3);
}
void createGlutMenus() {
    int menu, orbitMenu, rotationMenu, projectionMenu, colorMenu;
    int x, y, z;
    int head, torso, leftLeg, leftArm, rightLeg, rightArm;
    auto blankFunction = [](int menu) {};
    //create sub menu for x orbiting
    x = glutCreateMenu(orbitAroundX);
    addDegEntries();
    //create sub menu for y orbiting
    y = glutCreateMenu(orbitAroundY);
    addDegEntries();
    //create sub menu for z orbiting
    z = glutCreateMenu(orbitAroundZ);
    addDegEntries();
    //submenu for orbit, does not have any events that it needs to process, so blank lambda function is passed
    orbitMenu = glutCreateMenu(blankFunction);
    glutAddSubMenu("orbit about x", x); glutAddSubMenu("orbit about y", y); glutAddSubMenu("orbit about z", z);
    //submenu for projection
    projectionMenu = glutCreateMenu(processProjectionMenu);
    glutAddMenuEntry("Orthographic Projection", 0); glutAddMenuEntry("Perspective Projection", 1);
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
    colorMenu = glutCreateMenu(blankFunction);
    glutAddSubMenu("Head", head); glutAddSubMenu("Torso", torso); glutAddSubMenu("LeftArm", leftArm);
    glutAddSubMenu("RightArm", rightArm); glutAddSubMenu("LeftLeg", leftLeg); glutAddSubMenu("RightLeg", rightLeg);
    //add submenus for rotatingobject
    x = glutCreateMenu(rotateAroundX);
    addDegEntries();
    y = glutCreateMenu(rotateAroundY);
    addDegEntries();
    z = glutCreateMenu(rotateAroundZ);
    addDegEntries();
    //sub menu for rotating object
    rotationMenu = glutCreateMenu(blankFunction);
    glutAddSubMenu("RotateAroundX", x); glutAddSubMenu("RotateAroundY", y); glutAddSubMenu("RotateAroundZ", z);
    //create the menu and tell glut that processMenuEvents will handle the events
    menu = glutCreateMenu(blankFunction);
    //add entries to the menu
    //add entries to our menu
    glutAddSubMenu("Orbit Camera", orbitMenu); glutAddSubMenu("Rotate Humanoid", rotationMenu); glutAddSubMenu("Change Projection View", projectionMenu); glutAddSubMenu("Change Color of Body Part", colorMenu);
    // attach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMouse(int button, int state, int x, int y) {
    //detect left button for changing to black and white mode
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            gray_scale = !gray_scale;
        }
    }
    //handle scroll wheel input
    //scroll forward
    else if (button == 3) {
        if (state == GLUT_DOWN) {
            //1 indicates zoom camera in
            int moveTowardTarget = 1;
            camera.zoomCamera(moveTowardTarget);
        }
    }
    //scrollbackward
    else if (button == 4) {
        if (state == GLUT_DOWN) {
            //-1 indicates zoom camera out
            int moveAwayFromTarget = -1;
            camera.zoomCamera(moveAwayFromTarget);
        }
    }
}

//callback function for glutDisplayFunc
void renderScene() {
    //clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //reset transformations
    glLoadIdentity();
    //set the camera if needed
    camera.setCamera();
    //draw axis if enabled
    if (draw_axis) {
        axe.draw(gray_scale);
    }
    //draw robot
    robot.draw(draw_mode, gray_scale);
    //swap buffers
    glutSwapBuffers();
}

void animation(int value) {
    if (dance) {
        if (!rotate_clockwise) {
            angle += 1;
            if (angle >= 45) {
                rotate_clockwise = !rotate_clockwise;
            }
        }
        else {
            angle -= 1;
            if (angle <= -45) {
                rotate_clockwise = !rotate_clockwise;
            }
        }
        //robot turns side to side
        robot.setAngle(angle - robot.getAngle('y'), 'y');
        //get right arm bodypart angle when 
        GLdouble leftArmXAngle = robot.getAngleBodyPart(BodyPart::LeftArm, 'x');
        //get left arm bodypart angle
        GLdouble rightArmXAngle = robot.getAngleBodyPart(BodyPart::RightArm, 'x');
        if (windMillChecker >= 180) {
            //robot goes crazy and does the windmill because the music is too good
            robot.rotateBodyPart(BodyPart::LeftArm, 'x', angle / 2);
            robot.rotateBodyPart(BodyPart::RightArm, 'x', -angle / 2);
        }
        else {
            //robot doesn't have enough energy to do the windmill, so he chillaxes until he can go crazy again
            robot.rotateBodyPart(BodyPart::LeftArm, 'x', -angle / 2 - leftArmXAngle - 90);
            robot.rotateBodyPart(BodyPart::RightArm, 'x', angle / 2 - rightArmXAngle - 90);
        }
        //increment windmill checker
        windMillChecker = (windMillChecker + 1) % 360;
        //till head sidie

    }
    else {
        //reset all animations
        if (robot.getAngle('y') != 0.0) {
            //reset robot angle
            robot.setAngle(-robot.getAngle('y'), 'y');
            rotate_clockwise = true;
            angle = 0.0;
            //reset body part angles
            GLdouble leftArmXAngle = robot.getAngleBodyPart(BodyPart::LeftArm, 'x');
            GLdouble rightArmXAngle = robot.getAngleBodyPart(BodyPart::RightArm, 'x');
            robot.rotateBodyPart(BodyPart::LeftArm, 'x', -leftArmXAngle);
            robot.rotateBodyPart(BodyPart::RightArm, 'x', -rightArmXAngle);
        }
    }
    glutPostRedisplay();
    //call again for the future
    glutTimerFunc(16, animation, 0);
}

void printInstructions() {
    std::cout << "Keyboard Instructions: " << std::endl;
    std::cout << "Press 'p' to draw robot in vertex mode" << std::endl;
    std::cout << "Press 'w' to draw robot in wireframe mode" << std::endl;
    std::cout << "Press 's' to draw robot in solid mode" << std::endl;
    std::cout << "Press 'c' to clear the screen of all drawings" << std::endl;
    std::cout << "Press 'a' to toggle drawing the axe" << std::endl;
    std::cout << "Press 'm' to toggle music" << std::endl;
    std::cout << "Press 'd' to toggle the robot dancing" << std::endl;
    std::cout << "Press 't' to make the robot give an evil speech" << std::endl;
    std::cout << "Press 'esc' to exit the program" << std::endl << std::endl;;

    std::cout << "Mouse Controls:" << std::endl;
    std::cout << "Left click to toggle black and white mode" << std::endl;
    std::cout << "scroll the scroll wheel forward to zoom in(only noticable in perspective mode)" << std::endl;
    std::cout << "scroll the scroll wheel backward to zoom out(only noticable in perspective mode)" << std::endl;
    std::cout << "right click to open menu" << std::endl;
}