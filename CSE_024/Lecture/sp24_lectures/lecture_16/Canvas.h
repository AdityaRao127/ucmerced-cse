#ifndef CANVAS_H
#define CANVAS_H

#include "Rectangle.h"
#include "Toolbar.h"
#include "Point.h"
#include "Scribble.h"

struct Canvas{
    Rectangle area;

    // Rectangle squares[1000];
    // int sCounter;
    // int selectedSquare;

    float offsetX;
    float offsetY;

    // Scribble scribbles[100];
    // int scribbleCounter;
    // int selectedScribble;

    Shape* shapes[1000];
    int shapeCounter;
    int selectedShape;

    Canvas(){
        area = Rectangle(-0.8, 1, 1.8, 1.8, Color(1,1,1));
        // scribbleCounter = 0;
        // sCounter = 0;
        // selectedSquare = -1;
        // selectedScribble = -1;
        shapeCounter = 0;
        selectedShape = -1;
        offsetX = 0;
        offsetY = 0;
    }

    void draw(){
        area.draw();

        for (int i = 0; i < shapeCounter; i++){
            shapes[i]->draw();
        }

        // for (int i = 0; i < sCounter; i++){
        //     squares[i].draw();
        // }

        // for (int i = 0; i < scribbleCounter; i++){
        //     scribbles[i].draw();
        // }
    }

    void handleMouseClick(float x, float y, Tool selectedTool, Color color){
        if (selectedTool == PENCIL){
            shapes[shapeCounter] = new Scribble();
            shapeCounter++;
            ((Scribble*)shapes[shapeCounter-1])->addPoint(x, y, color);
        }
        else if (selectedTool == ERASER){

        }
        else if (selectedTool == SQUARE){
            shapes[shapeCounter] = new Rectangle(x, y, 0.3, 0.3, color);
            shapeCounter++;
        }
        else if (selectedTool == MOUSE){
            // for (int i = 0; i < sCounter; i++){
            //     squares[i].deselect();
            // }
            // selectedSquare = -1;
            // for (int i = sCounter-1; i >= 0; i--){
            //     if (squares[i].contains(x, y)){
            //         squares[i].select();
            //         selectedSquare = i;
            //         offsetX = x - squares[i].getX();
            //         offsetY = squares[i].getY() - y;
            //         break;
            //     }
            // }

            // for (int i = 0; i < scribbleCounter; i++){
            //     scribbles[i].deselect();
            // }
            // selectedScribble = -1;

            // for (int i = scribbleCounter-1; i >= 0; i--){
            //     if (scribbles[i].contains(x, y)){
            //         scribbles[i].select(); 
            //         selectedScribble = i;
            //         break;
            //     }
            // }
        }
    }

    void handleMouseDrag(float x, float y, Tool selectedTool, Color color){
        if (selectedTool == PENCIL){
            ((Scribble*)shapes[shapeCounter-1])->addPoint(x, y, color);
        }
        // else if (selectedTool == ERASER){

        // }
        // else if (selectedTool == MOUSE){
        //     if (selectedSquare != -1){
        //         squares[selectedSquare].setX(x - offsetX);
        //         squares[selectedSquare].setY(y + offsetY);
        //     }
        //     else if (selectedScribble != -1){
        //         // std::cout << "Move the scribble" << std::endl;
        //         scribbles[selectedScribble].setX(x - offsetX);
        //         scribbles[selectedScribble].setY(y + offsetY);
        //     }
        // }
    }

    

    bool contains(float x, float y){
        return area.contains(x, y);
    }
};

#endif