#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include "Rectangle.h"

struct ColorSelector {
private:
    Rectangle area;
    Rectangle redButton;
    Rectangle greenButton;
    Rectangle blueButton;
    Color currentColor;

    void deselectAll(){
        redButton.deselect();
        greenButton.deselect();
        blueButton.deselect();
    }

public:
    ColorSelector(){
        area = Rectangle(-0.8f, -0.8f, 1.8f, 0.2f, Color(0.8f, 0.8f, 0.8f));
        redButton = Rectangle(-0.8f, -0.8f, 0.2f, 0.2f, Color(1.0f, 0.0f, 0.0f));
        greenButton = Rectangle(-0.6f, -0.8f, 0.2f, 0.2f, Color(0.0f, 1.0f, 0.0f));
        blueButton = Rectangle(-0.4f, -0.8f, 0.2f, 0.2f, Color(0.0f, 0.0f, 1.0f));

        setRed();
    }

    Color getCurrentColor(){
        return currentColor;
    }

    void setRed(){
        deselectAll();
        currentColor = Color(1.0f, 0.0f, 0.0f);
        redButton.select();
    }
    
    void setGreen(){
        deselectAll();
        currentColor = Color(0.0f, 1.0f, 0.0f);
        greenButton.select();
    }

    void setBlue(){
        deselectAll();
        currentColor = Color(0.0f, 0.0f, 1.0f);
        blueButton.select();
    }

    void handleMouseClick(float x, float y){
        if (redButton.contains(x, y)){
            setRed();
        }
        else if (greenButton.contains(x, y)){
            setGreen();
        }
        else if (blueButton.contains(x, y)){
            setBlue();
        }
    }

    void draw(){
        area.draw();
        redButton.draw();
        greenButton.draw();
        blueButton.draw();
    }

    bool contains(float x, float y){
        return area.contains(x, y);
    }
};

#endif