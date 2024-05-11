#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include "Rectangle.h"

class ColorSelector {
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

        redButton.select();
        currentColor.setRed();
    }

    // getters
    Color getCurrentColor() {
        return currentColor;
    }

    void handleMouseClick(float x, float y){
        if (redButton.contains(x, y)){
            deselectAll();
            redButton.select();
            currentColor.setRed();
        }
        else if (greenButton.contains(x, y)){
            deselectAll();
            greenButton.select();
            currentColor.setGreen();
        }
        else if (blueButton.contains(x, y)){
            deselectAll();
            blueButton.select();
            currentColor.setBlue();
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