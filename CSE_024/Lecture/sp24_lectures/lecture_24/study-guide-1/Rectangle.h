#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/gl.h>

class Rectangle{
    float x;
    float y;
    float w;
    float h;
    float r;
    float g;
    float b;

public:
    Rectangle(){
        x = 0.0f;
        y = 0.0f;
        w = 0.4f;
        h = 0.2f;
        r = 1.0f;
        g = 0.0f;
        b = 0.0f;
    }

    Rectangle(float x, float y, float w, float h, float r, float g, float b){
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

            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);

        glEnd();
    }

    void setColor(float r, float g, float b){
        this->r = r;
        this->g = g;
        this->b = b;
    }

    bool contains(float mx, float my){
        return mx >= x && mx <= x + w && my <= y && my >= y - h;
    }
};

#endif