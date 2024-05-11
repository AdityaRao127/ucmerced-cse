#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/freeglut.h>
#include "Color.h"

struct Rectangle {
private:
    float x;
    float y;
    float w;
    float h;
    Color color;
    bool selected;

public:
    Rectangle() {
        x = 0.0f;
        y = 0.0f;
        w = 0.4f;
        h = 0.2f;
        selected = false;
    }

    Rectangle(float x, float y, float w, float h, Color color) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->color = color;
        selected = false;
    }

    void setColor(Color color) {
        this->color = color;
    }

    void select() {
        selected = true;
    }

    void deselect() {
        selected = false;
    }

    void draw() {
        glColor3f(color.getR(), color.getG(), color.getB());

        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        if (selected) {
            Rectangle outer(x + 0.02f, y - 0.02f, w - 0.04f, h - 0.04f, Color(1.0f, 1.0f, 1.0f));
            Rectangle inner(x + 0.04f, y - 0.04f, w - 0.08f, h - 0.08f, color);
            outer.draw();
            inner.draw();
        }
    }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        } else {
            return false;
        }
    }
};

#endif