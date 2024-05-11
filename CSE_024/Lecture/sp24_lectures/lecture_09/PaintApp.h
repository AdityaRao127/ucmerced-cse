#ifndef PAINT_APP_H
#define PAINT_APP_H

#include <GL/freeglut.h>
#include "Rectangle.h"
#include "Button.h"
#include "Texture.h"
#include <iostream>

enum TOOL {PENCIL, ERASER};
enum COLOR {RED, GREEN, BLUE};

struct PaintApp {
    Rectangle verticalToolbar;
    Rectangle horizontalToolbar;
    Rectangle canvas;

    Rectangle redButton;
    Rectangle greenButton;
    Rectangle blueButton;

    Texture pencilButton;
    Texture eraserButton;

    Button clearButton;
    TOOL selectedTool;
    COLOR selectedColor;

    PaintApp() {
        verticalToolbar = Rectangle(-1.0f, 1.0f, 0.2f, 2.0f, Color(0.7f, 0.7f, 0.7f));
        horizontalToolbar = Rectangle(-0.8f, -0.8f, 1.8f, 0.2f, Color(0.7f, 0.7f, 0.7f));
        canvas = Rectangle(-0.8f, 1.0f, 1.8f, 1.8f, Color(0.9f, 0.9f, 0.9f));

        redButton = Rectangle(-0.8f, -0.8f, 0.2f, 0.2f, Color(1.0f, 0.0f, 0.0f));
        greenButton = Rectangle(-0.6f, -0.8f, 0.2f, 0.2f, Color(0.0f, 1.0f, 0.0f));
        blueButton = Rectangle(-0.4f, -0.8f, 0.2f, 0.2f, Color(0.0f, 0.0f, 1.0f));
        clearButton = Button("Clear", 0.7f, -0.8f);

        pencilButton = Texture("assets/pencil.png", -1.0f, 1.0f, 0.2f, 0.2f);
        eraserButton = Texture("assets/eraser.png", -1.0f, 0.8f, 0.2f, 0.2f);

        selectedTool = PENCIL;
        selectedColor = RED;
    }

    void init() {
        pencilButton.loadTexture();
        eraserButton.loadTexture();
    }

    void leftMouseDown(float x, float y) {
        if (pencilButton.isClicked(x, y)) {
            selectedTool = PENCIL;
        } else if (eraserButton.isClicked(x, y)) {
            selectedTool = ERASER;
        }

        if (redButton.isClicked(x, y)) {
            selectedColor = RED;
        } else if (greenButton.isClicked(x, y)) {
            selectedColor = GREEN;
        } else if (blueButton.isClicked(x, y)) {
            selectedColor = BLUE;
        }
    }

    void leftMouseUp(float x, float y) {
        // 
    }

    void rightMouseDown(float x, float y) {
        // 
    }

    void rightMouseUp(float x, float y) {
        // 
    }

    void mouseMotion(float x, float y) {
        // 
    }

    void keyboardDown(unsigned char key, float x, float y) {
        // 
    }

    void render() {
        if (selectedTool == PENCIL) {
            pencilButton.selected = true;
            eraserButton.selected = false;
        } else if (selectedTool == ERASER) {
            pencilButton.selected = false;
            eraserButton.selected = true;
        }

        if (selectedColor == RED) {
            redButton.selected = true;
            greenButton.selected = false;
            blueButton.selected = false;
        } else if (selectedColor == GREEN) {
            redButton.selected = false;
            greenButton.selected = true;
            blueButton.selected = false;
        } else if (selectedColor == BLUE) {
            redButton.selected = false;
            greenButton.selected = false;
            blueButton.selected = true;
        }

        canvas.draw();
        verticalToolbar.draw();
        horizontalToolbar.draw();

        redButton.draw();
        greenButton.draw();
        blueButton.draw();
        clearButton.draw();

        pencilButton.draw();
        eraserButton.draw();
    }
};

#endif