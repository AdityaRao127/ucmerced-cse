#ifndef NODE_H
#define NODE_H

#include <GL/gl.h>
#include <iostream>
#include "Button.h"

class Node : public Button{
protected:
    Node** neighbors;
    int degree;
    int capacity;

    

public:

    void connect(){
        for (int i = 0; i < degree; i++){
            Node* curr = neighbors[i];
            glColor3f(0,0,0);
            glBegin(GL_LINES);
            glVertex3f(x + w/2, y - h/2, 0.1);
            glVertex3f(curr->x + curr->w/2, curr->y - curr->h/2, 0.1);
            glEnd();
        }
    }
    
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
        degree = 0;
        capacity = 1;
        neighbors = new Node*[capacity];
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
        degree = 0;
        capacity = 1;
        neighbors = new Node*[capacity];
    }

    void addNeighbor(Node* v){
        neighbors[degree] = v;
        degree++;

        if (degree == capacity){
            capacity *= 2;
            Node** temp = new Node*[capacity];
            for (int i = 0; i < degree; i++){
                temp[i] = neighbors[i];
            }

            Node** old = neighbors;
            neighbors = temp;
            // for (int i = 0; i < degree; i++){
            //     delete old[i];
            // }
            delete[] old;
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

    float getW(){
        return w;
    }

    float getH(){
        return h;
    }

    void setText(std::string text){
        this->text = text;
    }

    std::string getText(){
        return text;
    }

    virtual ~Node(){
        std::cout << "~Node()" << std::endl;
        delete[] neighbors;
    }

};


#endif