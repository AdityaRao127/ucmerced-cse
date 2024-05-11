#ifndef CANVAS_H
#define CANVAS_H

#include "Rectangle.h"
#include "Toolbar.h"
#include "Point.h"

struct Canvas {
private:
    Rectangle area;

    Point points[10000];
    int pCounter;

public:
    Canvas(){
        area = Rectangle(-0.8f, 1.0f, 1.8f, 1.8f, Color(1.0f, 1.0f, 1.0f));
        pCounter = 0;
    }

    void draw(){
        area.draw();

        for (int i = 0; i < pCounter; i++){
            points[i].draw();
        }
    }

    void handleMouseClick(float x, float y, Tool tool, Color color){
        if (tool == PENCIL){
            points[pCounter] = Point(x, y, color);
            pCounter++;
        }
        else if (tool == ERASER){
            points[pCounter] = Point(x, y, Color(1.0f, 1.0f, 1.0f), 20.0f);
            pCounter++;
        }
    }

    bool contains(float x, float y){
        return area.contains(x, y);
    }
};

#endif