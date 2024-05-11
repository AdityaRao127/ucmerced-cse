#include "Button.h"
#include "Color.h"
#include "Point.h"
#include "Rectangle.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;

// Window width and height
int width = 400;
int height = 400;

Point points[10000];
int pCounter = 0;
int thickness = 10;

// buttons

Rectangle blueBtn(-1, 1, 0.2, 0.3, 0, 0, 1);
Rectangle redBtn(-1, 0.7, 0.2, 0.3, 1, 0, 0);
Rectangle yellowBtn(-1, 0.4, 0.2, 0.3, 1, 1, 0);
Rectangle orangeBtn(-1, 0.1, 0.2, 0.3, 1, 0.647, 0);
Rectangle greenBtn(-1, -0.2, 0.2, 0.3, 0, 0.502, 0);
Rectangle violetBtn(-1, -0.5, 0.2, 0.3, 0.58, 0.0, 0.827);
Rectangle colorIndicator(-0.90, -0.8025, 0.065, 0.065, 1, 1, 1);
Rectangle thicknessIndicator(-0.93, -0.92125, 0.05, 0.05, 0, 0, 0);

Color brushColor;
Color current;
// bool colorSelected = false;

Rectangle canvas(-0.8, 1, 1.8, 1.8, 1, 1, 1);
Rectangle vertical(-1, 1, 0.2, 2, 0.7, 0.7, 0.7);
Rectangle horizontal(-0.8, -0.8, 1.8, 0.2, 0.6, 0.6, 0.6);

Button clearBtn("Clear", 0.71, -0.8);
Button brushIcon("Brush", 0.375, -0.8);
Button eraser("Eraser", 0, -0.8);
Button plusSize("+ Size", -0.8, -0.8);
Button minusSize("- Size", -0.4, -0.8);

// indicate what tool is being selected
Rectangle toolSelection(-0.8, -0.8, 0.2, 0.2, 0, 0, 0);

// Convert window coordinates to Cartesian coordinates
void windowToScene(float &x, float &y) {
  x = (2.0f * (x / float(width))) - 1.0f;
  y = 1.0f - (2.0f * (y / float(height)));
}

void drawScene() {
  // Clear the screen and set it to current color (black)
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  canvas.draw();
  // int thickness = 10;
  // Objects to be drawn go here
  glEnable(GL_POINT_SMOOTH);
  glPointSize(thickness);

  for (int i = 0; i < pCounter; i++) {
    points[i].draw();
  }

  vertical.draw();
  horizontal.draw();

  blueBtn.draw();
  redBtn.draw();
  yellowBtn.draw();
  orangeBtn.draw();
  greenBtn.draw();
  violetBtn.draw();
  colorIndicator.draw();
  toolSelection.draw();
  thicknessIndicator.draw();

  clearBtn.render();
  brushIcon.render();
  eraser.render();
  plusSize.render();
  minusSize.render();

  // We have been drawing to the back buffer, put it in the front
  glutSwapBuffers();
}

bool brushClicked = false;

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

// none of the buttons are clicked is mouse is not down
  if (button == 0 && state == 1) {
    clearBtn.down = false;
    brushIcon.down = false;
    eraser.down = false;
    plusSize.down = false;
    minusSize.down = false; 
  }

  if (button == 0 && state == 0) {
    if (canvas.inside(mx, my) && brushClicked) {
      if (pCounter < 10000) {
        points[pCounter] = Point(mx, my, brushColor, thickness);
        pCounter++;
      }
    } else if (vertical.inside(mx, my) || (horizontal.inside(mx, my))) {
      if (blueBtn.inside(mx, my)) {
        if (brushClicked) {
          cout << "Blue was clicked" << endl;
          brushColor.setBlue();
          current = brushColor;
          colorIndicator.r = 0; // set color indicator to the color of brush
          colorIndicator.g = 0;
          colorIndicator.b = 1;
        } else {
          cout << "Select the brush tool to paint" << endl;
        }
        //
      }
      if (redBtn.inside(mx, my)) {
        if (brushClicked) {
          cout << "Red was clicked" << endl;
          brushColor.setRed();
          current = brushColor;
          colorIndicator.r = 1;
          colorIndicator.g = 0;
          colorIndicator.b = 0;
        } else {
          cout << "Select the brush tool to paint" << endl;
        }
      }

      // added additional colors 
      if (yellowBtn.inside(mx, my)) {
        if (brushClicked) {
          cout << "Yellow was clicked" << endl;
          brushColor.setYellow();
          current = brushColor;
          colorIndicator.r = 1;
          colorIndicator.g = 1;
          colorIndicator.b = 0;
        } else {
          cout << "Select the brush tool to paint" << endl;
        }
      }
      if (orangeBtn.inside(mx, my)) {
        if (brushClicked) {
          cout << "Orange was clicked" << endl;
          brushColor.setOrange();
          current = brushColor;
          colorIndicator.r = 1;
          colorIndicator.g = 0.647;
          colorIndicator.b = 0;
        } else {
          cout << "Select the brush tool to paint" << endl;
        }
        // r = 0; g = 0; b = 1;
      }
      if (greenBtn.inside(mx, my)) {
        if (brushClicked) {
          cout << "Green was clicked" << endl;
          brushColor.setGreen();
          current = brushColor;
          colorIndicator.r = 0;
          colorIndicator.g = 0.502;
          colorIndicator.b = 0;
        } else {
          cout << "Select the brush tool to paint" << endl;
        }
        // r = 0; g = 0; b = 1;
      }
      if (violetBtn.inside(mx, my)) {
        if (brushClicked) {
          cout << "Violet was clicked" << endl;
          brushColor.setViolet();
          current = brushColor;
          colorIndicator.r = 0.58;
          colorIndicator.g = 0.0;
          colorIndicator.b = 0.827;
        } else {
          cout << "Select the brush tool to paint" << endl;
        }
        // r = 0; g = 0; b = 1;
      }
      if (clearBtn.inside(mx, my)) {
        cout << "Clear was clicked" << endl;
        pCounter = 0;
        clearBtn.down = true;
        brushColor.set(1, 1, 1);
      }
      if (brushIcon.inside(mx, my)) {
        cout << "Brush was selected. Select a color to paint!" << endl;
        brushIcon.down = true;
        brushClicked = true;
        current = brushColor;
        brushColor = current;
        current = brushColor;
        colorIndicator.r = brushColor.r;
        colorIndicator.g = brushColor.g;
        colorIndicator.b = brushColor.b;

        toolSelection.x = (brushIcon.x) - 0.0235;
        toolSelection.y = brushIcon.y;
        toolSelection.r = 1;
        toolSelection.g = 0;
        toolSelection.b = 0;
      }
      if (eraser.inside(mx, my)) {
        cout << "Eraser was selected" << endl;
        eraser.down = true;
        brushClicked = true;
        brushColor.set(1, 1, 1);
        toolSelection.x = (eraser.x) - 0.0235;
        toolSelection.y = (eraser.y);
        toolSelection.r = 1;
        toolSelection.g = 0;
        toolSelection.b = 0;
      }
      if (plusSize.inside(mx, my)) {
        glBegin(GL_POINTS);
        cout << "Brush thickness was increased" << endl;
        if (thickness < 30) {
          thickness++;
          // increase thickness if size button clicked
          thicknessIndicator.w += 0.0025;
          thicknessIndicator.h += 0.0025;
          thicknessIndicator.w = thicknessIndicator.h;
        } else {
          cout << "max thickness reached" << endl;
        }
        plusSize.down = true;
        glEnd();
      }
      if (minusSize.inside(mx, my)) {
        glBegin(GL_POINTS);
        if (thickness > 1) {
          thickness--;
          // decreased thickness if size button is thick
          cout << "Brush thickness decreased" << endl;
          thicknessIndicator.w -= 0.0025;
          thicknessIndicator.h -= 0.0025;
          thicknessIndicator.w = thicknessIndicator.h;
        } else {
          cout << "thickness can not be set lower" << endl;
        }

        minusSize.down = true;
        glEnd();
      }
    } else if (vertical.inside(mx, my)) {
      cout << "Clicked on Vertical" << endl;
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

  if (pCounter < 10000 && brushClicked) {
    if (canvas.inside(mx, my)) {
      points[pCounter] = Point(mx, my, brushColor, thickness);
      pCounter++;
    }
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