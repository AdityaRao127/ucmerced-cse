#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/freeglut.h>
#include "Color.h"

struct Rectangle {
    float x;
    float y;
    float w;
    float h;
    Color color;
    bool selected;

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

    void draw() {
        glColor3f(color.r, color.g, color.b);
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        if (selected) {
            Rectangle outer(x + 0.02, y - 0.02, w - 0.04, h - 0.04, Color(1.0f, 1.0f, 1.0f));
            Rectangle inner(x + 0.04, y - 0.04, w - 0.08, h - 0.08, color);
            outer.draw();
            inner.draw();
        }
    }

    bool isClicked(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
            return true;
        } else {
            return false;
        }
    }
};

#endif