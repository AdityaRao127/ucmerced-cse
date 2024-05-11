#ifndef CANVAS_H
#define CANVAS_H

#include "Rectangle.h"
#include "Toolbar.h"
#include "Point.h"

struct Canvas{
    Rectangle area;

    Point points[10000];
    int pCounter;

    Canvas(){
        area = Rectangle(-0.8, 1, 1.8, 1.8, Color(1,1,1));
        pCounter = 0;
    }

    void draw(){
        area.draw();
        for (int i = 0; i < pCounter; i++){
            points[i].draw();
        }
    }

    void handleMouseClick(float x, float y, Tool selectedTool, Color color){
        if (selectedTool == PENCIL){
            points[pCounter] = Point(x, y, color);
            pCounter++;
        }
    }

    bool contains(float x, float y){
        return area.contains(x, y);
    }
};

#endif