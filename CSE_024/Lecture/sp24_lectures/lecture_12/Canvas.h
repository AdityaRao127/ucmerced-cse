#ifndef CANVAS_H
#define CANVAS_H

#include "Rectangle.h"
#include "Toolbar.h"
#include "Point.h"

struct Canvas{
    Rectangle area;

    Point points[10000];
    int pCounter;

    Rectangle squares[1000];
    int sCounter;

    int selectedSquare;

    Canvas(){
        area = Rectangle(-0.8, 1, 1.8, 1.8, Color(1,1,1));
        pCounter = 0;
        sCounter = 0;
        selectedSquare = -1;
    }

    void draw(){
        area.draw();
        for (int i = 0; i < pCounter; i++){
            points[i].draw();
        }
        for (int i = 0; i < sCounter; i++){
            squares[i].draw();
        }
    }

    void handleMouseClick(float x, float y, Tool selectedTool, Color color){
        if (selectedTool == PENCIL){
            points[pCounter] = Point(x, y, color);
            pCounter++;
        }
        else if (selectedTool == ERASER){
            points[pCounter] = Point(x, y, Color(1,1,1), 20);
            pCounter++;
        }
        else if (selectedTool == SQUARE){
            squares[sCounter] = Rectangle(x, y, 0.3, 0.3, color);
            sCounter++;
        }
        else if (selectedTool == MOUSE){
            for (int i = 0; i < sCounter; i++){
                squares[i].selected = false;
            }
            selectedSquare = -1;
            for (int i = sCounter-1; i >= 0; i--){
                if (squares[i].contains(x, y)){
                    squares[i].selected = true;
                    selectedSquare = i;
                    break;
                }
            }
        }
    }

    bool contains(float x, float y){
        return area.contains(x, y);
    }
};

#endif