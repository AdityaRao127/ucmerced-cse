#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "AppController.h"
#include "Button.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Diamond.h"
#include "Shape.h"

class Controller : public AppController {
    Button* rBtn;
    Button* cBtn;
    Button* dBtn;

    Shape* r;
    Shape* c;
    Shape* d;

public:
    Controller(){
        // Initialize your state variables 
        rBtn = new Button("Rectangle", -0.9, -0.7);
        cBtn = new Button("  Circle  ", -0.4, -0.7);
        dBtn = new Button(" Diamond ", 0.15, -0.7);

        r = nullptr;
        c = nullptr;
        d = nullptr;
    }

    void leftMouseDown( float x, float y ){
        // Handle left mouse button down events
        if (rBtn->contains(x, y)){
            std::cout << "Rectangle" << std::endl;
            if (c){
                delete c;
                c = nullptr;
            } 
            if (d){
                delete d;
                d = nullptr;
            } 

            if (!r) r = new Rectangle();
        }
        else if (cBtn->contains(x, y)){
            std::cout << "Circle" << std::endl;
            if (r){
                delete r;
                r = nullptr;
            } 
            if (d){
                delete d;
                d = nullptr;
            } 

            if (!c) c = new Circle();
        }
        else if (dBtn->contains(x, y)){
            std::cout << "Diamond" << std::endl;
            if (c){
                delete c;
                c = nullptr;
            } 
            if (r){
                delete r;
                r = nullptr;
            } 

            if (!d) d = new Diamond();
        }
    } 

    void render() {
        // Render some graphics
        rBtn->draw();
        cBtn->draw();
        dBtn->draw();

        if (r) r->draw();
        if (c) c->draw();
        if (d) d->draw();
    }

    ~Controller(){
        // Free up any memory used by the app
        delete rBtn;
        delete cBtn;
        delete dBtn;

        if (r) delete r;
        if (c) delete c;
        if (d) delete d;
    }
};

#endif