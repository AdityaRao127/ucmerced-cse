#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include "AppController.h"
#include "Rectangle.h"
#include "Button.h"

class Controller : public AppController {
    // State variables needed for you app

    Rectangle **r;
    // Rectangle r[5];
    int count;

    Button button3;
    Button button4;
    Button button5;

    void init(){

        r = new Rectangle*[count];
        for (int i = 0; i < count; i++){
            r[i] = new Rectangle[count];
        }

        float x = -0.9;
        float y = 0.9;

        float w = 1.8 / count;
        float h = 1.5 / count;
        // Initialize your state variables
        for (int i = 0; i < count; i++){
            x = -0.9;
            for (int j = 0; j < count; j++){
                r[i][j] = Rectangle(x, y, w, h);
                x += w;
            }
            y -= h;
        }
    }
public:
    Controller(){

        button3 = Button("3 x 3", -0.9, -0.75);
        button4 = Button("4 x 4", -0.5, -0.75);
        button5 = Button("5 x 5", -0.1, -0.75);

        count = 3;
        init();
        
    }

    void leftMouseDown( float x, float y ){
        // Respond to left mouse down events
        if (button3.contains(x, y)){
            std::cout << "Will change to 3x3" << std::endl;
            for (int i = 0; i < count; i++){
                delete[] r[i];
            }
            delete[] r;
            count = 3;
            init();
        }
        else if (button4.contains(x, y)){
            std::cout << "Will change to 4x4" << std::endl;
            for (int i = 0; i < count; i++){
                delete[] r[i];
            }
            delete[] r;
            count = 4;
            init();
        }
        else if (button5.contains(x, y)){
            std::cout << "Will change to 5x5" << std::endl;
            for (int i = 0; i < count; i++){
                delete[] r[i];
            }
            delete[] r;
            count = 5;
            init();
        }
    }

    void render() {
        // Render some graphics

        button3.draw();
        button4.draw();
        button5.draw();

        for (int i = 0; i < count; i++){
            for(int j = 0; j < count; j++){
                r[i][j].draw();
            }
        }
    }

};

#endif