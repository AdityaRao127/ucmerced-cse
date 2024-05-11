#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "AppController.h"
#include <GL/gl.h>
#include "Toolbar.h"
#include "Canvas.h"
#include "ColorSelector.h"


struct Controller : public AppController {

    Toolbar toolbar;
    Canvas canvas;
    ColorSelector colorSelector;

    Controller(){

    }

    void leftMouseDown( float x, float y ){
        if (toolbar.contains(x, y)){
            toolbar.handleMouseClick(x, y);
        }
        else if (canvas.contains(x, y)){
            canvas.handleMouseClick(x, y, toolbar.getSelectedTool(), colorSelector.currentColor);
        }
        else if (colorSelector.contains(x, y)){
            colorSelector.handleMouseClick(x, y);
            if (canvas.selectedSquare != -1){
                canvas.squares[canvas.selectedSquare].setColor(colorSelector.currentColor);
            }
        }
    }

    void mouseMotion( float x, float y ){
        if (canvas.contains(x, y)){
            canvas.handleMouseDrag (x, y, toolbar.getSelectedTool(), colorSelector.currentColor);
        }
    }

    void render() {
        canvas.draw();
        toolbar.draw();
        colorSelector.draw();
    }

};

#endif