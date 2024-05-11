#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "Shape.h"
#include "Point.h"
#include <iostream>
#include <stdexcept>

class Scribble : public Shape {

    // Point points[5000];
    Point *points;
    int pCounter;

    int capacity;

    float leftX;
    float rightX;
    float topY;
    float bottomY;

public:
    Scribble() {
        capacity = 1;
        points = new Point[capacity];
        pCounter = 0;

        x = 0.0f;
        y = 0.0;

        leftX = 0.0f;
        rightX = 0.0f;
        topY = 0.0f;
        bottomY = 0.0f;

        selected = false;
    }

    Scribble& operator=(const Scribble& other){

        capacity = other.capacity;
        pCounter = other.pCounter;

        x = other.x;
        y = other.y;

        leftX = other.leftX;
        rightX = other.rightX;
        topY = other.topY;
        bottomY = other.bottomY;

        selected = other.selected;

        // points = other.points; // Default behavior

        delete[] points;

        points = new Point[capacity];

        for (int i = 0; i < pCounter; i++){
            points[i] = other.points[i];
        }

        return *this;
    }

    void moveUp(){
        for (int i = 0; i < pCounter; i++){
            points[i].setY(points[i].getY() + 0.1);
        }
    }

    void moveDown(){
        for (int i = 0; i < pCounter; i++){
            points[i].setY(points[i].getY() - 0.1);
        }
    }

    void addPoint(float x, float y, Color color) {
        if (pCounter == 0) {
            this->x = x;
            this->y = y;
        }

        points[pCounter] = Point(x - this->x, y - this->y, color);
        pCounter++;

        if (pCounter == capacity){
            // throw std::logic_error("Out of resources");
            Point *old = points;

            points = new Point[capacity * 2];

            for (int i = 0; i < pCounter; i++){
                points[i] = old[i];
            }

            delete[] old;

            capacity = capacity * 2;
            
        }


        if (this->x - x > leftX) {
            leftX = this->x - x;
        }
        if (x - this->x > rightX) {
            rightX = x - this->x;
        }
        if (this->y - y > bottomY) {
            bottomY = this->y - y;
        }
        if (y - this->y > topY) {
            topY = y - this->y;
        }
    }


    void draw() {
        for (int i = 0; i < pCounter; i++) {
            float computedX = x + points[i].getX();
            float computedY = y + points[i].getY();
            Color computedColor = points[i].getColor();
            Point computedPoint = Point(computedX, computedY, computedColor);
            computedPoint.draw();
        }

        if (selected) {
            glColor3f(0.0f, 0.0f, 0.0f);
            glLineWidth(2.0f);

            glBegin(GL_LINES);
                glVertex2f(x - leftX - 0.02f, y + topY + 0.02f);
                glVertex2f(x + rightX + 0.02f, y + topY + 0.02f);

                glVertex2f(x + rightX + 0.02f, y + topY + 0.02f);
                glVertex2f(x + rightX + 0.02f, y - bottomY - 0.02f);

                glVertex2f(x + rightX + 0.02f, y - bottomY - 0.02f);
                glVertex2f(x - leftX - 0.02f, y - bottomY - 0.02f);

                glVertex2f(x - leftX - 0.02f, y - bottomY - 0.02f);
                glVertex2f(x - leftX - 0.02f, y + topY + 0.02f);
            glEnd();
        }
    }

    bool contains(float x, float y) {
        if (x >= this->x - leftX && x <= this->x + rightX && y >= this->y - bottomY && y <= this->y + topY) {
            return true;
        } else {
            return false;
        }
    }

};

#endif