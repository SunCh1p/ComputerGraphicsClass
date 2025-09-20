#include "Scene.h"

Scene::Scene() {
	//initialize default values
	m_drawMode = 'w';
	m_drawAxis = true;
	m_grayScale = false;
	m_musicToggle = false;
	m_dance = false;
	m_angle = 0.0;
	m_rotateClockwise = true;
	m_windMillChecker = 0;
	m_axe = Axes(Vector3(0, 0, 0));
	m_robot = HumanoidRobot(Vector3(0, 0, 0));
}

void Scene::initScene() {
    //initialize the music
    m_audioController.registerSound(Audio::DANCEMUSIC, L"PartyDance.wav");
    m_audioController.registerSound(Audio::SPEAKSOUND, L"EvilRobotSpeech.wav");
    //set the camera position
    m_camera.setPosition(Vector3(0, 5, 20));
    m_camera.setTarget(Vector3(0, 5, 0));
    m_camera.changePerspective('p');
    //give robot a head
    auto tmpPtr = std::make_unique<Box>(1, 7, 1, 1, 1, 1);
    m_robot.addChild(BodyPart::Head, std::move(tmpPtr));
    //set the color of head to yellow
    m_robot.colorBodyPart(BodyPart::Head, 3);

    //give robot a torso
    tmpPtr = std::make_unique<Box>(0, 6, 1, 3, 3, 1);
    m_robot.addChild(BodyPart::Torso, std::move(tmpPtr));
    //set color of torso to red
    m_robot.colorBodyPart(BodyPart::Torso, 0);

    //give robot a left arm
    tmpPtr = std::make_unique<Box>(-1, 6, 1, 1, 3, 1);
    m_robot.addChild(BodyPart::LeftArm, std::move(tmpPtr));
    //set left arm color to yellow
    m_robot.colorBodyPart(BodyPart::LeftArm, 3);

    //give robot a right arm
    tmpPtr = std::make_unique<Box>(3, 6, 1, 1, 3, 1);
    m_robot.addChild(BodyPart::RightArm, std::move(tmpPtr));
    //set right arm color to yellow
    m_robot.colorBodyPart(BodyPart::RightArm, 3);

    //give robot a left leg
    tmpPtr = std::make_unique<Box>(0, 3, 1, 1, 3, 1);
    m_robot.addChild(BodyPart::LeftLeg, std::move(tmpPtr));
    //set color of left leg to blue
    m_robot.colorBodyPart(BodyPart::LeftLeg, 2);

    //give robot a right leg
    tmpPtr = std::make_unique<Box>(2, 3, 1, 1, 3, 1);
    m_robot.addChild(BodyPart::RightLeg, std::move(tmpPtr));
    //set color of right leg to blue
    m_robot.colorBodyPart(BodyPart::RightLeg, 2);
}

void Scene::drawScene() {
    //clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //reset transformations
    glLoadIdentity();
    //set the camera if needed
    m_camera.setCamera();
    //draw axis if enabled
    if (m_drawAxis) {
        m_axe.draw(m_grayScale);
    }
    //draw robot
    m_robot.draw(m_drawMode, m_grayScale);
    //swap buffers
    glutSwapBuffers();
}

void Scene::processKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'p':
            m_drawMode = 'p';
            break;
        case 'w':
            m_drawMode = 'w';
            break;
        case 's':
            m_drawMode = 's';
            break;
        case 'c':
            m_drawMode = 'c';
            m_drawAxis = false;
            break;
        case 'a':
            m_drawAxis = !m_drawAxis;
            break;
        case 'm':
            //toggle music
            m_musicToggle = !m_musicToggle;
            //if music_toggle is true, play the dance music
            if (m_musicToggle) { m_audioController.playSoundInLoop(Audio::DANCEMUSIC); }
            //otherwise cancel sounds
            else { m_audioController.cancelSounds(); }
            break;
        case 'd':
            //toggle dancing mode
            m_dance = !m_dance;
            break;
        case 't':
            //Robot gives an evil speech
            m_audioController.playSound(Audio::SPEAKSOUND);
            break;
        case 27:
            exit(0);
            break;
    }
}

void Scene::processMouse(int button, int state, int x, int y) {
    //detect left button for changing to black and white mode
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            m_grayScale = !m_grayScale;
        }
    }
    //roll mouse wheel forward
    else if (button == 3) {
        if (state == GLUT_DOWN) {
            //1 indicates zoom camera in
            int moveTowardTarget = 1;
            m_camera.zoomCamera(moveTowardTarget);
        }
    }
    //roll mouse wheel backwards
    else if (button == 4) {
        if (state == GLUT_DOWN) {
            //-1 indicates zoom camera out
            int moveAwayFromTarget = -1;
            m_camera.zoomCamera(moveAwayFromTarget);
        }
    }
}

void Scene::orbitAroundX(int option) {
    m_camera.rotateAroundXAxis(30 * (option + 1));
    m_camera.setCamera();
}
void Scene::orbitAroundY(int option) {
    m_camera.rotateAroundYAxis(30 * (option + 1));
    m_camera.setCamera();
}
void Scene::orbitAroundZ(int option) {
    m_camera.rotateAroundZAxis(30 * (option + 1));
    m_camera.setCamera();
}

void Scene::changePerspectiveType(int option) {
    if (option == 0) {
        m_camera.changePerspective('o');
    }
    else {
        m_camera.changePerspective('p');
    }
}

void Scene::rotateAroundX(int option) {
    m_robot.setAngle(30 * (option + 1), 'x');
}
void Scene::rotateAroundY(int option) {
    m_robot.setAngle(30 * (option + 1), 'y');
}
void Scene::rotateAroundZ(int option) {
    m_robot.setAngle(30 * (option + 1), 'z');
}

void Scene::headColorChange(int option) {
    m_robot.colorBodyPart(BodyPart::Head, option);
}

void Scene::torsoColorChange(int option) {
    m_robot.colorBodyPart(BodyPart::Torso, option);
}
void Scene::leftLegColorChange(int option) {
    m_robot.colorBodyPart(BodyPart::LeftLeg, option);
}
void Scene::leftArmColorChange(int option) {
    m_robot.colorBodyPart(BodyPart::LeftArm, option);
}

void Scene::rightLegColorChange(int option) {
    m_robot.colorBodyPart(BodyPart::RightLeg, option);
}
void Scene::rightArmColorChange(int option) {
    m_robot.colorBodyPart(BodyPart::RightArm, option);
}
