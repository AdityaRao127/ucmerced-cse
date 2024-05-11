#include <GL/freeglut_std.h>
#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>


using namespace std;


// State variables
int width = 400;
int height = 400;

float px = 0.5;
float py = 0.5;

float r = 1;
float g = 0;
float b = 0;

int point = 20;

void windowToScene ( float& x, float &y ){
    x = (2.0f * (x / float(width))) - 1.0f;
    y = 1.0f - (2.0f * (y / float(height)));
}

void drawPoint(float x, float y, float r, float g, float b, int size){
    glColor3f(r,g,b);
    glPointSize(size);
    glEnable(GL_POINT_SMOOTH);

    glBegin(GL_POINTS);

    glVertex2f(x, y);

    glEnd();
}

void drawScene(){
    // Clear the screen and set it to current color (black)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Objects to be drawn go here

    drawPoint(px, py, r, g, b, point);
    drawPoint(px, py, 1, 1, 1, point/3);

    // We have been drawing to the back buffer, put it in the front
    glutSwapBuffers();
}

void motion(int x, int y){
    float mx = x;
    float my = y;
    windowToScene(mx, my);

    px = mx;
    py = my;

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){

    float mx = x;
    float my = y;

    if (state == 0){
        point = 10;
    }
    else if (state == 1){
        point = 20;
    }

    windowToScene(mx, my);
    if (state == 0 && button == 0){
        // cout << "Button:    " << button << endl;
        // cout << "State:     " << state << endl;
        // cout << "X:         " << mx << endl;
        // cout << "Y:         " << my << endl;

        px = mx;
        py = my;

        
    }

    glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y){
    if (key == 'r'){
        r = 1;
        g = 0;
        b = 0;
    }
    else if (key == 'g'){
        r = 0;
        g = 1;
        b = 0;
    }
    else if (key == 'b'){
        r = 0;
        g = 0;
        b = 1;
    }
    else if (key == 27){
        exit(0);
    }

    glutPostRedisplay();
}

int main(int argc,char** argv) {
    // Perform some initialization
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("GLUT App");

    // Set the Display Function
    glutDisplayFunc(drawScene);

    glutMouseFunc(mouse);

    glutKeyboardFunc(keyDown);

    glutMotionFunc(motion);
    
    // Run the program
    glutMainLoop();

    return 0;
}







