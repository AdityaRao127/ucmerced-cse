#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "Color.h"
#include "Point.h"
#include <GL/gl.h>

class Scribble{
    Point points[5000];
    int pCounter;

    bool selected;

    float left;
    float right;
    float top;
    float bottom;

public:
    Scribble(){
        pCounter = 0;
        selected = false;

        left = 1;
        right = -1;
        top = -1;
        bottom = 1;
    }

    void addPoint(float x, float y, Color color){
        if (x < left){
            left = x;
        }
        if (x > right){
            right = x;
        }
        if (y > top){
            top = y;
        }
        if (y < bottom){
            bottom = y;
        }
        points[pCounter] = Point(x, y, color);
        pCounter++;
    }

    void draw(){
        if (selected){
            //Draw bounding box
            glLineWidth(2);
            glColor3f(0.6,0.6,0.6);

            glBegin(GL_LINES);

            glVertex2f(left - 0.02, top + 0.02);
            glVertex2f(right + 0.02, top + 0.02);

            glVertex2f(right + 0.02, top + 0.02);
            glVertex2f(right + 0.02, bottom - 0.02);

            glVertex2f(right + 0.02, bottom - 0.02);
            glVertex2f(left - 0.02, bottom - 0.02);

            glVertex2f(left - 0.02, bottom - 0.02);
            glVertex2f(left - 0.02, top + 0.02);

            glEnd();
        }

        for (int i = 0; i < pCounter; i++){
            points[i].draw();
        }
    }

    bool contains(float x, float y){
        return x >= left && x <= right && y <= top && y >= bottom;
    }

    void deselect(){
        selected = false;
    }

    void select(){
        selected = true;
    }

};

#endif