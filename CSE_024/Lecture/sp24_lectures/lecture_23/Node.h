#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "Button.h"

class Node : public Button{

public:
    Node(){
        std::cout << "Node()" << std::endl;
        text = "Node";
        float textWidth = 0.0f;
        for (int i = 0; i < text.length(); i++) {
            textWidth += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text[i]);
        }
        float padding = 0.06;
        textWidth = 2.0f * (textWidth / 400.0);
        w = textWidth + padding;
    }

    Node (std::string text){
        std::cout << "Node(std::string)" << std::endl;
        this->text = text;
        float textWidth = 0.0f;
        for (int i = 0; i < text.length(); i++) {
            textWidth += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text[i]);
        }
        float padding = 0.06;
        textWidth = 2.0f * (textWidth / 400.0);
        w = textWidth + padding;
    }

    bool isSelected(){
        return pressed;
    }

    void select(){
        pressed = true;
    }

    void deselect(){
        pressed = false;
    }

    virtual void draw() = 0;

    void setX(float x){
        this->x = x;
    }

    void setY(float y){
        this->y = y;
    }

    float getX(){
        return x;
    }

    float getY(){
        return y;
    }

    void setText(std::string text){
        this->text = text;
    }

    std::string getText(){
        return text;
    }

    virtual ~Node(){
        std::cout << "~Node()" << std::endl;
    }

};


#endif