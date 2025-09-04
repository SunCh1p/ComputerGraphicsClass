#include <GL/glut.h>
#define WIN_X 50
#define WIN_Y 50
#define WIN_H 500
#define WIN_W 800

//callback function for glutDisplayFunc
void myDisplay(){
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    //draw triangle 
    glBegin(GL_POLYGON);
        //set color to red
        glColor3f(1, 0, 0);
        //draw vertice 1
        glVertex3f(-0.5, 0, 0);
        //set color to green
        glColor3f(0, 1, 0);
        //draw vertice
        glVertex3f(0, 0.5, 0);
        //set color to blue
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0.5);
    glEnd();
    glFlush();
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
    glutCreateWindow("DrawTriangle");
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}