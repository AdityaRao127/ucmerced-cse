#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "Rectangle.h"
#include "Texture.h"

enum Tool {PENCIL, ERASER};

struct Toolbar {
private:
    Rectangle area;
    Texture pencilButton;
    Texture eraserButton;
    Tool selectedTool;

    void deselectAll(){
        pencilButton.deselect();
        eraserButton.deselect();
    }

public:
    Toolbar(){
        area = Rectangle(-1.0f, 1.0f, 0.2f, 2.0f, Color(0.8f, 0.8f, 0.8f));
        pencilButton = Texture("assets/pencil.png", -1.0f, 1.0f, 0.2f, 0.2f);
        eraserButton = Texture("assets/eraser.png", -1.0f, 0.8f, 0.2f, 0.2f);

        selectPencil();
    }

    Tool getSelectedTool(){
        return selectedTool;
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

    void handleMouseClick(float x, float y){
        if (pencilButton.contains(x, y)){
            selectPencil();
        } else if (eraserButton.contains(x, y)){
            selectEraser();
        }
    }

    void draw(){
        area.draw();
        pencilButton.draw();
        eraserButton.draw();
    }

    bool contains(float x, float y){
        return area.contains(x, y);
    }
};

#endif