#ifndef POINT_H
#define POINT_H

#include <GL/freeglut.h>
#include <GL/gl.h>

class Point {
    float x;
    float y;
    float r;
    float g; 
    float b;
    int thickness;

public:
    Point() {
        x = 0.0f;
        y = 0.0f;
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
        thickness = 5;
    }

    Point(float x, float y) : Point() {
        this->x = x;
        this->y = y;
    }

    Point(float x, float y, float r, float g, float b) : Point(x, y) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    Point(float x, float y, float r, float g, float b, int thickness) : Point(x, y, r, g, b) {
        this->thickness = thickness;
    }

    void draw() {
        glColor3f(r, g, b);
        glPointSize(thickness);
        glBegin(GL_POINTS);
            glVertex2f(x, y);
        glEnd();
    }

    float getX(){
        return x;
    }
    float getY(){
        return y;
    }


    int getThickness(){
        return thickness;
    }

    void setX(float x){
        this->x = x;
    }

    void setY(float y){
        this->y = y;
    }

    void setColor(float r, float g, float b){
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void setThickness(int thickness){
        this->thickness = thickness;
    }
};


#endif