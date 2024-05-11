
#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include "Rectangle.h"
#include "Color.h"
#include "Circle.h"
#include "Texture.h"

struct ColorPicker{
private:
    Circle R; 
    Circle G; 
    Circle B; 
    Rectangle colorAreas; 
    Texture plusRed;
    Texture minusRed;
    Texture plusGreen;
    Texture minusGreen;
    Texture plusBlue; 
    Texture minusBlue; 
    Rectangle currentColorSquare; 
    Color currentChange;
    Color brushColor; 

    // taken from COlorSelector
        Rectangle area;
    Rectangle redButton;
    Rectangle greenButton;
    Rectangle blueButton;
    //Color currentColor; 

    void deselectAll(){
        plusRed.deselect();
        minusRed.deselect();
        plusGreen.deselect();
        minusGreen.deselect();
        plusBlue.deselect();
        minusBlue.deselect(); 

        // colorSelector 
        redButton.deselect();
        greenButton.deselect();
        blueButton.deselect();
    }


public:
    ColorPicker(){
        colorAreas =  Rectangle(-1.0f, 0.575f, 0.2f, 2.0f, Color(0.8f, 0.8f, 0.8f));
        R = Circle(-0.96, 0.4, 0.035, Color(1.0f, 0.0f, 0.0f));
        G = Circle(-0.96, 0.0, 0.035, Color(0.0f, 1.0f, 0.0f)); 
        B = Circle(-0.96, -0.40, 0.035, Color(0.0f, 0.0f, 1.0f)); 
        plusRed = Texture("/home/me/workspace/assignments/lab-6/exercise-1/assets/plus.png", -0.90, 0.52, 0.1, 0.14);
        minusRed = Texture("/home/me/workspace/assignments/lab-6/exercise-1/assets/minus.png", -0.90, 0.365, 0.1, 0.14);

        plusGreen = Texture("/home/me/workspace/assignments/lab-6/exercise-1/assets/plus.png",-0.90, 0.15, 0.1, 0.14);
        minusGreen = Texture("/home/me/workspace/assignments/lab-6/exercise-1/assets/minus.png", -0.90, 0.0, 0.1, 0.15);

        plusBlue = Texture("/home/me/workspace/assignments/lab-6/exercise-1/assets/plus.png",-0.90, -0.25, 0.1, 0.15);
        minusBlue = Texture("/home/me/workspace/assignments/lab-6/exercise-1/assets/minus.png", -0.90, -0.405, 0.1, 0.15);

        currentColorSquare = Rectangle(-1.0, -0.6, 0.2f, 0.2f, Color(1.0f, 0.0f, 0.0f));
        currentChange = Color(1.0f,0.0f,0.0f);

        //taken from colorSelector 
        area = Rectangle(-0.8f, -0.8f, 1.8f, 0.2f, Color(0.8f, 0.8f, 0.8f));
        redButton = Rectangle(-0.8f, -0.8f, 0.2f, 0.2f, Color(1.0f, 0.0f, 0.0f));
        greenButton = Rectangle(-0.6f, -0.8f, 0.2f, 0.2f, Color(0.0f, 1.0f, 0.0f));
        blueButton = Rectangle(-0.4f, -0.8f, 0.2f, 0.2f, Color(0.0f, 0.0f, 1.0f));

        setRed();
        
    }

    Color getCurrentColor(){
        return currentChange; 
    }

    // colorSelector 
    void setRed(){
        deselectAll();
        currentChange = Color(1.0f, 0.0f, 0.0f);
        redButton.select();
    }
    
    void setGreen(){
        deselectAll();
        currentChange = Color(0.0f, 1.0f, 0.0f);
        greenButton.select();
    }

    void setBlue(){
        deselectAll();
        currentChange = Color(0.0f, 0.0f, 1.0f);
        blueButton.select();
    }
// 

    void setPlusRed(){
        deselectAll();
        if(currentChange.getR()+0.10 < 1){
            currentChange = Color(0.10 + currentChange.getR(), currentChange.getG(), currentChange.getB());
            plusRed.select(); 
            updateCurrentColorSquare();
        }
    }

    void setMinusRed(){
                deselectAll();
        if(currentChange.getR()-0.10 > 0){
        currentChange = Color(currentChange.getR()-0.10, currentChange.getG(), currentChange.getB());
        minusRed.select(); 
                updateCurrentColorSquare();
        }
    }

    void setPlusGreen(){
                deselectAll();
        if(currentChange.getG()+0.10 < 1){
        currentChange = Color(currentChange.getR(), currentChange.getG()+0.10, currentChange.getB());
        plusGreen.select(); 
                updateCurrentColorSquare();
        }
    }

    void setMinusGreen(){
                deselectAll();
        if(currentChange.getG()-0.10 > 0){
        currentChange = Color(currentChange.getR(), currentChange.getG()-0.10, currentChange.getB());
        minusGreen.select(); 
                updateCurrentColorSquare();
        }
    }

    void setPlusBlue(){
                deselectAll();
        if(currentChange.getB()+0.10 < 1){
        currentChange = Color(currentChange.getR(), currentChange.getG(), currentChange.getB()+0.10);
        plusBlue.select(); 
                updateCurrentColorSquare();
        }
    }

    void setMinusBlue(){
                deselectAll();
        if(currentChange.getB()-0.10 > 0){
        currentChange = Color(currentChange.getR(), currentChange.getG(), currentChange.getB()-0.10);
        minusBlue.select(); 
                updateCurrentColorSquare();
        }
    }

    void updateCurrentColorSquare(){
        currentColorSquare.setColor(currentChange);
    }

    void handleMouseClick(float x, float y){
        if (plusRed.contains(x, y)){
            setPlusRed();
        }
        else if (plusGreen.contains(x, y)){
            setPlusGreen();
        }
        else if (plusBlue.contains(x, y)){
            setPlusBlue();
        }
        else if (minusRed.contains(x, y)){
            setMinusRed();
        }
        else if (minusGreen.contains(x, y)){
            setMinusGreen();
        }
        else if(minusBlue.contains(x,y)){
            setMinusBlue();
            
        }
                // color selector stuff
        else if(redButton.contains(x, y)){
            setRed();
            redButton.select();
        }
         else if (greenButton.contains(x, y)){
            setGreen();
            greenButton.select();
        }
        else if (blueButton.contains(x, y)){
            setBlue();
            blueButton.select();
        }

        else{
            deselectAll();
        }

 
        updateCurrentColorSquare();
    }

    void draw(){

        area.draw();
        redButton.draw();
        greenButton.draw();
        blueButton.draw();
                colorAreas.draw();
        R.draw(); 
        G.draw();
        B.draw();
        plusRed.draw();
        plusGreen.draw();
        plusBlue.draw();
        minusRed.draw();
        minusGreen.draw(); 
        minusBlue.draw(); 
        currentColorSquare.draw();
        //
        
    }

    bool contains(float x, float y){
        return (colorAreas.contains(x, y) || area.contains(x,y));
    }
};



#endif