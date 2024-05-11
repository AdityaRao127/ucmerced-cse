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


    // give each color a function, so dont have to define rgb every time

    void setYellow(){
        r= 1; 
        g = 1;
        b= 0;
    }

    void setBlue(){
        r = 0;
        g= 0; 
        b = 1; 
    }

    void setOrange(){
        r=1;
        g = 0.647; 
        b = 0;
    }

    void setGreen(){
        r = 0; 
        g = 0.502; 
        b = 0; 
    }
    
    void setViolet(){
        r = 0.58; 
        g = 0.0; 
        b = 0.827; 
    }

    void noColor(){
        r = 0;
        g= 0; 
        b =0;
    }

    void set(float r, float g, float b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

#endif