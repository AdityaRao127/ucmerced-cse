#include "Button.h"
#include "Point.h"
#include <GL/freeglut.h>
#include <iostream>

using namespace std;

// Window width and height
int width = 400;
int height = 400;

Point points[1000];
int pCounter = 0;

Button blueBtn(-0.8, -0.8, 0.4, 0.2, 0, 0, 1);
Button redBtn(-0.3, -0.8, 0.4, 0.2, 1, 0, 0);

float r = 1;
float g = 0;
float b = 0;

// Convert window coordinates to Cartesian coordinates
void windowToScene(float &x, float &y) {
  x = (2.0f * (x / float(width))) - 1.0f;
  y = 1.0f - (2.0f * (y / float(height)));
}

void drawScene() {
  // Clear the screen and set it to current color (black)
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Objects to be drawn go here

  glPointSize(10);

  for (int i = 0; i < pCounter; i++) {
    points[i].draw();
  }

  blueBtn.draw();
  redBtn.draw();

  // We have been drawing to the back buffer, put it in the front
  glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
  /*
      button: 0 -> left mouse button
              1 -> right mouse button

      state:  0 -> mouse click
              2 -> mouse release

      x, y:   mouse location in window relative coordinates
  */
  float mx = x;
  float my = y;
  windowToScene(mx, my);

  if (button == 0 && state == 0) {
    points[pCounter] = Point(mx, my, r, g, b);
    pCounter++;

    if (blueBtn.inside(mx, my)) {
      cout << "Blue was clicked" << endl;
      r = 0;
      g = 0;
      b = 1;
    }
    if (redBtn.inside(mx, my)) {
      cout << "Red was clicked" << endl;
      r = 1;
      g = 0;
      b = 0;
    }
  }
  glutPostRedisplay();
}

void motion(int x, int y) {
  /*
      x, y:   mouse location in window relative coordinates
  */
  float mx = x;
  float my = y;
  windowToScene(mx, my);

  if (pCounter < 1000) {
    points[pCounter] = Point(mx, my, r, g, b);
    pCounter++;
  }
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
  /*
      key:    ASCII character of the keyboard key that was pressed
      x, y:   mouse location in window relative coordinates
  */
}

int main(int argc, char **argv) {
  // Perform some initialization
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("GLUT App");

  // Set the Display Function
  glutDisplayFunc(drawScene);

  // Set the Mouse Function
  glutMouseFunc(mouse);

  // Set the Motion Function
  glutMotionFunc(motion);

  // Set the Keyboard Funcion
  glutKeyboardFunc(keyboard);

  // Run the program
  glutMainLoop();

  return 0;
}