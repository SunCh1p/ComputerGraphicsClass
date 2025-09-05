#include <GL/glut.h>
#define WIN_X 100
#define WIN_Y 100
#define WIN_H 500
#define WIN_W 500

// global variables
float gRed = 1.0;
float gGreen = 1.0;
float gBlue = 1.0;


//callback function for glutDisplayFunc
void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    //set color to white
    glColor3f(1.0, 1.0, 1.0);
    //draw square which is all white
    glBegin(GL_POLYGON);
        glColor3f(gRed, 0.0, 0.0);
        glVertex3f(0.25,0.25,0.0);
        glColor3f(0.0,gGreen,0.0);
        glVertex3f(0.75,0.25,0.0);
        glColor3f,(0.0,0.0,gBlue);
        glVertex3f(0.75,0.75,0.0);
        glColor3f(1.0,1.0,1.0);
        glVertex3f(0.25,0.75,0.0);
    glEnd();
    glFlush();
}

void init(void){
    /*select clearing background color*/
    glClearColor(0.0, 0.0, 0.0, 0.0);
    /*Initialize viewing values*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void procSpecialKeys(int key, int x, int y){
    switch(key){
        case GLUT_KEY_F1:
            gRed += .1;
            break;
        case GLUT_KEY_F2:
            gGreen += .1;
            break;
        case GLUT_KEY_F3:
            gBlue += .1;
            break;
    }
}

void procKeys(unsigned char key, int x, int y){
    switch(key){
        case 'r':
            gRed -= .1;
            break;
        case 'g':
            gGreen -= .1;
            break;
        case 'b':
            gBlue += .1;
            break;
        case 27: //escape
            exit(0);
    }
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
    glutCreateWindow("Ex3 - keyboard input");

    init(); //initialize opengl state

    //register callbacks
    //register display callbacks
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);

    //keyinput
    glutSpecialFunc(procSpecialKeys);
    glutKeyboardFunc(procKeys);

    glutMainLoop(); //enter event loop
    return 0;
}