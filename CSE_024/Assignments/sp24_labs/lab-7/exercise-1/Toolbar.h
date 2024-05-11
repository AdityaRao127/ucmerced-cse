#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "Rectangle.h"
#include "Texture.h"

enum Tool {PENCIL, ERASER, SQUARE, TRIANGLE, CIRCLE, RECTANGLE, MOUSE, CLEAR, FRONT, BACK};

struct Toolbar {
private:
    Rectangle area;
    Rectangle second_area; 
    Texture pencilButton;
    Texture eraserButton;
    Texture squareButton; 
    Texture circleButton; 
    Texture rectangleButton; 
    Texture mouseButton;
    Texture triangleButton;
    Texture clearButton; 
    Texture frontButton; 
    Texture backButton;

    Tool selectedTool; 
    
    bool isCleared = false; 

    void deselectAll(){
        pencilButton.deselect();
        eraserButton.deselect();
        squareButton.deselect();
        circleButton.deselect(); 
        rectangleButton.deselect(); 
        mouseButton.deselect(); 
        triangleButton.deselect(); 
        clearButton.deselect(); 
        frontButton.deselect();
        backButton.deselect();
    }

public:
    Toolbar(){
        area = Rectangle(-0.8f, -0.8f, 1.8f, 0.2f, Color(0.8f, 0.8f, 0.8f));
    
        second_area = Rectangle(-1.0f, 1.0f, 0.2f, 0.40f, Color(1.0f, 1.0f, 0.8f));
        pencilButton = Texture("assets/pencil.png", -1.0f, 1.0f, 0.2f, 0.2f);
        eraserButton = Texture("assets/eraser.png", -1.0f, 0.8f, 0.2f, 0.2f);

        // horizontal bar
        mouseButton = Texture("assets/mouse.png", -0.81, -0.8, 0.2, 0.2);
        squareButton = Texture("assets/square.png", -0.5, -0.8, 0.2, 0.2);
        circleButton = Texture("assets/circle.png", -0.3, -0.8, 0.2, 0.2);
        rectangleButton = Texture("assets/rectangle.png", -0.1, -0.8, 0.2, 0.2);
        triangleButton = Texture("assets/triangle.png", 0.1, -0.8, 0.2, 0.2);
        clearButton = Texture("assets/clear.png", 0.7, -0.8, 0.3, 0.21);
        frontButton = Texture("assets/front.png", 0.3, -0.8, 0.2, 0.2);
                backButton = Texture("assets/back.png", 0.50, -0.8, 0.2, 0.2);

        selectPencil();
    }

    Tool getSelectedTool(){
        return selectedTool;
    }

    void selectFront() {
        deselectAll();
                isCleared = false; 
        frontButton.select();
        selectedTool = FRONT;
    }

    void selectBack() {
        deselectAll();
                isCleared = false; 
        backButton.select();
        selectedTool = BACK;
    }

    void selectPencil() {
        deselectAll();
                isCleared = false; 
        pencilButton.select();
        selectedTool = PENCIL;
    }

    void selectEraser() {
        deselectAll();
                isCleared = false; 
        eraserButton.select();
        selectedTool = ERASER;
    }

    void selectMouse(){
        deselectAll();
        isCleared = false; 
        mouseButton.select(); 
        selectedTool = MOUSE; 
    }

    void selectSquare(){
        deselectAll(); 
                isCleared = false; 
        squareButton.select(); 
        selectedTool = SQUARE; 
    }

    void selectCircle(){
        deselectAll(); 
                isCleared = false; 
        circleButton.select(); 
        selectedTool = CIRCLE; 
    }

    void selectRectangle(){
        deselectAll(); 
                isCleared = false; 
        rectangleButton.select(); 
        selectedTool = RECTANGLE; 
    }

    void selectTriangle(){ 
        deselectAll(); 
                isCleared = false; 
        triangleButton.select();
        selectedTool = TRIANGLE;
    }

    void selectClear(){
        deselectAll();
        clearButton.select(); 
        selectedTool = CLEAR;
        isCleared = true; 
        pressedClear();
    }

    bool pressedClear(){
        return isCleared; 
    }

    void setClear (bool isCleared){
        this->isCleared = isCleared;
    }




    void handleMouseClick(float x, float y){
        if (pencilButton.contains(x, y)){
            selectPencil();
        } else if(eraserButton.contains(x,y)){
            selectEraser(); 
        } else if (mouseButton.contains(x, y)){
            selectMouse();
        } else if (squareButton.contains(x, y)){
            selectSquare();
        }else if (circleButton.contains(x, y)){
            selectCircle();
        }else if (rectangleButton.contains(x, y)){
            selectRectangle();
        }else if (triangleButton.contains(x, y)){
            selectTriangle();
        }else if (clearButton.contains(x, y)){
            selectClear();
        }
        else if(frontButton.contains(x,y)){
            selectFront(); 
        }
        else if(backButton.contains(x,y)){
            selectBack();  
        }
    }

    void draw(){
        area.draw();
        second_area.draw();
        pencilButton.draw();
        eraserButton.draw();
        squareButton.draw();
        circleButton.draw(); 
        rectangleButton.draw(); 
        mouseButton.draw(); 
        triangleButton.draw(); 
        clearButton.draw(); 
        frontButton.draw();
        backButton.draw(); 
    }

    bool contains(float x, float y){
        return (area.contains(x, y) || second_area.contains(x,y));
    }
};

#endif