#include <GL/freeglut_std.h>
#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>


using namespace std;

void drawScene(){
    // Clear the screen and set it to current color (black)
    glColor3f(0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Objects to be drawn go here

    // We have been drawing to the back buffer, put it in the front
    glutSwapBuffers();
}



int main(int argc,char** argv) {
    // Perform some initialization
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("GLUT App");

    // Set the Display Function
    glutDisplayFunc(drawScene);

    // Run the program
    glutMainLoop();

    return 0;
}