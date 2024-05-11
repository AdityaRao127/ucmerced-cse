#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "AppController.h"
#include <GL/gl.h>
#include "Toolbar.h"
#include "Canvas.h"
#include "ColorPicker.h"


struct Controller : public AppController {

    Toolbar toolbar;
    Canvas canvas;
    ColorPicker colorPicker;
    bool x = false; 

    Controller(){

    }

    void leftMouseDown( float x, float y ){
        if (toolbar.contains(x, y)){
            toolbar.handleMouseClick(x, y);
            if(toolbar.pressedClear()){
                canvas.setCounter(0);
            }
                                       // toolbar.setClear(false);

        }
        else if (canvas.contains(x, y)){
            canvas.handleMouseClick(x, y, toolbar.getSelectedTool(), colorPicker.getCurrentColor());
        }
        else if (colorPicker.contains(x, y)){
            colorPicker.handleMouseClick(x, y);
        }
    }

    void mouseMotion( float x, float y ){
        if (canvas.contains(x, y)){
            canvas.handleMouseDrag(x, y, toolbar.getSelectedTool(), colorPicker.getCurrentColor());
        }
    }

    void render() {
        canvas.draw();
        toolbar.draw();
        colorPicker.draw();
    }

};

#endif