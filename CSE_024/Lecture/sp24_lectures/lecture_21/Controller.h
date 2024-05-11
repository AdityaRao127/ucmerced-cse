#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <new>
#include "AppController.h"
#include "Rectangle.h"
#include "Button.h"

class Controller : public AppController {
    Button* addBtn;

    // Rectangle r;
    Rectangle* r;
    // Rectangle* s;

public:
    Controller(){
        // Initialize your state variables 
        addBtn = new Button("Add", -0.9, -0.7);
        r = nullptr;
    }

    void leftMouseDown( float x, float y ){
        // if (r) {
        //     r->deselect();
        // }
        // if (r && r->neighbor) {
        //     r->neighbor->deselect();
        // }
        // if (r && r->neighbor && r->neighbor->neighbor){
        //     r->neighbor->neighbor->deselect();
        // }
        Rectangle* temp = r;
        while (temp != nullptr){
            temp->deselect();
            temp = temp->neighbor;
        }

        if (y < -0.7){
            if (addBtn->contains(x, y)){
                std::cout << "Clicked add" << std::endl;
                if (r == nullptr){
                    r = new Rectangle();
                }
                else {
                    // find the last rectangle
                    Rectangle* last = r;
                    while (last->neighbor != nullptr){
                        last = last->neighbor;
                    }
                    last->neighbor = new Rectangle();
                }
                // if (r == nullptr){
                //     r = new Rectangle();
                // }
                // else if (r->neighbor == nullptr) {
                //     r->neighbor = new Rectangle();
                // }
                // else if (r->neighbor->neighbor == nullptr){
                //     r->neighbor->neighbor = new Rectangle();
                // }
            }
        }
        else {
            Rectangle* temp = r;
            while (temp != nullptr){
                if (temp->contains(x, y)){
                    temp->select();
                    break;
                }
                temp = temp->neighbor;
            }
            // if (r && r->contains(x, y)){
            //     r->select();
            // }
            // else if(r && r->neighbor && r->neighbor->contains(x, y)){
            //     r->neighbor->select();
            // }
            // else if(r && r->neighbor && r->neighbor->neighbor && r->neighbor->neighbor->contains(x, y)){
            //     r->neighbor->neighbor->select();
            // }
        }
    } 

    void mouseMotion( float x, float y ) {
        if (y > -0.7){

            Rectangle* temp = r;
            while (temp != nullptr){
                if (temp->isSelected()){
                    temp->setX(x);
                    temp->setY(y);
                }
                temp = temp->neighbor;
            }
            // if (r && r->isSelected()){
            //     r->setX(x);
            //     r->setY(y);
            // }
            // else if (r && r->neighbor && r->neighbor->isSelected()){
            //     r->neighbor->setX(x);
            //     r->neighbor->setY(y);
            // }
            // else if (r && r->neighbor && r->neighbor->neighbor && r->neighbor->neighbor->isSelected()){
            //     r->neighbor->neighbor->setX(x);
            //     r->neighbor->neighbor->setY(y);
            // }
        }
    }

    void render() {
        // Render some graphics
 
        // if (r){ // if (r != nullptr){
        //     r->draw();
        // }
        // if (r && r->neighbor){
        //     r->neighbor->draw();
        //     glBegin(GL_LINES);
        //     glVertex2f(r->getX() + r->getW()/2, r->getY() - r->getH()/2);
        //     glVertex2f(r->neighbor->getX() + r->neighbor->getW()/2, r->neighbor->getY()- r->neighbor->getH()/2);
        //     glEnd();
        // }
        // if (r && r->neighbor && r->neighbor->neighbor){
        //     r->neighbor->neighbor->draw();
        //     glBegin(GL_LINES);
        //     glVertex2f(r->neighbor->getX() + r->neighbor->getW()/2, r->neighbor->getY()- r->neighbor->getH()/2);
        //     glVertex2f(r->neighbor->neighbor->getX() + r->neighbor->neighbor->getW()/2, r->neighbor->neighbor->getY()- r->neighbor->neighbor->getH()/2);
        //     glEnd();
        // }

        Rectangle* temp = r;
        while (temp != nullptr){
            temp->draw();
            temp = temp->neighbor;
        }

        addBtn->draw();

    }

};

#endif