#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/gl.h>
#include <iostream>
#include "AppController.h"
#include "Rectangle.h"

class Controller : public AppController {
    Rectangle* rectangles[3];

public:
    Controller(){
        // Initialize your state variables 
        rectangles[0] = new Rectangle();
        rectangles[1] = new Rectangle(-0.8f, 0.6f, 0.4f, 0.2f, 1.0f, 0.0f, 0.0f);
        rectangles[2] = new Rectangle(-0.5f, -0.6f, 0.4f, 0.2f, 1.0f, 0.0f, 0.0f);
    }

    void leftMouseDown( float x, float y ){
        // Handle left mouse button down events
        for (int i = 0; i < 3; i++){
            if (rectangles[i]->contains(x, y)){
                rectangles[i]->setColor(0.0f, 1.0f, 0.0f);
            }
            else{
                rectangles[i]->setColor(1.0f, 0.0f, 0.0f);
            }
        }
        
    } 

    void render() {
        // Render some graphics
        for (int i = 0; i < 3; i++){
            rectangles[i]->draw();
        }
    }

    ~Controller(){
        for (int i = 0; i < 3; i++){
            delete rectangles[i];
        }
    }
};

#endif