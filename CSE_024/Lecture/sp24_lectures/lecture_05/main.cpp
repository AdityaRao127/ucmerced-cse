#include <GL/freeglut_std.h>
#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

using namespace std;

struct Circle{
    float radius;
    float x;
    float y;
    float r;
    float g;
    float b;
    bool selected;

    // Constructor (Default)
    Circle(){
        radius = 0.2;
        x = 0;
        y = 0;
        r = 1;
        g = 0;
        b = 0;
        selected = false;
    }

    Circle(float _radius, float _x, float _y, float _r, float _g, float _b){
        radius = _radius;
        x = _x;
        y = _y;
        r = _r;
        g = _g;
        b = _b;
        selected = false;
    }

    void draw(){
        if (selected){
            glColor3f(1, 0, 1);
        }
        else{
            glColor3f(r, g, b);
        }
        glBegin(GL_POLYGON);

        float inc = (2*M_PI) / 60;
        for (float theta = 0; theta < 2*M_PI; theta += inc){
            glVertex2f(radius*cos(theta)+x, radius*sin(theta)+y);
        }

        glEnd();
    }

    bool inside(float px, float py){
        float d = sqrt(pow(x - px, 2)) + sqrt(pow(y - py, 2));
        if (d <= radius){
            return true;
        }
        else {
            return false;
        }
    }

};



int width = 400;
int height = 400;


// State information needed to render the scene

// Circle c(0.5, 0, 0, 0, 0, 1);

Circle circles[5];
int counter = 0;
float r = 0, g = 0, b = 0;

void windowToScene ( float& x, float &y ){
    x = (2.0f * (x / float(width))) - 1.0f;
    y = 1.0f - (2.0f * (y / float(height)));
}


void drawScene(){
    // Clear the screen and set it to current color (black)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Objects to be drawn go here

    for (int i = 0; i < counter; i++){
        circles[i].draw();
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y){
    // Gets called mouse button is pressed or released

    // button:  0 - left button
    //          2 - right button
    
    // state:   0 - down
    //          1 - up

    // x:       the x coordinate of the mouse pointer in
    //          as int in the range [0..width]
    // y:       the y coordinate of the mouse pointer in
    //          as int in the range [0..height]

    // We need the mouse position in Cartesian coordinates
    // where x is in range [-1..1] and y from [-1..1]
    // with (0, 0) being the center of the window (origin)

    float mx = x;
    float my = y;
    windowToScene(mx, my);

    if (button == 0 && state == 0){

        bool onCircle = false;

        for (int i = 0; i < counter; i++){
            circles[i].selected = false;
        }
    
        for (int i = 0; i < counter; i++){
            if (circles[i].inside(mx, my)){
                cout << "Clicked on " << i << endl;
                circles[i].selected = true;
                onCircle = true;
                break;
            }
        }


        if (counter < 5 && !onCircle){
            circles[counter] = Circle(0.2, mx, my, r, g, b);
            counter++;
        }   
    }

    glutPostRedisplay();
    
}

void keyDown(unsigned char key, int x, int y){ 
    if (key == 'r'){
        r = 1;
        g = 0;
        b = 0;
    }

    if (key == 'g'){
        r = 0;
        g = 1;
        b = 0;
    }

    if (key == 'b'){
        r = 0;
        g = 0;
        b = 1;
    }
    if (key == 'k'){
        r = 0;
        g = 0;
        b = 0;
    }

    if (key == 27){
        exit(0);
    }

    glutPostRedisplay();
}

int main(int argc,char** argv) {
    // Perform some initialization
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("GLUT App");

    // Set the Display Function
    glutDisplayFunc(drawScene);

    // Set the mouse function
    glutMouseFunc(mouse);

    glutKeyboardFunc(keyDown);

    // Run the program
    glutMainLoop();

    return 0;
}