#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/gl.h>
#include <iostream>
#include <cmath>
#include "Shape.h"

class Circle : public Shape{
    float radius;

public:
    Circle(){
        radius = 0.2;
    }

    Circle(float x, float y, float radius, float r, float g, float b){
        std::cout << "Circle(...)" << std::endl;
        this->x = x;
        this->y = y;
        this->radius = radius;
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void draw(){
        glColor3f(r, g, b);


        float inc = ( 2 * M_PI) / 60;
        
        glBegin(GL_POLYGON);
        for (float theta = 0; theta < 2*M_PI; theta += inc){
            glVertex2f(radius * cos(theta) + x, radius * sin(theta) + y);
        }
        glEnd();
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