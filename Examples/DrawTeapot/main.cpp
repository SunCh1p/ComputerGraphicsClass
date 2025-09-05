#include <GL/glut.h>
#define WIN_H 480
#define WIN_W 640
#define SIZE 100

GLfloat rot = .1;
bool bXaxis = false;
bool bYaxis = false;
bool bZaxis = false;
bool bMouseDown = false;


//callback function for glutDisplayFunc
void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    //set color to white
    glColor3f(1.0, 1.0, 1.0);
    //draw square which is all white
    glMatrixMode(GL_MODELVIEW);
    if(!bMouseDown){
        if(bXaxis) glRotatef(rot, 1.0f, 0.0f, 0.0f);
        else if(bYaxis) glRotatef(rot, 0.0f, 1.0f, 0.0f);
        else if(bZaxis) glRotatef(rot, 0.0f, 0.0f, 1.0f);
        else glRotatef(rot, 1.0f, 1.0f, 1.0f);
    }
    glutWireTeapot(SIZE);
    glFlush();
}

void init(void){
    /*select clearing background color*/
    glClearColor(0.0, 0.0, 0.0, 0.0);
    /*Initialize viewing values*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIN_W/2, WIN_W/2, -WIN_H/2, WIN_H/2, -100, 100);
}

void procKeys(unsigned char key, int x, int y){
    switch(key){
        case 'x':
            bXaxis = true;
            bYaxis = false;
            bZaxis = false;
            break;
        case 'y':
            bXaxis = false;
            bYaxis = true;
            bZaxis = false;
            break;
        case 'z':
            bXaxis = false;
            bYaxis = false;
            bZaxis = true;
            break;
        case 'i':
            rot += .1;
            break;
        case 27: //escape
            exit(0);
            break;
    }
}

void procMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        bMouseDown = true;
    } else {
        bMouseDown = false;
    }
}

int main(int argc, char** argv){
    //initialize glut
    glutInit(&argc, argv);
    //set display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //set window position
    glutInitWindowPosition(100, 100);
    //set window size
    glutInitWindowSize(WIN_W, WIN_H);
    //create the window
    glutCreateWindow("Ex4 - Object Rotation with the mouse");

    init(); //initialize opengl state

    //register callbacks
    //register display callbacks
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);

    //keyinput and mouse input
    glutKeyboardFunc(procKeys);
    glutMouseFunc(procMouse);

    glutMainLoop(); //enter event loop
    return 0;
}