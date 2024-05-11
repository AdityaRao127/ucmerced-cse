#ifndef BUTTON_H
#define BUTTON_H

#include <GL/freeglut.h>

struct Button{
    float w;
    float h;
    float x;
    float y;

    float r;
    float g;
    float b;

    Button(){
        x = 0;
        y = 0;
        w = 0.4;
        h = 0.2;
        r = 0;
        g = 0;
        b = 1;
    }

    Button(float x, float y, float w, float h, float r, float g, float b){
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
        glVertex2f(x+w, y);
        glVertex2f(x+w, y-h);
        glVertex2f(x, y-h);

        glEnd();
    }

    bool inside(float mx, float my){
        if (mx >= x && mx <= x + w && my <= y && my >= y-h){
            return true;
        }
        else {
            return false;
        }
    }
};

#endif