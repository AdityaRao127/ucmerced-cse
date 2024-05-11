#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "AppController.h"
#include "Button.h"
#include "Rectangle.h"

class Controller : public AppController {
    Button* addBtn;
    Rectangle* r;
    float currX;
    float currY;

public:
    Controller(){
        // Initialize your state variables 
        addBtn = new Button("Add", -0.9, -0.7);
        r = nullptr;
        currX = -0.85;
        currY = 0.9;
    }

    void leftMouseDown( float x, float y ){
        // Handle left mouse button down events
        if (addBtn->contains(x, y)){
            if (!r){
                r = new Rectangle(currX, currY, 0.2, 0.2, 1, 0, 0);
            }
            else {
                Rectangle* temp = r;
                while (temp->neighbor != nullptr){
                    temp = temp->neighbor;
                }
                temp->neighbor = new Rectangle(currX, currY, 0.2, 0.2, 1, 0, 0);
            }
            currX += 0.25;
            if (currX >= 0.85){
                currX = -0.85;
                currY -= 0.25;
            }
        }
    } 

    void render() {
        // Render some graphics
        addBtn->draw();
        
        Rectangle* temp = r;
        while (temp){
            temp->draw();
            temp = temp->neighbor;
        }
    }

    ~Controller(){
        // Free up any memory used by the app
        delete addBtn;
        if (r){
            delete r;
        }
    }
};

#endif