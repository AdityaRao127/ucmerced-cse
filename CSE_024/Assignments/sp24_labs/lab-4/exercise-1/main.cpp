#include "Button.h"
#include "Color.h"
#include "Point.h"
#include "Rectangle.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include "Texture.h"

using namespace std;

/* MAKE A WHITE BOX TO SHOW WHICH SHAPE IS SELECTED. MAke sure that overlapping shapes, only top one is selectedd*/
// possibly go backwards through the array
// does not have to be selection shwon on dtag          
// doo not have corner follow mouse, but wheerevvr it's clicked 
// risizing has to be on drag ?                                                                                                                                                                                                                                                                                            


// 

// selection feature
int selected = -1; 
enum Shape{NONE, RECTANGLE, TRIANGLE, CIRCLE};
Shape selectedType = NONE;
int maxRec = 100;
int maxCirc = 100;
int maxTri = 100;
int recCount = 0;
int triCount = 0;
int circCount = 0;
Rectangle rectangles[100];
Triangle triangles[100];
Circle circles[100];
bool shapeFound; 
bool selectorActivity; 
// Window width and height
int width = 400;
int height = 400;

Point points[10000];
int pCounter = 0;
int thickness = 10;
float offsetX = 0; 
float offsetY =0;

bool brushClicked = false;
bool shapeSelected = false;
bool rectSelected = false;
bool triSelected = false;
bool circSelected = false;
bool recButtonDown = false; 
bool circButtonDown = false;
bool triButtonDown = false;
bool dragging = false; 
bool dragOnShape = false;
bool shapeClicked = false; 
 

// buttons

Rectangle blueBtn(-1, 1, 0.2, 0.1, 0, 0, 1);
Rectangle redBtn(-1, 0.9, 0.2, 0.1, 1, 0, 0);
Rectangle yellowBtn(-1, 0.8, 0.2, 0.1, 1, 1, 0);
Rectangle orangeBtn(-1, 0.7, 0.2, 0.1, 1, 0.647, 0);
Rectangle greenBtn(-1, 0.6, 0.2, 0.1, 0, 0.502, 0);
Rectangle violetBtn(-1, 0.5, 0.2, 0.1, 0.58, 0.0, 0.827);
Rectangle colorIndicator(-0.90, -0.8025, 0.065, 0.065, 1, 1, 1);
Rectangle thicknessIndicator(-0.93, -0.92125, 0.05, 0.05, 0, 0, 0);
Rectangle shapeSizeIndicator(-0.975, -0.912, 0.04, 0.04, 1, 0, 0);


Color brushColor;
Color current;
// bool colorSelected = false;

Rectangle canvas(-0.8, 1, 1.8, 1.8, 1, 1, 1);
Rectangle vertical(-1, 1, 0.2, 2, 0.7, 0.7, 0.7);
Rectangle horizontal(-0.8, -0.8, 1.8, 0.2, 0.6, 0.6, 0.6);

Button clearBtn("Clear", 0.71, -0.8);
Button brushIcon("Brush", 0.40, -0.8);
Texture pencilTexture("/home/me/workspace/assignments/lab-4/assets/pencil.png", brushIcon.x, brushIcon.y, brushIcon.w+0.1, brushIcon.h);
Button eraser("Eraser", 0.07, -0.8);
Texture eraserTexture("/home/me/workspace/assignments/lab-4/assets/eraser.png", eraser.x, eraser.y, eraser.w+0.1, eraser.h);
Button plusSize("+Thick", -0.27, -0.8);
Button minusSize("-Thick", -0.6, -0.8);
Button plusShapeSize("+", -.7, -0.8);
Button minusShapeSize("-",-0.8, -0.8 );

Button selector("Sel", -1, 0.3);
Texture cursor("/home/me/workspace/assignments/lab-4/assets/cursor.png", selector.x, selector.y, selector.w, selector.h);
Button drawRect("Rec", -1, 0);
Texture rectTexture("/home/me/workspace/assignments/lab-4/assets/rectangle.png", drawRect.x, drawRect.y, drawRect.w, drawRect.h);
Button drawTri("Tri", -1, -.3);
Texture triTexture("/home/me/workspace/assignments/lab-4/assets/triangle.png.png", drawTri.x, drawTri.y, drawTri.w, drawTri.h);
Button drawCirc("Cir", -1, -0.59);
Texture circTexture("/home/me/workspace/assignments/lab-4/assets/circle.png", drawCirc.x, drawCirc.y, drawCirc.w, drawCirc.h);

// indicate what tool is being selected
Rectangle selectorIndicator(-1, 0, 0.19, 0.05, 0,1,0);
Rectangle toolSelection(-0.8, -0.8, 0.2, 0.2, 0, 0, 0);

// Convert window coordinates to Cartesian coordinates
void windowToScene(float &x, float &y) {
  x = (2.0f * (x / float(width))) - 1.0f;
  y = 1.0f - (2.0f * (y / float(height)));
}

void drawScene() {
  // Clear the screen and set it to current color (black)
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  canvas.draw();
  // int thickness = 10;
  // Objects to be drawn go here

glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_POINT_SMOOTH);
  glPointSize(thickness);


  vertical.draw();
  horizontal.draw();
  for (int x = 0; x < recCount; x++) {

    rectangles[x].drawShape();

  }

  for (int k = 0; k < circCount; k++) {
    circles[k].drawShape();
  }

  for (int t = 0; t < triCount; t++) {
    triangles[t].drawShape();
     vertical.draw();
  }

  for (int i = 0; i < pCounter; i++) {
    points[i].draw();
  }
  vertical.draw();


  blueBtn.draw();
  redBtn.draw();
  yellowBtn.draw();
  orangeBtn.draw();
  greenBtn.draw();
  violetBtn.draw();
  colorIndicator.draw();
  toolSelection.draw();
  thicknessIndicator.draw();
  shapeSizeIndicator.draw(); 
selectorIndicator.draw();
  

  clearBtn.render();
  brushIcon.render();
  pencilTexture.draw(); 
  eraser.render();
  eraserTexture.draw(); 
  selector.render();
  cursor.draw(); 
  plusSize.render();
  minusSize.render();
  drawRect.render();
  rectTexture.draw(); 
  drawTri.render();
  triTexture.draw();
  drawCirc.render();
  circTexture.draw();
  plusShapeSize.render();
  minusShapeSize.render();


       if(selectedType == RECTANGLE && shapeClicked && !recButtonDown){
            rectangles[selected].ifSelected(); 
        }
        else if(selectedType == CIRCLE && shapeClicked && !circButtonDown){
            circles[selected].ifSelected(); 
        }
        else if(selectedType == TRIANGLE && shapeClicked && !triButtonDown){
            triangles[selected].ifSelected();
        } 
  






  // We have been drawing to the back buffer, put it in the front
  glutSwapBuffers();
}



void mouse(int button, int state, int x, int y) {
  /*
      button: 0 -> left mouse button
              1 -> right mouse button

      state:  0 -> mouse click
              2 -> mouse release

      x, y:   mouse location in window relative coordinates
  */
  float mx = x;
  float my = y;
  windowToScene(mx, my);



  // none of the buttons are clicked is mouse is not down
  if (button == 0 && state == 1) {
    clearBtn.down = false;
    brushIcon.down = false;
    eraser.down = false;
    plusSize.down = false;
    minusSize.down = false;
    drawRect.down = false;
    drawCirc.down = false;
    drawTri.down = false;
    selector.down = false;
    dragging = false; 
    dragOnShape = false; 
    plusShapeSize.down = false;
    minusShapeSize.down = false; 



    //selected =-1; 
    //selectedType = NONE;

  }


  if (button == 0 && state == 0) {
    float mx = x;
    float my = y;
    windowToScene(mx, my);


    dragging = true;
    shapeClicked = false; 

   if(drawRect.inside(mx, my) || drawTri.inside(mx, my) || drawCirc.inside(mx ,my)){
        selected = -1; 
        selectedType = NONE;

        recButtonDown = true; 
        triButtonDown = true; 
        circButtonDown = true; 
    } 

    


    

// increase size of shapes

if(plusShapeSize.inside(mx,my) && selected != -1){
    float s = 1 + 0.1; 
    if(selectedType == RECTANGLE){

            plusShapeSize.down = true;
                    if(shapeSizeIndicator.w + 0.01 <  0.15){
                                rectangles[selected].resize(s);
                                rectangles[selected].ifSelected(); 
            shapeSizeIndicator.w += 0.01; 
            shapeSizeIndicator.h += 0.01; 
                    }
    }
    else if(selectedType == CIRCLE){

                    plusShapeSize.down = true;
                    if(shapeSizeIndicator.w + 0.01 <  0.05){
                                circles[selected].resize(s); 
                                                    circles[selected].ifSelected(); 
            shapeSizeIndicator.w += 0.01; 
            shapeSizeIndicator.h += 0.01; 
                    }
    }
    else if(selectedType == TRIANGLE){

                    plusShapeSize.down = true;
                    if(shapeSizeIndicator.w + 0.01 <  0.15){
                                triangles[selected].resize(s);
                    triangles[selected].ifSelected(); 
            shapeSizeIndicator.w += 0.01; 
            shapeSizeIndicator.h += 0.01; 
                    }
    }
}

if(minusShapeSize.inside(mx,my) && selected != -1){
    float s = 1 - 0.1; 
    if(selectedType == RECTANGLE){

            minusShapeSize.down = true; 
                    if(shapeSizeIndicator.w - 0.01 >  0.005){
                                rectangles[selected].resize(s);
            shapeSizeIndicator.w -= 0.01; 
            shapeSizeIndicator.h -= 0.01; 
                    }
    }
    else if(selectedType == CIRCLE){

                    minusShapeSize.down = true; 
                    if(shapeSizeIndicator.w - 0.01 > 0.00025){
                                circles[selected].resize(s); 
            shapeSizeIndicator.w -= 0.01; 
            shapeSizeIndicator.h -= 0.01; 
                    }

    }
    else if(selectedType == TRIANGLE){
                    
                    minusShapeSize.down = true; 
                    if(shapeSizeIndicator.w - 0.01 >  0.005){
                                triangles[selected].resize(s);
            shapeSizeIndicator.w -= 0.01; 
            shapeSizeIndicator.h -= 0.01; 
                    }

    }
}



// selecting individual shapes in arrays

      for(int q = recCount-1; q>=0; q--){
          if(rectangles[q].inside(mx,my)){
            selected = q; 
            selectedType = RECTANGLE; 
            shapeClicked = true; 
                        offsetX = mx - rectangles[q].x; 
            offsetY = my - rectangles[q].y; 
            break;

          }
      }

      for(int a=triCount-1; a>=0; a--){
          if(triangles[a].inside(mx, my)){
              selected = a; 
              selectedType = TRIANGLE; 
              shapeClicked = true;
                          offsetX = mx - triangles[a].x1; 
            offsetY = my - triangles[a].y1; 
              break;
              
          }
      }
      for(int w=circCount-1; w>=0; w--){
          if(circles[w].inside(mx, my)){
              selected = w; 
              selectedType = CIRCLE; 
              shapeClicked = true;
                          offsetX = mx - circles[w].x; 
            offsetY = my - circles[w].y; 
              break;
          }
      }



    

      dragOnShape = shapeClicked; 

// showing selected shape


// rrecoloring 



if(selectedType == RECTANGLE){
    if(blueBtn.inside(mx, my)){
        rectangles[selected].setColor(0,0,1); 
                colorIndicator.r =0;
                colorIndicator.g = 0;
                colorIndicator.b =1; 
    }

    else if(redBtn.inside(mx,my)){
        rectangles[selected].setColor(1,0,0);
                colorIndicator.r =1;
                colorIndicator.g = 0;
                colorIndicator.b =0; 
    }
    else if(yellowBtn.inside(mx,my)){
        rectangles[selected].setColor(1,1,0);
                      colorIndicator.r =1;
                colorIndicator.g = 1;
                colorIndicator.b =0; 
    }
    else if(orangeBtn.inside(mx,my)){
        rectangles[selected].setColor(1,0.647,0);
                colorIndicator.r = 1;
                colorIndicator.g = 0.647; 
                colorIndicator.b =0;
    }
    else if(greenBtn.inside(mx,my)){
        rectangles[selected].setColor(0,0.502,0);
                        colorIndicator.r = 0;
                colorIndicator.g = 0.52; 
                colorIndicator.b =0;
    }
    else if(violetBtn.inside(mx,my)){
        rectangles[selected].setColor(0.58, 0, 0.827);
        colorIndicator.r = 0.58;
        colorIndicator.g = 0;
        colorIndicator.b = 0.827;

    }
}

if(selectedType == TRIANGLE){
    if(blueBtn.inside(mx, my)){
        triangles[selected].setColor(0,0,1); 
                colorIndicator.r =0;
                colorIndicator.g = 0;
                colorIndicator.b =1; 
    }

    else if(redBtn.inside(mx,my)){
        triangles[selected].setColor(1,0,0);
                colorIndicator.r =1;
                colorIndicator.g = 0;
                colorIndicator.b =0; 
    }
    else if(yellowBtn.inside(mx,my)){
        triangles[selected].setColor(1,1,0);
                  colorIndicator.r =1;
                colorIndicator.g = 1;
                colorIndicator.b =0; 
    }
    else if(orangeBtn.inside(mx,my)){
        triangles[selected].setColor(1,0.647,0);
                colorIndicator.r = 1;
                colorIndicator.g = 0.647; 
                colorIndicator.b =0;
    }
    else if(greenBtn.inside(mx,my)){
        triangles[selected].setColor(0,0.502,0);
                        colorIndicator.r = 0;
                colorIndicator.g = 0.52; 
                colorIndicator.b =0;
    }
    else if(violetBtn.inside(mx,my)){
        triangles[selected].setColor(0.58, 0, 0.827);
        colorIndicator.r = 0.58;
        colorIndicator.g = 0;
        colorIndicator.b = 0.827;
    }
}

if(selectedType == CIRCLE){
    if(blueBtn.inside(mx, my)){
        circles[selected].setColor(0,0,1); 
                colorIndicator.r =0;
                colorIndicator.g = 0;
                colorIndicator.b =1; 
    }

    else if(redBtn.inside(mx,my)){
        circles[selected].setColor(1,0,0);
                colorIndicator.r =1;
                colorIndicator.g = 0;
                colorIndicator.b =0; 
    }
    else if(yellowBtn.inside(mx,my)){
        circles[selected].setColor(1,1,0);
                  colorIndicator.r =1;
                colorIndicator.g = 1;
                colorIndicator.b =0; 
    }
    else if(orangeBtn.inside(mx,my)){
        circles[selected].setColor(1,0.647,0);
                colorIndicator.r = 1;
                colorIndicator.g = 0.647; 
                colorIndicator.b =0;
    }
    else if(greenBtn.inside(mx,my)){
        circles[selected].setColor(0,0.502,0);
                        colorIndicator.r = 0;
                colorIndicator.g = 0.52; 
                colorIndicator.b =0;
    }
    else if(violetBtn.inside(mx,my)){
        circles[selected].setColor(0.58, 0, 0.827);
        colorIndicator.r = 0.58;
        colorIndicator.g = 0;
        colorIndicator.b = 0.827;
    }
}
  }
        




    if (canvas.inside(mx, my) && (shapeSelected || selector.down) && !brushClicked) {
      if (rectSelected && (recCount < maxRec)) {
        rectangles[recCount] = Rectangle(mx, my, 0.4, 0.2, current.r,
                                         current.g, current.b);
        recCount++;
        rectSelected = false;
      }

      if (circSelected && (circCount < maxCirc)) {
        circles[circCount] = Circle(mx, my, 0.2, current.r,
                                    current.g, current.b);
        circCount++;
        circSelected = false;
      }

      if (triSelected && (triCount < maxTri)) {
        float sideLength = 0.1; 
        triangles[triCount] = Triangle(mx, my, mx+0.1, my+0.125, mx+0.25, my, current.r,
                                       current.g, current.b);
                                
        triCount++;
        triSelected = false;
        }
    }
    if (canvas.inside(mx, my) && brushClicked) {
      if (pCounter < 10000) {
        points[pCounter] = Point(mx, my, brushColor, thickness);
        pCounter++;
      }
    } else if (vertical.inside(mx, my) || (horizontal.inside(mx, my))) {
      if (drawRect.inside(mx, my)) {

        shapeSelected = true;
        rectSelected = true;
        triSelected = false; 
        circSelected=false; 
        drawRect.down = true;
        brushClicked = false;
          selectorIndicator.y = 0.03;
          selectorIndicator.w = 0.20; 
          selectedType = RECTANGLE;
          selectorActivity = false;

          recButtonDown = true;

                  toolSelection.x = (brushIcon.x)+3;
        toolSelection.y = brushIcon.y + 3;
        


      }
      if (drawTri.inside(mx, my)) {

        shapeSelected = true;
        triSelected = true;
        rectSelected = false; 
        circSelected = false;
        drawTri.down = true;
        brushClicked = false;
        selectorIndicator.y = -0.27;
          selectorIndicator.w = 0.20;
          selectedType = TRIANGLE;
          triButtonDown = true;

          
        toolSelection.x = (brushIcon.x)+3;
        toolSelection.y = brushIcon.y + 3;
      }
      if (drawCirc.inside(mx, my)) {

        shapeSelected = true;
        circSelected = true;
        triSelected = false; 
        rectSelected = false; 
        drawCirc.down = true;
        brushClicked = false;
        selectorIndicator.y = -0.56;
          selectorIndicator.w = 0.20;
          selectedType = CIRCLE;
          circButtonDown = true; 

        toolSelection.x = (brushIcon.x)+3;
        toolSelection.y = brushIcon.y + 3;

      }
      if (blueBtn.inside(mx, my)) {
        brushColor.setBlue();
        colorIndicator.r = 0; // set color indicator to the color of brush
          colorIndicator.g = 0;
          colorIndicator.b = 1;
            current = brushColor;
        if (brushClicked) {
          cout << "Blue was clicked" << endl;
          brushColor.setBlue();
          current = brushColor;
          colorIndicator.r = 0; // set color indicator to the color of brush
          colorIndicator.g = 0;
          colorIndicator.b = 1;
                    current = brushColor;

       toolSelection.x = (brushIcon.x)+0.05;
        toolSelection.y = brushIcon.y + 0.025;
          toolSelection.r = 1;
          toolSelection.g = 0;
          toolSelection.b = 0;
        } else {
          cout << "Select the brush tool to paint" << endl;
        }
        //
      }
      if (redBtn.inside(mx, my)) {
                    brushColor.setRed();
                      colorIndicator.r = 1;
          colorIndicator.g = 0;
          colorIndicator.b = 0;
                              current = brushColor;
        if (brushClicked) {
          cout << "Red was clicked" << endl;
          brushColor.setRed();
          current = brushColor;
          colorIndicator.r = 1;
          colorIndicator.g = 0;
          colorIndicator.b = 0;
                    current = brushColor;

       toolSelection.x = (brushIcon.x)+0.05;
        toolSelection.y = brushIcon.y + 0.025;
          toolSelection.r = 1;
          toolSelection.g = 0;
          toolSelection.b = 0;
        } else {
          cout << "Select the brush tool to paint" << endl;
        }
      }

      // added additional colors
      if (yellowBtn.inside(mx, my)) {
                    brushColor.setYellow();
                              colorIndicator.r = 1;
          colorIndicator.g = 1;
          colorIndicator.b = 0;
                              current = brushColor;
        if (brushClicked) {
          cout << "Yellow was clicked" << endl;
          brushColor.setYellow();
                    current = brushColor;
          colorIndicator.r = 1;
          colorIndicator.g = 1;
          colorIndicator.b = 0;
                    current = brushColor;

        toolSelection.x = (brushIcon.x)+0.05;
        toolSelection.y = brushIcon.y + 0.025;
          toolSelection.r = 1;
          toolSelection.g = 0;
          toolSelection.b = 0;
        } else {
          cout << "Select the brush tool to paint" << endl;
        }
      }
      if (orangeBtn.inside(mx, my)) {
                    brushColor.setOrange();
                              colorIndicator.r = 1;
          colorIndicator.g = 0.647;
          colorIndicator.b = 0;
                            current = brushColor;
        if (brushClicked) {
          cout << "Orange was clicked" << endl;
          brushColor.setOrange();
          current = brushColor;
          colorIndicator.r = 1;
          colorIndicator.g = 0.647;
          colorIndicator.b = 0;
                    current = brushColor;

        toolSelection.x = (brushIcon.x)+0.05;
        toolSelection.y = brushIcon.y + 0.025;
          toolSelection.r = 1;
          toolSelection.g = 0;
          toolSelection.b = 0;
        } else {
          cout << "Select the brush tool to paint" << endl;
        }
        // r = 0; g = 0; b = 1;
      }
      if (greenBtn.inside(mx, my)) {
                    brushColor.setGreen();
                              colorIndicator.r = 0;
          colorIndicator.g = 0.502;
          colorIndicator.b = 0;
                              current = brushColor;
        if (brushClicked) {
          cout << "Green was clicked" << endl;
          brushColor.setGreen();
          current = brushColor;
          colorIndicator.r = 0;
          colorIndicator.g = 0.502;
          colorIndicator.b = 0;
                    current = brushColor;

        toolSelection.x = (brushIcon.x)+0.05;
        toolSelection.y = brushIcon.y + 0.025;
          toolSelection.r = 1;
          toolSelection.g = 0;
          toolSelection.b = 0;
        } else {
          cout << "Select the brush tool to paint" << endl;
        }
        // r = 0; g = 0; b = 1;
      }
      if (violetBtn.inside(mx, my)) {
                    brushColor.setViolet();
                              colorIndicator.r = 0.58;
          colorIndicator.g = 0.0;
          colorIndicator.b = 0.827;
                              current = brushColor;
        if (brushClicked) {
          cout << "Violet was clicked" << endl;
          brushColor.setViolet();
          current = brushColor;
          colorIndicator.r = 0.58;
          colorIndicator.g = 0.0;
          colorIndicator.b = 0.827;
                    current = brushColor;

        toolSelection.x = (brushIcon.x)+0.05;
        toolSelection.y = brushIcon.y + 0.025;
          toolSelection.r = 1;
          toolSelection.g = 0;
          toolSelection.b = 0;
        } else {
          cout << "Select the brush tool to paint" << endl;
        }
        // r = 0; g = 0; b = 1;
      }
      if (clearBtn.inside(mx, my)) {
        cout << "Clear was clicked" << endl;
        pCounter = 0;
        recCount = 0;
        circCount = 0;
        triCount = 0;
        clearBtn.down = true;
        brushColor.set(1, 1, 1);
      }
      if (brushIcon.inside(mx, my)) {
        cout << "Brush was selected. Select a color to paint!" << endl;
        brushIcon.down = true;
        brushClicked = true;
        current = brushColor;
        brushColor = current;
        current = brushColor;
        colorIndicator.r = brushColor.r;
        colorIndicator.g = brushColor.g;
        colorIndicator.b = brushColor.b;

        toolSelection.x = (brushIcon.x)+0.05;
        toolSelection.y = brushIcon.y + 0.025;
        toolSelection.r = 1;
        toolSelection.g = 0;
        toolSelection.b = 0;

                selectorIndicator.y = -3;
          selectorIndicator.w = 3;
      }
      if (eraser.inside(mx, my)) {
        cout << "Eraser was selected" << endl;

        selector.down = false; 
        eraser.down = true;
        brushClicked = true;
        brushColor.set(1, 1, 1);
        toolSelection.x = (eraser.x) + 0.05;
        toolSelection.y = (eraser.y) + 0.025;
        toolSelection.r = 0;
        toolSelection.g = 0;
        toolSelection.b = 0;

                        selectorIndicator.y = -3;
          selectorIndicator.w = 3;
      }

      if(selector.inside(mx,my)){
          cout << "selection tool has been pressed" << endl;
          selector.down = true; 
          recButtonDown =false;
          triButtonDown = false;
          circButtonDown = false; 
          brushClicked = false; 
          selectorIndicator.y = 0.33;
          selectorIndicator.w = 0.20;
          selectorActivity = true; 
                  toolSelection.x = (brushIcon.x)+20;
        toolSelection.y = brushIcon.y + 20;


      }
      else{
          selectorActivity=false;
      }
      if (plusSize.inside(mx, my)) {
        glBegin(GL_POINTS);
        cout << "Brush thickness was increased" << endl;
        if (thickness < 30) {
          thickness++;
          // increase thickness if size button clicked
          thicknessIndicator.w += 0.0025;
          thicknessIndicator.h += 0.0025;
          thicknessIndicator.w = thicknessIndicator.h;
        } else {
          cout << "max thickness reached" << endl;
        }
        plusSize.down = true;
        glEnd();
      }
      if (minusSize.inside(mx, my)) {
        glBegin(GL_POINTS);
        if (thickness > 1) {
          thickness--;
          // decreased thickness if size button is thick
          cout << "Brush thickness decreased" << endl;
          thicknessIndicator.w -= 0.0025;
          thicknessIndicator.h -= 0.0025;
          thicknessIndicator.w = thicknessIndicator.h;
        } else {
          cout << "thickness can not be set lower" << endl;
        }

        minusSize.down = true;
        glEnd();
      }
    } else if (vertical.inside(mx, my)) {
      cout << "Clicked on Vertical" << endl;
    }

  glutPostRedisplay();
  }



void motion(int x, int y) {
  /*
      x, y:   mouse location in window relative coordinates
  */
  float mx = x;
  float my = y;
  windowToScene(mx, my);
  
 
if(dragging && dragOnShape && !recButtonDown && !brushClicked && !eraser.down){
  if((selectedType == RECTANGLE) && (selected !=-1)){
      rectangles[selected].x  = mx - offsetX; 
        rectangles[selected].y = my - offsetY; 
  }
}


if(dragging && dragOnShape && !triButtonDown&& !brushClicked && !eraser.down){
  if((selectedType == TRIANGLE) &&(selected != -1)){
      float dx = mx - triangles[selected].x1; 
    float dy = my - triangles[selected].y1;

      triangles[selected].x1 += dx - offsetX; 
      triangles[selected].y1 += dy - offsetY; 
            triangles[selected].x2 += dx - offsetX; 
      triangles[selected].y2 += dy - offsetY; 
            triangles[selected].x3 += dx-offsetX; 
      triangles[selected].y3 += dy-offsetY; 

  }
}

if(dragging && dragOnShape && !circButtonDown&& !brushClicked && !eraser.down){
  if((selectedType == CIRCLE) && (selected != -1)){
      circles[selected].x = mx - offsetX; 
      circles[selected].y = my - offsetY;
  }
}

// ADD OTEHRS

  if (pCounter < 10000 && brushClicked) {
    if (canvas.inside(mx, my)) {
      points[pCounter] = Point(mx, my, brushColor, thickness);
      pCounter++;
    }
  }
  glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
  /*
      key:    ASCII character of the keyboard key that was pressed
      x, y:   mouse location in window relative coordinates
  */
}
void initialize(){
    pencilTexture.loadTexture(); 
    eraserTexture.loadTexture();
    rectTexture.loadTexture(); 
    triTexture.loadTexture(); 
    circTexture.loadTexture(); 
    cursor.loadTexture();
}
int main(int argc, char **argv) {
  // Perform some initialization
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("GLUT App");

  // Set the Display Function
  glutDisplayFunc(drawScene);

  // Set the Mouse Function
  glutMouseFunc(mouse);

  // Set the Motion Function
  glutMotionFunc(motion);

  // load texture
   initialize(); 
  // Set the Keyboard Funcion
  glutKeyboardFunc(keyboard);

  // Run the program
  glutMainLoop();

  return 0;
}