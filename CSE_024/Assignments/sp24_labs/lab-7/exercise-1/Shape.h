#ifndef SHAPE_H
#define SHAPE_H

#include "Color.h"
class Shape{
protected:
    float x, x2, x3;
    float y, y2, y3;
    bool selected;
    Color color; 

public:
    virtual void draw() = 0;
    virtual bool contains(float, float) = 0;

    void select(){
        selected = true;
    }

    void deselect(){
        selected = false;
    }

    bool isSelected(){
        return selected;
    }

    void setX(float x){
        this->x = x;
    }

    

    Color getColor() {
        return color;
    }

    void setY(float y){
        this->y = y;
    }

    float getX(){
        return x;
    }

           float getX2(){
          return x2; 
        }

        void setX2(float x2){
            this->x2 = x2;
        }

        void setX3(float x3){
            this->x3 = x3; 
        }
           float getX3(){
          return x3; 
        }

    float getY(){
        return y;
    }

    
        void setY2(float y2){
            this->y2 = y2;
    }

        void setY3(float y2){
            this->y3 = y3;
    }


        float getY2(){
            return y2; 
        }

        float getY3(){
            return y3; 
        }


       void setColor(Color color) {
        this->color = color;
    }

    virtual ~Shape(){}

};

#endif