#ifndef CANVAS_H
#define CANVAS_H

#include "Circle.h"
#include "Rectangle.h"
#include "Toolbar.h"
#include "Point.h"
#include "Scribble.h"
#include "Triangle.h"
#include "Shape.h"
#include "ColorPicker.h"

struct Canvas{
    private: 
    Rectangle area;
    ColorPicker colorPicker;
    Color currentColor; 

    Rectangle squares[100];
     int sCounter;
     int selectedSquare;

    Rectangle rectangles[100];
    int rCounter; 
    int selectedRectangle; 

    Circle circles[100];
    int cCounter; 
    int selectedCircle; 

    Triangle triangles[100];
    int tCounter;
    int selectedTriangle; 

    float offsetX;
    float offsetY;
    float offsetX2; 
    float offsetX3; 
    float offsetY2; 
    float offsetY3; 

     Scribble scribbles[1000];
     int scribbleCounter;
     int selectedScribble;

    Shape* shapes[1000];
    int shapeCounter;
    int selectedShape;

    public:

    Canvas(){
        area = Rectangle(-0.8, 1, 1.8, 1.8, Color(1,1,1));
            colorPicker = ColorPicker(); 
            currentColor = colorPicker.getCurrentColor(); 
         scribbleCounter = 0;
         sCounter = 0;
         rCounter=0;
         cCounter=0;
         tCounter = 0;
         selectedSquare = -1;
         selectedRectangle = -1; 
         selectedCircle = -1;
         selectedScribble = -1;
         selectedTriangle = -1; 
        shapeCounter = 0;
        selectedShape = -1;
        offsetX = 0;
        offsetX2= 0;
        offsetX3 = 0;
        offsetY = 0;
        offsetY2 = 0;
        offsetY3 = 0; 
    }

    void draw(){
        area.draw();

        for (int i = 0; i < shapeCounter; i++){
            shapes[i]->draw();
        }

    }

    void bringToFront(int index){
        std::cout << "click on the shape to bring it to the front" << std::endl;
        Shape* selectedShape = shapes[index];
        for(int i = index; i<shapeCounter-1; i++){
            shapes[i] = shapes[i+1];
        }

        shapes[shapeCounter -1] = selectedShape; 


    }

    void bringToBack(int index){
                std::cout << "click on the shape to move it to the back" << std::endl;
        Shape* selectedShape = shapes[index]; 

        for(int i = index; i>0; i--){
            shapes[i] = shapes[i-1];

        }

        shapes[0] = selectedShape; 
    }


    void handleMouseClick(float x, float y, Tool selectedTool, Color color){
               currentColor = colorPicker.getCurrentColor(); 
        if (selectedTool == PENCIL){
            shapes[shapeCounter] = new Scribble();
            shapeCounter++;
            ((Scribble*)shapes[shapeCounter-1])->addPoint(x, y, color);
        }
        else if (selectedTool == ERASER){


            // erase shapes

            for(int i=0; i < shapeCounter; i++){
                if(shapes[i]->contains(x,y)){
                    for(int j =i; j< shapeCounter; j++){
                        shapes[j] = shapes[j+1];
                    }
                    shapeCounter--;
                    i--;
                    break;

                }
            }
            
        }
        else if (selectedTool == SQUARE){
            shapes[shapeCounter] = new Rectangle(x, y, 0.3, 0.3, color);
            shapeCounter++;
        }

        else if (selectedTool == RECTANGLE){
            shapes[shapeCounter] = new Rectangle(x, y, 0.5, 0.3, color);
            shapeCounter++;
        }

        else if(selectedTool == CIRCLE){
            std::cout<<"circle selected";
            shapes[shapeCounter] = new Circle(x, y, 0.15, color);
            shapeCounter++; 
        }

        else if(selectedTool == TRIANGLE){
            shapes[shapeCounter] = new Triangle(x, y, x+0.2, y, x+0.1, y+0.2, color);
            shapeCounter++; 
        }

        else if(selectedTool == FRONT){
            bringToFront(selectedShape);
            
        }

        else if(selectedTool == BACK){
            bringToBack(selectedShape);
            
        }

        else if (selectedTool == MOUSE){

            for (int i = 0; i < shapeCounter; i++){
                shapes[i]->deselect();
                                            
            }

            selectedShape = -1; 
            for (int i = shapeCounter-1; i >= 0; i--){
                if (shapes[i]->contains(x, y)){
                    shapes[i]->select();
                    selectedShape = i;
                                                      
                    offsetX = x - shapes[i]->getX();
                    offsetY = shapes[i]->getY() - y;
                   offsetX2 = x - (shapes[i]->getX2()); 
                    offsetX3 = x - shapes[i]->getX3(); 
                    offsetY2 = shapes[i]->getY2() - y; 
                    offsetY3 = shapes[i]->getY3() - y;   

                    break;
                }
                                  
            }

            
            if(selectedShape != -1){
                std::cout<<"scrible selected" << std::endl;
                shapes[selectedShape]->setColor(color);
            } // click on the shape again to change its color



        }




        

        else if(selectedTool == CLEAR){
            std::cout << "clear button";
                for(int i =0; i<shapeCounter; i++){
                    delete shapes[i];
                    shapes[i] = nullptr; 
                }


                shapeCounter = 0;
                scribbleCounter = 0;
                selectedShape = -1; 
                selectedScribble = -1; 
                
                //glutPostRedisplay();


        }
    }
    

    void handleMouseDrag(float x, float y, Tool selectedTool, Color color){
        //currentColor = colorPicker.getCurrentColor(); 
         if (selectedTool == PENCIL){
                ((Scribble*)shapes[shapeCounter-1])->addPoint(x, y, color);
         }
         else if (selectedTool == ERASER){
            for(int i=0; i < shapeCounter; i++){
                if(shapes[i]->contains(x,y)){
                    for(int j =i; j< shapeCounter; j++){
                        shapes[j] = shapes[j+1];
                    }
                    shapeCounter--;
                    i--;
                    break;

                }
            }
         }
         else if (selectedTool == MOUSE){
            if (selectedShape != -1){
                                     
                shapes[selectedShape]->setX(x - offsetX);
                shapes[selectedShape]->setY(y + offsetY);
            
                    shapes[selectedShape]->setX2(x - offsetX2);
        shapes[selectedShape]->setY2(y + offsetY2);
        shapes[selectedShape]->setX3(x - offsetX3);
        shapes[selectedShape]->setY3(y + offsetY3);
                
         }
    }
    }

    

    bool contains(float x, float y){
        return area.contains(x, y);
    }
    
    int counterValue(){
        return shapeCounter;
    }

    void setCounter(int shapeCounter){
        this->shapeCounter = shapeCounter; 
    }
};

#endif