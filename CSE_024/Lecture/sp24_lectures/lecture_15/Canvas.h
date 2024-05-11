#ifndef CANVAS_H
#define CANVAS_H

#include "Rectangle.h"
#include "Toolbar.h"
#include "Point.h"
#include "Scribble.h"

struct Canvas{
    Rectangle area;

    // Point points[10000];
    // int pCounter;

    Rectangle squares[1000];
    int sCounter;
    int selectedSquare;

    float offsetX;
    float offsetY;

    Scribble scribbles[100];
    int scribbleCounter;
    int selectedScribble;

    Canvas(){
        area = Rectangle(-0.8, 1, 1.8, 1.8, Color(1,1,1));
        // pCounter = 0;
        sCounter = 0;
        selectedSquare = -1;
        selectedScribble = -1;
        offsetX = 0;
        offsetY = 0;
    }

    void draw(){
        area.draw();
        // for (int i = 0; i < pCounter; i++){
        //     points[i].draw();
        // }

        for (int i = 0; i < scribbleCounter; i++){
            scribbles[i].draw();
        }

        for (int i = 0; i < sCounter; i++){
            squares[i].draw();
        }
    }
    void handleMouseDrag(float x, float y, Tool selectedTool, Color color){
        if (selectedTool == PENCIL){
            // points[pCounter] = Point(x, y, color);
            // pCounter++;
            scribbles[scribbleCounter-1].addPoint(x, y, color);
        }
        else if (selectedTool == ERASER){
            // points[pCounter] = Point(x, y, Color(1,1,1), 20);
            // pCounter++;
        }
        else if (selectedTool == MOUSE){
            if (selectedSquare != -1){
                squares[selectedSquare].setX(x - offsetX);
                squares[selectedSquare].setY(y + offsetY);
            }
        }
    }

    void handleMouseClick(float x, float y, Tool selectedTool, Color color){
        if (selectedTool == PENCIL){
            // points[pCounter] = Point(x, y, color);
            // pCounter++;

            // scribble.addPoint(x, y, color);
            scribbles[scribbleCounter] = Scribble();
            scribbleCounter++;
            scribbles[scribbleCounter-1].addPoint(x, y, color);
        }
        else if (selectedTool == ERASER){
            // points[pCounter] = Point(x, y, Color(1,1,1), 20);
            // pCounter++;
        }
        else if (selectedTool == SQUARE){
            squares[sCounter] = Rectangle(x, y, 0.3, 0.3, color);
            sCounter++;
        }
        else if (selectedTool == MOUSE){
            for (int i = 0; i < sCounter; i++){
                squares[i].deselect();
            }
            selectedSquare = -1;
            for (int i = sCounter-1; i >= 0; i--){
                if (squares[i].contains(x, y)){
                    squares[i].select();
                    selectedSquare = i;
                    offsetX = x - squares[i].getX();
                    offsetY = squares[i].getY() - y;
                    break;
                }
            }

            for (int i = 0; i < scribbleCounter; i++){
                scribbles[i].deselect();
            }
            selectedScribble = -1;

            for (int i = scribbleCounter-1; i >= 0; i--){
                if (scribbles[i].contains(x, y)){
                    scribbles[i].select(); 
                    selectedScribble = i;
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