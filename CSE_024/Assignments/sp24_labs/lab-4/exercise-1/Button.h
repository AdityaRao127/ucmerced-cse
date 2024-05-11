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

// for shapes
    Button(std::string text, float x, float y, float w){
        this->x = x; 
        this->y = y; 
        this->w = w; 
        down = false; 
        this->text=text; 
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


struct Triangle{
    float x1, y1, x2, y2, x3, y3, r, g, b; 

    Triangle(){
        x1 =0; 
        y1 = 0; 
        x2 = 0.1; 
        y2 = 0.1; 
        x3 = -0.1; 
        y3 = 0.1; 
        r = 1; 
        g = 1; 
        b = 1;
    }

    Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b){
        this->x1 = x1; 
        this->y1 = y1; 
        this->x2 = x2; 
        this->y2 = y2;
        this->x3 = x3; 
        this->r = r;
        this->g = g; 
        this->b = b; 
    }

    void draw(){
        glColor3f(r,g,b);
        glBegin(GL_TRIANGLES);

        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glVertex2f(x3,y3);

        glEnd(); 
    }

    void setColor(float r, float g, float b){
        this->r = r; 
        this->g = g; 
        this->b = b; 
    }

    //bool inside(float mx, float my){

    //}
};

struct Circle{
    float x, y, rad;
    float r, g, b;

    Circle(){
        x=0; 
        y=0; 
        rad = 0.1; 
        r=0; 
        g=0;
        b=0; 
    }
    
    Circle(float x, float y, float rad, float r, float g, float b){
        this->x = x; 
        this->y=y;
        this->rad = rad; 
        this->r = r;
        this->g = g; 
        this->b = b; 
    }

    
};

}; 

#endif