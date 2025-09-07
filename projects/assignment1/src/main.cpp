#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include "composite.h"
#define WIN_X 100
#define WIN_Y 100
#define WIN_H 720
#define WIN_W 1280

Scene global_scene(Vector3(0,0,0));

//callback function for glutDisplayFunc
void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    //draw the scene
    global_scene.draw();
    //garry.draw();
    glFlush();
}

void init(void){
    /*select clearing background color*/
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)WIN_W / WIN_H, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 2, 10.0,  // camera position
        0.0, 0.0, 0.0,   // look at origin
        0.0, 1.0, 0.0    // up vector
    );
}

void initScene(){
    //add axis to the scene
    global_scene.addChild(std::make_unique<Axes>());

    //Create a humanoid robot named garry
    auto garry = std::make_unique<HumanoidRobot>();
    //give garry a head
    garry->addChild(BodyPart::Head, std::make_unique<Cube>(1.0, Vector3(0, 2.5, 0)));
    //give garry a torso
    garry->addChild(BodyPart::Torso, std::make_unique<Cube>(2.0, Vector3(0, 1, 0)));
    
    //add garry to the scene
    global_scene.addChild(std::move(garry));
}

void procKeys(unsigned char key){
    switch(key){
        case 'p':
            //implementing displaying vertex mode
            break;
        case 'w':
            //implement displaying wireframe mode
            break;
        case 's':
            //implement displaying solid mode
            break;
        case 'c':
            //implement clearing screen and only showing background
            break;
        case 'a':
            //implement toggling axis display
            break;
        case 't':
            //implement speaking functionality
            break;
        case 27:
            exit(0);
            break;
    }
}

int main(int argc, char** argv){
    //initialize glut
    glutInit(&argc, argv);
    //set display mode
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB);
    //set window position
    glutInitWindowPosition(WIN_X, WIN_Y);
    //set window size
    glutInitWindowSize(WIN_W, WIN_H);
    //create the window
    glutCreateWindow("Assignment 1 - Connor Blaha");
    //Initialize depth checking
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    //initialize opengl state
    init();

    //initialize scene
    initScene();
    //register callbacks
    glutDisplayFunc(myDisplay); //register display callback
    glutMainLoop(); //enter event loop
    return 0;
}