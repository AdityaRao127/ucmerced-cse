#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "AppController.h"
#include <GL/gl.h>
#include "Toolbar.h"
#include "Canvas.h"


struct Controller : public AppController {

    Toolbar toolbar;
    Canvas canvas;

    Controller(){

    }

    void leftMouseDown( float x, float y ){
        if (toolbar.contains(x, y)){
            toolbar.handleMouseClick(x, y);
        }
        else if (canvas.contains(x, y)){
            canvas.handleMouseClick(x, y, toolbar.selectedTool, Color(1,0,0));
        }
    }

    void mouseMotion( float x, float y ){
        if (canvas.contains(x, y)){
            canvas.handleMouseClick(x, y, toolbar.selectedTool, Color(1,0,0));
        }
    }

    void render() {
        toolbar.draw();
        canvas.draw();
    }

};

#endif