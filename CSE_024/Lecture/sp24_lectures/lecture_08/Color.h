#ifndef COLOR_H
#define COLOR_H


struct Color{
    float r;
    float g;
    float b;

    Color(){
        r = 1;
        g = 0;
        b = 0;
    }

    Color (float r, float g, float b){
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void setRed(){
        r = 1;
        g = 0;
        b = 0;
    }

    void setGreen(){
        r = 0;
        g = 1;
        b = 0;
    }

    void set(float r, float g, float b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

#endif