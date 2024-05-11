#ifndef COLOR_H
#define COLOR_H

#include <GL/freeglut.h>

struct Color {
    float r;
    float g;
    float b;

    Color() {
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
    }

    Color(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void setColor(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void setRed() {
        r = 1.0f;
        g = 0.0f;
        b = 0.0f;
    }

    void setGreen() {
        r = 0.0f;
        g = 1.0f;
        b = 0.0f;
    }

    void setBlue() {
        r = 0.0f;
        g = 0.0f;
        b = 1.0f;
    }
};


#endif