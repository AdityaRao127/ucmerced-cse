#ifndef BOX_H
#define BOX_H

#include "Button.h"
#include <iostream>

class Box : public Button{

public:

    Box* neighbor;

    Box(){
        neighbor = nullptr;
        text = " X ";
        float textWidth = 0.0f;
        for (int i = 0; i < text.length(); i++) {
            textWidth += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text[i]);
        }
        float padding = 0.06;
        textWidth = 2.0f * (textWidth / 400.0);
        w = textWidth + padding;
    }

    Box (std::string text){
        neighbor = nullptr;
        this->text = text;
        float textWidth = 0.0f;
        for (int i = 0; i < text.length(); i++) {
            textWidth += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text[i]);
        }
        float padding = 0.06;
        textWidth = 2.0f * (textWidth / 400.0);
        w = textWidth + padding;
    }

    Box(const Box& other){
        x = other.x;
        y = other.y;
        w = other.w;
        h = other.h;
        text = other.text;
        pressed = other.pressed;

        neighbor = nullptr;

        Box* temp = other.neighbor;
        Box* curr = this;

        while (temp != nullptr){
            curr->neighbor = new Box();
            curr->neighbor->x = temp->x;
            curr->neighbor->y = temp->y;
            curr->neighbor->w = temp->w;
            curr->neighbor->h = temp->h;
            curr->neighbor->text = temp->text;
            curr->neighbor->pressed = temp->pressed;
            
            curr = curr->neighbor;
            temp = temp->neighbor;
        }

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

    void draw(){
        if (neighbor){
            glColor3f(0,0,0);
            glBegin(GL_LINES);
            glVertex2f(x + w/2, y - h/2);
            glVertex2f(neighbor->x + neighbor->w/2, neighbor->y - neighbor->h/2);
            glEnd();
        }
        Button::draw();
    }

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

    ~Box(){
        std::cout << "Deleting " << text << std::endl;
        if (neighbor){
            delete neighbor;
        }
    }

};

#endif