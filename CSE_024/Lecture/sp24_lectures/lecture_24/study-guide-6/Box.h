#ifndef BOX_H
#define BOX_H

#include "Node.h"
#include <iostream>

class Box : public Node{

public:

    Box() : Node(){
        // Additional init specific to Box
        std::cout << "Box()" << std::endl;
    }

    Box (std::string s) : Node(s){
        // Additional init specific to Box
        std::cout << "Box(std::string)" << std::endl;
    }

    void draw() {
        float textWidth = 0.0f;
        for (int i = 0; i < text.length(); i++) {
            textWidth += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text[i]);
        }
        float padding = 0.06;
        textWidth = 2.0f * (textWidth / 400.0);
        w = textWidth + padding;
        
        glColor3f(1.0f, 1.0f, 1.0f);
        if (pressed) glColor3f(0.8, 0.8, 0.8);
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x + w, y);

            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);

            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);

            glVertex2f(x, y - h);
            glVertex2f(x, y);
        glEnd();

     
        glRasterPos2f(x + (padding / 2), y - (h / 2) - 0.025);
        for (int i = 0; i < text.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
        }
    }

    ~Box(){
        std::cout << "~Box() " << std::endl;
    }

};

#endif