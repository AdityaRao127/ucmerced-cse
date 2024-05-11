#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

void drawScene(){
    // Clear the screen and set it to current color (black)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(4);

    // rectangle
    glBegin(GL_LINES);
        glLineWidth(4);
        glVertex2f(-0.90, 0.75);
        glVertex2f(-0.90, -0.75);

        glVertex2f(-0.90, -0.75);
        glVertex2f(0.90, -0.75);

        glVertex2f(0.90, -0.75);
        glVertex2f(0.90, 0.75); 

        glVertex2f(0.90, 0.75);
        glVertex2f(-0.90, 0.75);
    glEnd(); 

    

    // letters

    glBegin(GL_LINES);
        glColor3f(0.0f, 1.0f, 1.0f);
        glLineWidth(2);

        // letter A

        glVertex2f(-0.75, -0.70);
        glVertex2f(-0.60, 0.70);

        glVertex2f(-0.60, 0.70);
        glVertex2f(-0.45, -0.70);

        glVertex2f(-0.67, 0);
        glVertex2f(-0.52,0);


        // letter K
        glVertex2f(-0.15, .70);
        glVertex2f(-0.15, -.70);

        glVertex2f(-.15, 0);
        glVertex2f(0.15, 0.70);

        glVertex2f(-.15, 0);
        glVertex2f(0.15, -0.70);

        // letter R

        glVertex2f(0.45, 0.70);
        glVertex2f(0.45, -.70);

        glVertex2f(0.45, 0.70);
        glVertex2f(0.70, 0.70);

        glVertex2f(0.70, 0.70);
        glVertex2f(0.70, 0.20);

        glVertex2f(0.70, 0.20); 
        glVertex2f(0.45, 0.20);

        glVertex2f(0.45, 0.20);
        glVertex2f(0.70, -0.70);       

        glEnd();

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

    return(0);
}