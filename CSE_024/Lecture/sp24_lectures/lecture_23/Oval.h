#ifndef OVAL_H
#define OVAL_H

#include <GL/gl.h>
#include <cmath>
#include "Node.h"

class Oval : public Node{
public:
    Oval() : Node(){
        std::cout << "Oval()" << std::endl;
    }

    Oval(std::string s) : Node(s){
        std::cout << "Oval(std::string)" << std::endl;
    }

    void draw() {

        float textWidth = 0.0f;
        for (int i = 0; i < text.length(); i++) {
            textWidth += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text[i]);
        }
        float padding = 0.06;
        textWidth = 2.0f * (textWidth / 400.0);
        w = textWidth + padding;

        float inc = (2*M_PI)/60;
        float a = w/2;
        float b = h/2;
        
        glColor3f(1.0f, 1.0f, 1.0f);
        if (pressed) glColor3f(0.8, 0.8, 0.8);
        glBegin(GL_POLYGON);
        for (float theta = 0; theta <= 2*M_PI; theta += inc){
            glVertex2f(a * cos(theta) + x + a, b * sin(theta) + y - b);        
        }
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);

        
        glBegin(GL_LINES);

        for (float theta = 0; theta < 2*M_PI; theta += inc){
            glVertex2f(a * cos(theta) + x + a, b * sin(theta) + y - b);
            glVertex2f(a * cos(theta+inc) + x + a, b * sin(theta+inc) + y - b);
        }

        glEnd();

     
        glRasterPos2f(x + (padding / 2), y - (h / 2) - 0.025);
        for (int i = 0; i < text.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
        }
    }

    ~Oval(){
        std::cout << "~Oval()" << std::endl;
    }
};

#endif