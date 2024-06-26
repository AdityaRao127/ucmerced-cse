#include <GL/freeglut.h>
#include <iostream>
#include "Point.h"
#include "Rectangle.h"
#include "Button.h"
#include "Color.h"
#include "TextureRect.h"

using namespace std;

unsigned char * data; // String
int w = 100;
int h = 100;
int bitdepth = 4;
GLuint texture;


// Window width and height
int width = 400;
int height = 400;

Point points[10000];
int pCounter = 0;

Rectangle blueBtn(-0.8, -0.8, 0.4, 0.2, 0, 0, 1);
Rectangle redBtn(-0.3, -0.8, 0.4, 0.2, 1, 0, 0);

Color brushColor;

Rectangle canvas(-0.8, 1, 1.8, 1.8, 0.8, 0.8, 0.8);
Rectangle vertical(-1, 1, 0.2, 2, 0.7, 0.7, 0.7);
Rectangle horizontal(-0.8, -0.8, 1.8, 0.2, 0.6, 0.6, 0.6);

// TextureRect saveBtn("assets/save.png", 0, 0, 0.5, 0.5);

Button clearBtn("Clear", 0.6, -0.8);
// Convert window coordinates to Cartesian coordinates
void windowToScene(float& x, float& y) {
    x = (2.0f * (x / float(width))) - 1.0f;
    y = 1.0f - (2.0f * (y / float(height)));
}

void drawScene(){
    // Clear the screen and set it to current color (black)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Objects to be drawn go here
    glEnable(GL_POINT_SMOOTH);
    glPointSize(10);

    canvas.draw();

            // Start texture display
        glColor3f(1,1,1);
        glEnable(GL_TEXTURE_2D);
        // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, texture);


        glBegin(GL_POLYGON);

        // Bottom Left
        glTexCoord2f(0.0f, 1.0f); 
        glVertex2f(0.0f, 0.0f);
        
        // Top Left
        glTexCoord2f(0.0f, 0.0f); 
        glVertex2f(0.0f, 0.5f);
        
        // Top Right
        glTexCoord2f(1.0f, 0.0f); 
        glVertex2f(0.5f, 0.5f);
        
        // Bottom Right
        glTexCoord2f(1.0f, 1.0f); 
        glVertex2f(0.5f, 0.0f);
        
        glEnd();

        glColor3f(1,1,1);
        glDisable(GL_TEXTURE_2D);
        // End texture display

    for (int i = 0; i < pCounter; i++){
        points[i].draw();
    }

    vertical.draw();
    horizontal.draw();

    blueBtn.draw();
    redBtn.draw();

    clearBtn.render();
    

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

    if (button == 0 && state == 1){
        clearBtn.down = false;
    }

    if (button == 0 && state == 0){
        if (canvas.inside(mx, my)){
            if (pCounter < 10000){
                points[pCounter] = Point(mx, my, brushColor);
                pCounter++;
            }
        }
        else if (horizontal.inside(mx, my)){
               if (blueBtn.inside(mx, my)){
                    cout << "Blue was clicked" << endl;
                    // r = 0; g = 0; b = 1;
                    brushColor.set(0, 0, 1);
                }
                if (redBtn.inside(mx, my)){
                    cout << "Red was clicked" << endl;
                    brushColor.setRed();
                }
                if (clearBtn.inside(mx, my)){
                    cout << "Clear was clicked" << endl;
                    pCounter = 0;
                    clearBtn.down = true;
                }
        }
        else if (vertical.inside(mx, my)){
            cout << "Clicked on Vertical" << endl;
        }
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

    if (pCounter < 10000){
        if (canvas.inside(mx, my)){
            points[pCounter] = Point(mx, my, brushColor);
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

int main(int argc,char** argv) {
    // Perform some initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("GLUT App");

    // Set the Display Function
    glutDisplayFunc(drawScene);

    // Set the Mouse Function
    glutMouseFunc(mouse);

    // Set the Motion Function
    glutMotionFunc(motion);

    // Set the Keyboard Funcion
    glutKeyboardFunc(keyboard);

    // Start texture load
        data = stbi_load("assets/pencil.png", &w, &h, &bitdepth, STBI_rgb_alpha);

        if (data == NULL){
            std::cerr << "Could not load texture file." << std::endl;
        }
        else{
            std::cout << "Loaded texture file successfully" << std::endl;
        }
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        // End texture load


    // Run the program
    glutMainLoop();

    return 0;
}