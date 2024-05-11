#ifndef CANVAS_H
#define CANVAS_H

#include "Toolbar.h"
#include "Rectangle.h"
#include "Scribble.h"
#include "Circle.h"

struct Canvas {
    Rectangle area;

    Shape* shapes[1000];
    int shapeCounter;
    int selectedShape;

    float offsetX;
    float offsetY;

    Canvas(){
        area = Rectangle(-0.8f, 1.0f, 1.8f, 1.8f, Color(1.0f, 1.0f, 1.0f));
        shapeCounter = 0;
        selectedShape = -1;
    }

    void eraseShape(float x, float y) {
        int indexToDelete = -1;

        for (int i = 0; i < shapeCounter; i++) {
            if (shapes[i]->contains(x, y)) {
                indexToDelete = i;
                break;
            }
        }
        
        if (indexToDelete != -1) {                
            delete shapes[indexToDelete];
            for (int i = indexToDelete; i < shapeCounter - 1; i++) {
                shapes[i] = shapes[i + 1];
            }

            shapeCounter--;
        }
    }

    void handleMouseClick(float x, float y, Tool tool, Color color){
        if (tool == PENCIL){
            shapes[shapeCounter] = new Scribble();
            shapeCounter++;
            ((Scribble*)shapes[shapeCounter - 1])->addPoint(x, y, color);
        }
        else if (tool == ERASER){
            eraseShape(x, y);
        }
        else if (tool == SQUARE){
            shapes[shapeCounter] = new Rectangle(x, y, 0.2f, 0.2f, color);
            shapeCounter++;
        } 
        else if (tool == CIRCLE){
            shapes[shapeCounter] = new Circle(x, y, 0.1f, color);
            shapeCounter++;
        }
        else if (tool == MOUSE) {
            for (int i = 0; i < shapeCounter; i++) {
                shapes[i]->deselect();
            }

            selectedShape = -1;
            for (int i = shapeCounter - 1; i >= 0; i--) {
                if (shapes[i]->contains(x, y)) {
                    shapes[i]->select();
                    selectedShape = i;
                    offsetX = x - shapes[i]->getX();
                    offsetY = shapes[i]->getY() - y;
                }
            }

            if (selectedShape != -1) {
                shapes[selectedShape]->setColor(color);
            }
        }
    }

    void handleMouseMotion(float x, float y, Tool tool, Color color) {
        if (tool == PENCIL){
            ((Scribble*)shapes[shapeCounter - 1])->addPoint(x, y, color);
        }
        else if (tool == ERASER){
            eraseShape(x, y);
        }
        if (tool == MOUSE) {
            if (selectedShape != -1) {
                shapes[selectedShape]->setX(x - offsetX);
                shapes[selectedShape]->setY(y + offsetY);
            }
        }
    }

    void draw(){
        area.draw();

        for (int i = 0; i < shapeCounter; i++) {
            shapes[i]->draw();
        }
    }

    bool contains(float x, float y){
        return area.contains(x, y);
    }
};

#endif