#ifndef POINT_H
#define POINT_H

#include "Color.h"
#include <GL/freeglut.h>

struct Point {
  // Instance variables
  float x;
  float y;

  float r;
  float g;
  float b;
  int thickness; 

  Point() {
    x = 0;
    y = 0;

    r = 0;
    g = 0;
    b = 0;
  }

  Point(float x, float y) {
    this->x = x;
    this->y = y;
    r = 0;
    g = 0;
    b = 0;
  }

  Point(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    this->r = r;
    this->g = g;
    this->b = b;
  }

  Point(float x, float y, Color color, int thickness) {
    this->x = x;
    this->y = y;
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
    this->thickness = thickness;
  }


  void draw() {
    glPointSize(thickness);
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
  }
};

#endif