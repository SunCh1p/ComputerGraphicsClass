#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#define WIN_X 100
#define WIN_Y 100
#define WIN_H 720
#define WIN_W 1280

void DrawAxes(){
    glBegin(GL_LINES);
        glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(10,0,0);
        glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,10,0);
        glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,10);
    glEnd();
}


//callback function for glutDisplayFunc
void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    // //set color to white
    // glColor3f(1.0, 1.0, 1.0);
    // //draw square which is all white
    // glBegin(GL_POLYGON);
    //     //draw vertice 0
    //     glVertex3f(-0.25, 0.25, 0);
    //     //draw vertice 1
    //     glVertex3f(0.25, 0.25, 0);
    //     //draw vertice 2
    //     glVertex3f(0.25, -0.25, 0);
    //     //draw vertice 3
    //     glVertex3f(-0.25, -0.25, 0);
    // glEnd();
    DrawAxes();
    //end drawing
    glFlush();
}

void init(void){
    /*select clearing background color*/
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-WIN_W/2, WIN_W/2, -WIN_H/2, WIN_H/2, -100, 100);
}


int main(int argc, char** argv){
    //initialize glut
    glutInit(&argc, argv);
    //set display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //set window position
    glutInitWindowPosition(WIN_X, WIN_Y);
    //set window size
    glutInitWindowSize(WIN_W, WIN_H);
    //create the window
    glutCreateWindow("Assignment 1 - Connor Blaha");
    //initialize opengl state
    init();
    //register callbacks
    glutDisplayFunc(myDisplay); //register display callback
    glutMainLoop(); //enter event loop
    return 0;
}