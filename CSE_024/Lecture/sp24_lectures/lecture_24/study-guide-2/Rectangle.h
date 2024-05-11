#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/gl.h>
#include <GL/freeglut.h>
#include <string>
#include <cmath>

class Rectangle{
    float x;
    float y;
    float w;
    float h;
    float r;
    float g;
    float b;
    float area;

    void displayArea(){
        float textWidth = 0.0f;
        std::string text = std::to_string(area);
        text.erase ( text.find_last_not_of('0') + 1, std::string::npos );
        text.erase ( text.find_last_not_of('.') + 1, std::string::npos );
        for (int i = 0; i < text.length(); i++) {
            textWidth += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text[i]);
        }
        
        glColor3d(0.0f, 0.0f, 0.0f);
        textWidth = 2.0f * (textWidth / 400.0f);
        float padding = (w - textWidth) / 2.0f;
        glRasterPos2f(x + padding, y - (h / 2.0f) - 0.025f);
        for (int i = 0; i < text.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
        }
    }

public:
    Rectangle(){
        x = 0.0f;
        y = 0.0f;
        w = 0.4f;
        h = 0.2f;
        r = 1.0f;
        g = 0.0f;
        b = 0.0f;
        area = 0.08f;
    }

    Rectangle(float x, float y, float w, float h, float r, float g, float b){
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->r = r;
        this->g = g;
        this->b = b;
        area = w * h;
    }

    void draw(){
        glColor3f(r, g, b);

        glBegin(GL_POLYGON);

            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);

        glEnd();

        displayArea();
    }

    void setW(float w){
        this->w = w;
        area = w * h;
    }

    void setH(float h){
        this->h = h;
        area = w * h;
    }

    void setX(float x){
        this->x = x;
    }

    void setY(float y){
        this->y = y;
    }

    float getW(){
        return w;
    }

    float getH(){
        return h;
    }

    float getX(){
        return x;
    }

    float getY(){
        return y;
    }


    void setColor(float r, float g, float b){
        this->r = r;
        this->g = g;
        this->b = b;
    }

    bool contains(float mx, float my){
        return mx >= x && mx <= x + w && my <= y && my >= y - h;
    }
};

#endif