#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <string>
#include "AppController.h"
#include "Button.h"
#include "Box.h"
#include "Node.h"
#include "Oval.h"
#include "Diamond.h"
#include "Texture.h"

class Controller : public AppController {
    Button* boxBtn;
    Button* ovalBtn;
    Button* diamondBtn;
    Texture* selectBtn;

    Node** node; 
    int count;
    int capacity;

    Node* selected;
    Node* src;

    float cx;
    float cy;

    void inflate(){

        if (count == capacity){
            capacity *= 2;

            Node** temp = new Node*[capacity];

            for (int i = 0; i < count; i++){
                temp[i] = node[i];
            }

            Node** old = node;
            node = temp;
            delete[] old;
        }
    }

public:
    Controller(){
        // Initialize your state variables 
        boxBtn = new Button("Box", -0.9, -0.7);
        ovalBtn = new Button("Oval", -0.6, -0.7);
        diamondBtn = new Button("Diamond", -0.25, -0.7);
        selectBtn = new Texture("assets/mouse.png", 0.6, -0.7, 0.2, 0.2);
        selectBtn->selected = false;

        count = 0;
        capacity = 1;
        node = new Node*[capacity]; 
        selected = nullptr;

        src = nullptr;
        cx = 0;
        cy = 0;
    }

    void leftMouseDown( float x, float y ){
        if (y < -0.7){
            if (boxBtn->contains(x, y)){
                // std::cout << "Clicked box" << std::endl;
                node[count] = new Box("Box");
                count++;
                inflate();
            }
            else if (ovalBtn->contains(x, y)){
                // std::cout << "Oval clicked" << std::endl;
                
                node[count] = new Oval("Oval");
                count++;
                inflate();
            }
            else if (diamondBtn->contains(x, y)){
                // std::cout << "Oval clicked" << std::endl;
                node[count] = new Diamond("Diamond");
                count++;
                inflate();
            }
            else if (selectBtn->contains(x, y)){
                selectBtn->selected = !selectBtn->selected;
            }
        }
        else{
            for (int i = 0; i < count; i++){
                node[i]->deselect();
            }
            selected = nullptr;

            if (selectBtn->selected){
                for (int i = 0; i < count; i++){
                    if (node[i]->contains(x, y)){
                        node[i]->select();
                        selected = node[i];
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < count; i++){
                    if (node[i]->contains(x, y)){
                        node[i]->select();
                        src = node[i];
                        cx = src->getX()+src->getW()/2;
                        cy = src->getY()-src->getH()/2;
                        break;
                    }
                }
            }
        }
    } 

    void mouseMotion( float x, float y ) {
        // Handle mouse motion
        if (y > -0.7){
            if (selectBtn->selected){
                for (int i = 0; i < count; i++){
                    if (node[i]->isSelected()){
                        node[i]->setX(x);
                        node[i]->setY(y);
                        break;
                    }
                }
            }
            else{
                cx = x;
                cy = y;
            }

        }
    }

    void leftMouseUp( float x, float y ) {
        if (src){
            for (int i = 0; i < count; i++){
                if (node[i]->contains(x, y)){
                    node[i]->addNeighbor(src);
                    break;
                }
            }

            src = nullptr;
        }

    }

    void render() {
        // Render some graphics

        if (src){
            glColor3f(0,0,0);
            glBegin(GL_LINES);

            glVertex2f(src->getX()+src->getW()/2, src->getY()-src->getH()/2);
            glVertex2f(cx, cy);

            glEnd();
        }


        for(int i = 0; i < count; i++){
            node[i]->connect();
        }

        for(int i = 0; i < count; i++){
            node[i]->draw();
        }

        boxBtn->draw();
        ovalBtn->draw();
        diamondBtn->draw();
        
        selectBtn->draw();
    }

    ~Controller(){
        delete boxBtn;
        delete ovalBtn;
        delete diamondBtn;
        delete selectBtn;

        for (int i = 0; i < count; i++){
            delete node[i];
        }
        delete[] node;
    }

};

#endif