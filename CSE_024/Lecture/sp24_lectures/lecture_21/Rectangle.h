#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include "Color.h"
#include "Shape.h"

class Rectangle : public Shape{

    float w;
    float h;
    Color color;
    bool solid;

    

public:

    Rectangle* neighbor;
    
    Rectangle() {
        x = 0.0f;
        y = 0.0f;
        w = 0.2f;
        h = 0.2f;
        selected = false;
        solid = true;
        neighbor = nullptr;
    }

    Rectangle(float x, float y, float w, float h, Color color) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->color = color;
        selected = false;
        solid = true;
        neighbor = nullptr;
    }
    Rectangle(float x, float y, float w, float h) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        selected = false;
        solid = false;
        neighbor = nullptr;
    }

    void draw() {
        if (!solid){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        glColor3f(color.getR(), color.getG(), color.getB());
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (selected) {
            Rectangle outer(x + 0.02, y - 0.02, w - 0.04, h - 0.04, Color(1.0f, 1.0f, 1.0f));
            Rectangle inner(x + 0.04, y - 0.04, w - 0.08, h - 0.08, color);
            outer.draw();
            inner.draw();
        }

        if (neighbor){
            glBegin(GL_LINES);
            glVertex2f(x + w/2, y - h/2);
            glVertex2f(neighbor->x + neighbor->w/2, neighbor->y - neighbor->h/2);
            glEnd();
        }
    }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        } else {
            return false;
        }
    }

    void setColor(Color color){
        this->color = color;
    }

    void setW(float w){
        this->w = w;
    }

    void setH(float h){
        this->h = h;
    }

    float getW(){
        return w;
    }

    float getH(){
        return h;
    }

};

#endif