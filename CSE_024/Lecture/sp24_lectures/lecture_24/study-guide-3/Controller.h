#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "AppController.h"
#include "Point.h"

class Controller : public AppController {

    Point* p[100];
    int counter;

public:
    Controller(){
        // Initialize your state variables 
        counter = 0;
    }

    void leftMouseDown( float x, float y ){
        // Handle left mouse button down events
        if (counter < 100){
            p[counter] = new Point(x, y, 1.0f, 0.0f, 0.0f, 8);
            counter++;
        }
    } 

    void mouseMotion( float x, float y ){
        // Handle left mouse button down events
        if (counter < 100){
            p[counter] = new Point(x, y, 1.0f, 0.0f, 0.0f, 8);
            counter++;
        }
    } 

    void render() {
        // Render some graphics
        for (int i = 0; i < counter; i++){
            p[i]->draw();
        }
    }

    ~Controller(){

        // Free up any memory used by the app
        for (int i = 0; i < counter; i++){
            delete p[i];
        }
    }
};

#endif