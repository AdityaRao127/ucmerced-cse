#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "Rectangle.h"
#include "Texture.h"

enum Tool {PENCIL, ERASER, SQUARE, MOUSE, CIRCLE};

class Toolbar {
    Rectangle area;
    Texture mouseButton;
    Texture pencilButton;
    Texture eraserButton;
    Texture squareButton;
    Texture circleButton;
    Tool selectedTool;

    void deselectAll(){
        mouseButton.deselect();
        pencilButton.deselect();
        eraserButton.deselect();
        squareButton.deselect();
        circleButton.deselect();
    }

public:
    Toolbar(){
        area = Rectangle(-1.0f, 1.0f, 0.2f, 2.0f, Color(0.8f, 0.8f, 0.8f));
        mouseButton = Texture("assets/mouse.png", -1.0f, 1.0f, 0.2f, 0.2f);
        pencilButton = Texture("assets/pencil.png", -1.0f, 0.8f, 0.2f, 0.2f);
        eraserButton = Texture("assets/eraser.png", -1.0f, 0.6f, 0.2f, 0.2f);
        squareButton = Texture("assets/square.png", -1.0f, 0.4f, 0.2f, 0.2f);
        circleButton = Texture("assets/circle.png", -1.0f, 0.2f, 0.2f, 0.2f);

        selectedTool = PENCIL;
        pencilButton.select();
    }

    // getters
    Tool getSelectedTool() {
        return selectedTool;
    }

    // setters
    void selectMouse() {
        deselectAll();
        mouseButton.select();
        selectedTool = MOUSE;
    }

    void selectPencil() {
        deselectAll();
        pencilButton.select();
        selectedTool = PENCIL;
    }

    void selectEraser() {
        deselectAll();
        eraserButton.select();
        selectedTool = ERASER;
    }

    void selectSquare() {
        deselectAll();
        squareButton.select();
        selectedTool = SQUARE;
    }

    void selectCircle() {
        deselectAll();
        circleButton.select();
        selectedTool = CIRCLE;
    }

    void handleMouseClick(float x, float y){
        if (mouseButton.contains(x, y)){
            selectMouse();
        }
        else if (pencilButton.contains(x, y)){
            selectPencil();
        }
        else if (eraserButton.contains(x, y)){
            selectEraser();
        }
        else if (squareButton.contains(x, y)){
            selectSquare();
        }
        else if (circleButton.contains(x, y)){
            selectCircle();
        }
    }

    void draw(){
        area.draw();
        mouseButton.draw();
        pencilButton.draw();
        eraserButton.draw();
        squareButton.draw();
        circleButton.draw();
    }

    bool contains(float x, float y){
        return area.contains(x, y);
    }
};

#endif