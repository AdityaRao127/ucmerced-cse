#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "Shape.h"
#include "Point.h"

class Scribble : public Shape {
    Point points[5000];
    int pCounter;

    float leftX;
    float rightX;
    float topY;
    float bottomY;

public:
    Scribble() {
        pCounter = 0;

        x = 0.0f;
        y = 0.0;

        leftX = 0.0f;
        rightX = 0.0f;
        topY = 0.0f;
        bottomY = 0.0f;

        selected = false;
    }

    void addPoint(float x, float y, Color color) {
        if (pCounter == 0) {
            this->x = x;
            this->y = y;
        }

        points[pCounter] = Point(x - this->x, y - this->y, color);
        pCounter++;

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