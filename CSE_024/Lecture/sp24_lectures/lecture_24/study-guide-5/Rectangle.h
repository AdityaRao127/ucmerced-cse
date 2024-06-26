#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/gl.h>
#include <iostream>
#include "Shape.h"

class Rectangle : public Shape{
    float w;
    float h;

public:

    Rectangle(){
        w = 0.4f;
        h = 0.4f;
    }

    Rectangle(float x, float y, float w, float h, float r, float g, float b){
        std::cout << "Rectangle(...)" << std::endl;
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void draw(){
        glColor3f(r, g, b);

        glBegin(GL_POLYGON);

            glVertex2f(x-w/2, y+h/2);
            glVertex2f(x + w/2, y+h/2);
            glVertex2f(x + w/2, y - h/2);
            glVertex2f(x-w/2, y - h/2);

        glEnd();
    }


    bool contains(float mx, float my){
        return mx >= x && mx <= x + w && my <= y && my >= y - h;
    }

};

#endif