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
    Button* addBtn;
    Button* delBtn;
    Button* copyBtn;

    Box* r;
    Box* c;

    float offsetX;
    float offsetY;

    int count;

public:
    Controller(){
        // Initialize your state variables 
        addBtn = new Button("Add", -0.9, -0.7);
        delBtn = new Button("Delete", -0.6, -0.7);
        copyBtn = new Button("Copy", -0.2, -0.7);
        r = nullptr;
        c = nullptr;
        offsetX = 0;
        offsetY = 0;
        count = 0;
    }

    void leftMouseDown( float x, float y ){
        if (y < -0.7){
            if (addBtn->contains(x, y)){
                std::cout << "Clicked add" << std::endl;
                count++;
                if (r == nullptr){
                    r = new Box(std::to_string(count));
                }
                else {
                    // find the last box
                    Box* last = r;
                    while (last->neighbor != nullptr){
                        last = last->neighbor;
                    }
                    last->neighbor = new Box(std::to_string(count));
                }
            }
            else if (delBtn->contains(x, y)){
                std::cout << "Clicked delete" << std::endl;
                
                delete r;
                
                r = nullptr;
            }
            else if (copyBtn->contains(x, y)){
                std::cout << "Clicked copy" << std::endl;

                if (r){
                    // c = r;
                    c = new Box(*r);
                    // c->setText(c->getText() + " copy");
                    // c->setX(-0.8);
                    // c->setY(-0.5);

                }

            }
        }
        else {
            Box* temp = r;
            while (temp != nullptr){
                temp->deselect();
                temp = temp->neighbor;
            }
            
            temp = r;
            while (temp != nullptr){
                if (temp->contains(x, y)){
                    temp->select();
                    offsetX = x - temp->getX();
                    offsetY = temp->getY() - y;
                    break;
                }
                temp = temp->neighbor;
            }
        }
    } 

    void mouseMotion( float x, float y ) {
        if (y > -0.7){

            Box* temp = r;
            while (temp != nullptr){
                if (temp->isSelected()){
                    temp->setX(x - offsetX);
                    temp->setY(y + offsetY);
                }
                temp = temp->neighbor;
            }
        }
    }

    void render() {
        // Render some graphics

        Box* temp = r;
        while (temp != nullptr){
            temp->draw();
            temp = temp->neighbor;
        }

        temp = c;
        while (temp != nullptr){
            temp->draw();
            temp = temp->neighbor;
        }

        addBtn->draw();
        delBtn->draw();
        copyBtn->draw();
    }

};

#endif