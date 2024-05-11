#ifndef PAINT_APP_H
#define PAINT_APP_H

#include <GL/freeglut.h>
#include "Rectangle.h"
#include "Button.h"
#include "Texture.h"
#include "Point.h"
#include <iostream>

enum TOOL {PENCIL, ERASER, SQUARE, MOUSE};
enum COLOR {RED, GREEN, BLUE};

struct PaintApp {
    Rectangle verticalToolbar;
    Rectangle horizontalToolbar;
    Rectangle canvas;

    Rectangle redButton;
    Rectangle greenButton;
    Rectangle blueButton;

    Texture mouseButton;
    Texture pencilButton;
    Texture eraserButton;
    Texture squareButton;

    Button clearButton;
    TOOL selectedTool;
    COLOR selectedColor;
    Color currentColor;

    Point points[10000];
    int pCounter;

    Rectangle squares[1000];
    int sCounter;
    int selectedSquare;
    float offsetX;
    float offsetY;

    PaintApp() {
        verticalToolbar = Rectangle(-1.0f, 1.0f, 0.2f, 2.0f, Color(0.7f, 0.7f, 0.7f));
        horizontalToolbar = Rectangle(-0.8f, -0.8f, 1.8f, 0.2f, Color(0.7f, 0.7f, 0.7f));
        canvas = Rectangle(-0.8f, 1.0f, 1.8f, 1.8f, Color(0.9f, 0.9f, 0.9f));

        redButton = Rectangle(-0.8f, -0.8f, 0.2f, 0.2f, Color(1.0f, 0.0f, 0.0f));
        greenButton = Rectangle(-0.6f, -0.8f, 0.2f, 0.2f, Color(0.0f, 1.0f, 0.0f));
        blueButton = Rectangle(-0.4f, -0.8f, 0.2f, 0.2f, Color(0.0f, 0.0f, 1.0f));
        clearButton = Button("Clear", 0.7f, -0.8f);

        mouseButton = Texture("assets/mouse.png", -1.0f, 1.0f, 0.2f, 0.2f);
        pencilButton = Texture("assets/pencil.png", -1.0f, 0.8f, 0.2f, 0.2f);
        eraserButton = Texture("assets/eraser.png", -1.0f, 0.6f, 0.2f, 0.2f);
        squareButton = Texture("assets/square.png", -1.0f, 0.4f, 0.2f, 0.2f);

        selectedTool = PENCIL;
        selectedColor = RED;
        currentColor.setRed();

        pCounter = 0;
        sCounter = 0;
        selectedSquare = -1;
        offsetX = 0;
        offsetY = 0;
    }

    void init() {
        mouseButton.loadTexture();
        pencilButton.loadTexture();
        eraserButton.loadTexture();
        squareButton.loadTexture();
    }

    void leftMouseDown(float x, float y) {
        if (pencilButton.isClicked(x, y)) {
            selectedTool = PENCIL;
        } else if (eraserButton.isClicked(x, y)) {
            selectedTool = ERASER;
        } else if (squareButton.isClicked(x, y)) {
            selectedTool = SQUARE;
        } else if (mouseButton.isClicked(x, y)) {
            selectedTool = MOUSE;
        } 

        if (redButton.isClicked(x, y)) {
            selectedColor = RED;
            currentColor.setRed();
        } else if (greenButton.isClicked(x, y)) {
            selectedColor = GREEN;
            currentColor.setGreen();
        } else if (blueButton.isClicked(x, y)) {
            selectedColor = BLUE;
            currentColor.setBlue();
        }

        if (canvas.isClicked(x, y)){
            if (selectedTool == PENCIL){
                // Draw the point there
                points[pCounter] = Point(x, y, currentColor);
                pCounter++;
            }
            else if (selectedTool == ERASER){
                // Implement what should happen for ERASER
            }
            else if (selectedTool == SQUARE){
                // Plase a square of the correct color
                // at the coordinates of the click

                squares[sCounter] = Rectangle(x, y, 0.3f, 0.3f, currentColor);
                sCounter++;
            }
            else if (selectedTool == MOUSE){
                // Check if the mouse pointer falls
                // inside a rectangle, and if so,
                // select it
                for (int i = 0; i < sCounter; i++){
                    squares[i].selected = false;
                }

                selectedSquare = -1;

                for (int i = sCounter-1; i >= 0; i--){
                    if (squares[i].isClicked(x, y)){
                        squares[i].selected = true;
                        selectedSquare = i;
                        offsetX = x - squares[i].x;
                        offsetY = squares[i].y - y;
                        break;
                    }
                }
            }
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
        if (canvas.isClicked(x, y)){
            // Draw the point there
            if (selectedTool == PENCIL){
                points[pCounter] = Point(x, y, currentColor);
                pCounter++;
            }
            else if(selectedTool == MOUSE) {
                if (selectedSquare >= 0){
                    squares[selectedSquare].x = x - offsetX;
                    squares[selectedSquare].y = y + offsetY;
                }
            }
        }
    }

    void keyboardDown(unsigned char key, float x, float y) {
        // 
    }

    void render() {
        if (selectedTool == PENCIL) {
            mouseButton.selected = false;
            pencilButton.selected = true;
            eraserButton.selected = false;
            squareButton.selected = false;
        } else if (selectedTool == ERASER) {
            mouseButton.selected = false;
            pencilButton.selected = false;
            eraserButton.selected = true;
            squareButton.selected = false;
        } else if (selectedTool == SQUARE) {
            mouseButton.selected = false;
            pencilButton.selected = false;
            eraserButton.selected = false;
            squareButton.selected = true;
        } else if (selectedTool == MOUSE) {
            mouseButton.selected = true;
            pencilButton.selected = false;
            eraserButton.selected = false;
            squareButton.selected = false;
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

        for (int i = 0; i < pCounter; i++){
            points[i].draw();
        }

        for (int i = 0; i < sCounter; i++){
            squares[i].draw();
        }


        verticalToolbar.draw();
        horizontalToolbar.draw();

        redButton.draw();
        greenButton.draw();
        blueButton.draw();
        clearButton.draw();

        mouseButton.draw();
        pencilButton.draw();
        eraserButton.draw();
        squareButton.draw();
    }
};

#endif