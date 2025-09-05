#include <GL/glut.h>
#define WIN_W 800
#define WIN_H 600

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glutWireTorus(0.5,3,15,30);
    //draw red x-axis, green y-axis, and a blue z-axis
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(10,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,10,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,10);
    glEnd();
    glFlush();
}

void procKeys(unsigned char key, int x, int y){
    switch(key){
        case 'p':
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-1.7,1.7,-1.7,1.7,5,100);
            glutPostRedisplay();
            break;
        case 'o':
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-7.0, 7.0, -7.0, 7.0, 5, 100);
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
    }
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //perspective projection
    glFrustum(-2.0, 2.0, -2.0, 2.0, 5, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //position camera at (0,0,20) looking at (0,0,0) with the vector <0,1,0>
    gluLookAt(0,0,20,0,0,0,0,1,0);
}

int main(int argc, char** argv){
    //initialize glut
    glutInit(&argc, argv);
    //set window size
    glutInitWindowSize(WIN_W, WIN_H);
    //create the window
    glutCreateWindow("A torus at different views");

    //register callbacks
    //register display callbacks
    glutDisplayFunc(mydisplay);
    glutKeyboardFunc(procKeys);

    init();

    glutMainLoop(); //enter event loop
    return 0;
}