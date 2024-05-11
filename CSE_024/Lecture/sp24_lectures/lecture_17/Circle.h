#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/freeglut.h>
#include "Shape.h"
#include "Color.h"
#include <cmath>

class Circle : public Shape {
    float radius;

public:
    // default constructor
    Circle() {
        radius = 0.1f;
    }

    Circle(float x, float y, float radius, Color color) {
        this->x = x;
        this->y = y;
        this->radius = radius;
        this->color = color;
    }

    void draw() {
        glColor3f(color.getR(), color.getG(), color.getB());

        float inc = ( 2 * M_PI) / 60;
        
        glBegin(GL_POLYGON);
            for (float theta = 0; theta < 2*M_PI; theta += inc){
                glVertex2f(radius * cos(theta) + x, radius * sin(theta) + y);
            }
        glEnd();

        if (selected) {
            Circle outer(x, y, radius - 0.02f, Color(1.0f, 1.0f, 1.0f));
            Circle inner(x, y, radius - 0.04f, color);
            outer.draw();
            inner.draw();
        }
    }

    bool contains(float mx, float my) {
        if (radius >= sqrt((pow((mx - x), 2) + pow((my - y), 2)))) {
            return true;
        } else {
            return false;
        }
    }
};

#endif