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

class Controller : public AppController {
    Button* boxBtn;
    Button* ovalBtn;
    Button* diamondBtn;
    Button* delBtn;

    
    // Box* node; // we had this
    Node* node;   // now we have that

public:
    Controller(){
        // Initialize your state variables 
        boxBtn = new Button("Box", -0.9, -0.7);
        ovalBtn = new Button("Oval", -0.6, -0.7);
        diamondBtn = new Button("Diamond", -0.2, -0.7);
        delBtn = new Button("Delete", 0.2, -0.7);

        node = nullptr;   
    }

    void leftMouseDown( float x, float y ){
        if (y < -0.7){
            if (boxBtn->contains(x, y)){
                // std::cout << "Clicked box" << std::endl;
                if (node) delete node;
                node = new Box("UC Merced");
            }
            else if (delBtn->contains(x, y)){
                if (node) delete node;
                node = nullptr;
            }
            else if (ovalBtn->contains(x, y)){
                // std::cout << "Oval clicked" << std::endl;
                if (node) delete node;
                node = new Oval("UC Merced");
            }
            else if (diamondBtn->contains(x, y)){
                // std::cout << "Oval clicked" << std::endl;
                if (node) delete node;
                node = new Diamond("UC Merced");
            }
        }
        else{
            if (node){
                node->deselect();
                if (node->contains(x, y)){
                    node->select();
                }
            }
        }
    } 

    void mouseMotion( float x, float y ) {
        // Handle mouse motion
    }

    void render() {
        // Render some graphics

        if (node) node->draw();

        boxBtn->draw();
        delBtn->draw();
        ovalBtn->draw();
        diamondBtn->draw();
    }

    ~Controller(){
        delete boxBtn;
        delete delBtn;
        delete ovalBtn;
        delete diamondBtn;
        delete node;
    }

};

#endif