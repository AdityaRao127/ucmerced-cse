#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/gl.h>
#include <iostream>
#include "AppController.h"
#include "Rectangle.h"

class Controller : public AppController {
    Rectangle* rectangle;

public:
    Controller(){
        // Initialize your state variables 
        rectangle = new Rectangle(0.0f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
    }

    void leftMouseDown( float x, float y ){
        // Handle left mouse button down events
        if (rectangle->contains(x, y)){
            rectangle->setW(0.8);
        }
        else{
            rectangle->setW(0.5);
        }
    } 

    void render() {
        // Render some graphics
        rectangle->draw();
    }

    ~Controller(){
        delete rectangle;
    }
};

#endif