    #ifndef TRIANGLE_H
    #define TRIANGLE_H

#include <cmath>
#include <GL/freeglut.h>
#include "Color.h"
#include "Shape.h"

class Triangle : public Shape{
        float x2, y2, x3, y3;

        public: 
        Triangle(){
            x =0.0f; 
            y = 0.0f; 
            x2 = 0.1f; 
            y2 = 0.1f; 
            x3 = -0.1f; 
            y3 = 0.1f; 
            //selected = false; 
        }

        Triangle(float x, float y, float x2, float y2, float x3, float y3, Color color){
            this->x = x; 
            this->y = y; 
            this->x2 = x2; 
            this->y2 = y2;
            this->x3 = x3; 
            this->y3=y3;
            this->color = color; 
            selected = false; 
        }

        void draw(){
            glColor3f(color.getR(), color.getG(), color.getB());
            glBegin(GL_POLYGON);

            glVertex2f(x,y);
            glVertex2f(x2,y2);
            glVertex2f(x3,y3); 
            glEnd();

           if(selected){
            //Rectangle outer(x, y + 0.02, outerWidth, outerHeight, Color(1.0, 1.0, 0.0));
            std::cout<<"selectecTED"<<std::endl;
           Triangle outer(x-0.01f,y-0.01f, x2+0.01f, y2-0.01f, x3, y3+0.01f, Color(0.0, 0.0, 0.0));
            Triangle inner(x+0.005f, y-0.005f, x2-0.005f, y2-0.005f, x3, y3-0.005f, color);
            outer.draw(); 
            inner.draw();   
            } 
        }

       bool contains(float mx, float my) {

        if (mx >= x && mx <= x2 && my >= y && my <= y3) {
                       std::cout<<"triangle"<<std::endl;
        return true;
        } else {
        return false;
        }
        }

        void setColor(Color color){
            this->color = color; 
        }

    void select() {
        selected = true;
    }

    void deselect() {
        selected = false;
    }


        float getX(){
            return x; 
        }

        float getY(){
            return y; 
        }

        void setX(float x){
            this->x=x;
    }

    void setY(float y){
            this->y = y;
    }

    };

    #endif