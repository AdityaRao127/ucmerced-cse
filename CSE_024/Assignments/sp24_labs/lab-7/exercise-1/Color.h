#ifndef COLOR_H
#define COLOR_H

#include <GL/freeglut.h>

struct Color {
private:
    float r;
    float g;
    float b;

public:
    Color() {
        r = 1.0f;
        g = 0.0f;
        b = 0.0f;
    }

    Color(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void setColor(float r, float g, float b) { // other function is 'set" from lab4
        this->r = r;
        this->g = g;
        this->b = b;
    } 

    void setRed(Color color){
        color = Color(1.0f, 0.0f, 0.0f);
    }
    
    void setGreen(Color color){
        color = Color(0.0f, 1.0f, 0.0f);
    }

    void setBlue(Color color){
        color = Color(0.0f, 0.0f, 1.0f);
    }

    void setViolet(Color color){
        color = Color(0.58, 0.0, 0.827);
    }

    void setOrange(Color color){
        color = Color(1, 0.647, 0);
    }

    void setYellow(Color color){
        color = Color(0,0,1);
    }

    void noColor(Color color){
        color = Color(0,0,0);
    }

    float getR() {
        return r;
    }

    float getG() {
        return g;
    }

    float getB() {
        return b;
    }
};


#endif