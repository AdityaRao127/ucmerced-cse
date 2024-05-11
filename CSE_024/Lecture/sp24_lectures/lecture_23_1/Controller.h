#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <string>
#include "AppController.h"
#include "Button.h"
#include "Box.h"

class Controller : public AppController {
    Button* boxBtn;

    Box* box;

public:
    Controller(){
        // Initialize your state variables 
        boxBtn = new Button("Box", -0.9, -0.7);

        box = nullptr;   
    }

    void leftMouseDown( float x, float y ){
        if (y < -0.7){
            if (boxBtn->contains(x, y)){
                // std::cout << "Clicked box" << std::endl;
                if (box) delete box;
                box = new Box("Hello World");
            }
        }
        else{
            if (box){
                box->deselect();
                if (box->contains(x, y)){
                    box->select();
                }
            }
        }
    } 

    void mouseMotion( float x, float y ) {
        // Handle mouse motion
    }

    void render() {
        // Render some graphics

        if (box) box->draw();

        boxBtn->draw();
    }

    ~Controller(){
        delete boxBtn;
        delete box;
    }

};

#endif