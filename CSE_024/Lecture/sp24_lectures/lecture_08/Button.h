#ifndef BUTTON_H
#define BUTTON_H

#include <GL/freeglut.h>
#include <string>

struct Button{
    float x;
    float y;

    float w;
    float h;

    std::string text;

    bool down;

    Button(){
        x = 0;
        y = 0;
        h = 0.2;
        w = 0.2;

        down = false;

        text = "Click here";
    }

    Button(std::string text){
        x = 0;
        y = 0;
        h = 0.2;
        w = 0.2;

        down = false;

        this->text = text;
    }

    Button(std::string text, float x, float y){
        this->x = x;
        this->y = y;
        h = 0.2;
        w = 0.2;

        down = false;

        this->text = text;
    }

    void render(){

        int width = 0;
        for (int i = 0; i < text.length(); i++){
            width += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text[i]);
        }

        w = width * 2/400.0 + 0.06;
    
        if (down){
            glColor3f(0.8,0.8,0.8);
        }
        else{
            glColor3f(0.9, 0.9, 0.9);
        }
        glBegin(GL_POLYGON);
        
        glVertex2f(x, y);
        glVertex2f(x+w, y);
        glVertex2f(x+w, y-h);
        glVertex2f(x, y-h);

        glEnd();

        glLineWidth(1);
        glColor3f(0,0,0);
        glBegin(GL_LINES);
        
        glVertex2f(x, y);
        glVertex2f(x+w, y);

        glVertex2f(x+w, y);
        glVertex2f(x+w, y-h);

        glVertex2f(x+w, y-h);
        glVertex2f(x, y-h);

        glVertex2f(x, y-h);
        glVertex2f(x, y);

        glEnd();

        glColor3f(0,0,0);
        if (down){
            glRasterPos2f(x+0.025, y-h+0.055);
        }
        else{
            glRasterPos2f(x+0.03, y-h+0.07);
        }
        unsigned char* caption = (unsigned char*) text.c_str();
        glutBitmapString(GLUT_BITMAP_9_BY_15, caption);
    }

    bool inside(float px, float py){
        return (px >= x && px <= x + w) && (py <= y && py >= y - h) ;
    }
};

#endif