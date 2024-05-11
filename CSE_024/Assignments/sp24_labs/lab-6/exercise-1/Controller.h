#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/freeglut.h>
#include "AppController.h"
#include "ColorSelector.h"
#include "Toolbar.h"
#include "Canvas.h"
#include "ColorPicker.h"

struct Controller : public AppController {
    Toolbar toolbar;
    Canvas canvas;
    ColorSelector colorSelector;
    ColorPicker colorPicker; 

    Controller(){
        //
    }

    void leftMouseDown( float x, float y ){
        if(colorPicker.contains(x,y)){
            colorPicker.handleMouseClick(x,y);
        }
        else if (toolbar.contains(x, y)){
            toolbar.handleMouseClick(x, y);
        } else if (canvas.contains(x, y)){
               canvas.handleMouseClick(x, y, toolbar.getSelectedTool(), colorPicker.getCurrentColor());
        } else if (colorSelector.contains(x, y)){ // not needed
            colorSelector.handleMouseClick(x, y);

        }
    }

    void mouseMotion( float x, float y ) {
        if (canvas.contains(x, y)){
            if (toolbar.getSelectedTool() == PENCIL || toolbar.getSelectedTool() == ERASER){
                canvas.handleMouseClick(x, y, toolbar.getSelectedTool(), colorPicker.getCurrentColor()); // replace colorSelector with colorPicker here. 
            }
        }
    }

    void render(){
        canvas.draw();
        toolbar.draw();
        colorSelector.draw();
                colorPicker.draw(); // rendered over just to make the set colors selecition show
 

    }
};

#endif