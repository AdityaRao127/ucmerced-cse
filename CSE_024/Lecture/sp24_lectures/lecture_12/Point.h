#ifndef POINT_H
#define POINT_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include "Color.h"

struct Point {
    float x;
    float y;
    Color color;
    int thickness;

    Point() {
        x = 0.0f;
        y = 0.0f;
        thickness = 5;
    }

    Point(float x, float y, Color color) {
        this->x = x;
        this->y = y;
        this->color = color;
        thickness = 5;
    }

    Point(float x, float y, Color color, int thickness) {
        this->x = x;
        this->y = y;
        this->color = color;
        this->thickness = thickness;
    }

    void draw() {
        glColor3f(color.r, color.g, color.b);
        glPointSize(thickness);
        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
    }
};


#endif