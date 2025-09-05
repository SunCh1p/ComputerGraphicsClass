#include <GL/glut.h>
#include <GL/glut.h>
#define WIN_H 480
#define WIN_W 640
#define SIZE 100

//callback function for glutDisplayFunc
void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5);
    glEnd();
    glFlush();
}

void mymenu(int value){
    if(value == 1){
        //Do something
        glFlush();
    } else if(value == 2){
        exit(0);
    }
}


int main(int argc, char** argv){
    //initialize glut
    glutInit(&argc, argv);
    //set window position
    glutInitWindowPosition(100, 100);
    //set window size
    glutInitWindowSize(600, 400);
    //create the window
    glutCreateWindow("Simple menu");
    glutCreateMenu(mymenu);
    glutAddMenuEntry("Do something", 1);
    glutAddMenuEntry("Exit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    //register display callbacks
    glutDisplayFunc(myDisplay);
    glutMainLoop(); //enter event loop
    return 0;
}