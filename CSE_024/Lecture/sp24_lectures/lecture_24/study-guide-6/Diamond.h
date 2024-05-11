#ifndef DIAMOND_H
#define DIAMOND_H

#include <GL/gl.h>
#include "Node.h"

class Diamond : public Node{
public:
    Diamond() : Node(){
        std::cout << "Diamond()" << std::endl;
    }

    Diamond(std::string s) : Node(s){
        std::cout << "Diamond(std::string)" << std::endl;
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
        // Selected

        glVertex2f(x - padding, y - h/2);
        glVertex2f(x + w/2, y);
        glVertex2f(x + w + padding, y - h/2);
        glVertex2f(x + w/2, y - h);

        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);

        
        glBegin(GL_LINES);
        // Outline

        glVertex2f(x - padding, y - h/2);
        glVertex2f(x + w/2, y);

        glVertex2f(x + w/2, y);
        glVertex2f(x + w + padding, y - h/2);

        glVertex2f(x + w + padding, y - h/2);
        glVertex2f(x + w/2, y - h);

        glVertex2f(x + w/2, y - h);
        glVertex2f(x - padding, y - h/2);

        glEnd();

     
        glRasterPos2f(x + (padding / 2), y - (h / 2) - 0.025);
        for (int i = 0; i < text.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
        }
    }

    ~Diamond(){
        std::cout << "~Diamond()" << std::endl;
    }
};

#endif