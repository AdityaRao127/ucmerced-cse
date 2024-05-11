#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include "AppController.h"
#include "Button.h"
#include "Scribble.h"

class Controller : public AppController {

    Scribble left;
    Scribble right;

    Button copy;
    Button up;
    Button down;

public:
    Controller(){
        // Initialize your state variables
        copy = Button("Duplicate", 0.3, -0.7);
        up = Button(" Up ", -0.9, -0.7);
        down = Button("Down", -0.5, -0.7);
    }

    void leftMouseDown( float x, float y ){
        // Respond to left mouse down events
        if (x < 0 && y > -0.6){
            left.addPoint(x, y, Color(1,0,0));
        }
        
        if (copy.contains(x, y)){
            right = left;
            right.setX(left.getX()+1);
        }
        else if (up.contains(x, y)){
            left.moveUp(); 
        }
        else if (down.contains(x, y)){
            left.moveDown();
        }
    } 

    void mouseMotion( float x, float y ) {
        if (x < 0 && y > -0.6){
            left.addPoint(x, y, Color(1,0,0));
        }
    }


    void render() {
        // Render some graphics

        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(0, 1);
        glVertex2f(0, -1);
        glEnd();

        left.draw();
        right.draw();

        copy.draw();
        up.draw();
        down.draw();
    }

};

#endif