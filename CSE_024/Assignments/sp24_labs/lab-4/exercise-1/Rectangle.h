    #ifndef Rectangle_H
    #define Rectangle_H

    #include <GL/freeglut.h>
    #include <GL/gl.h>
    #include <cmath>

    struct Rectangle {
    float w;
    float h;
    float x;
    float y;

    float r;
    float g;
    float b;

    Rectangle() {
        x = 0;
        y = 0;
        w = 0.4;
        h = 0.2;
        r = 0;
        g = 0;
        b = 1;
    }




    Rectangle(float x, float y, float w, float h, float r, float g, float b) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->r = r;
        this->g = g;
        this->b = b;
    }

    void draw() {
        glColor3f(r, g, b);
        glBegin(GL_POLYGON);

        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y - h);
        glVertex2f(x, y - h);

        glEnd();
    }

    void drawShape(){
        glColor3f(r, g, b);
        glBegin(GL_LINES);

        glVertex2f(x,y);
        glVertex2f(x+w,y);

        glVertex2f(x+w,y);
        glVertex2f(x+w, y-h);

        glVertex2f(x+w, y-h);
        glVertex2f(x,y-h);

        glVertex2f(x, y-h);
        glVertex2f(x,y);

        glEnd(); 


    }

        void setColor(float r, float g, float b){
            this->r = r; 
            this->g = g; 
            this->b = b; 
        }

        void resize(float s){
            w = w*s;
            h = h*s; 
        }

    bool inside(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
        return true;
        } else {
        return false;
        }
    }

    void ifSelected(){
        float recCenterX = x + (w/2);
        float recCenterY = y - (h/2);

        glColor3f(0, 0, 0);
        glPointSize(4);
        glBegin(GL_POINTS);
        glVertex2f(recCenterX, recCenterY);
        glEnd();
    }


    };

    struct Circle{
        float x,y,rad,r,g,b;
        float w;
    float h;
        Circle(){
            x=0; 
            y=0; 
            rad=0;
            r=0;
            g=0;
            b=0;
        }
        Circle(float x, float y, float rad, float r, float g, float b){
            this->x = x;
            this->y = y;
            this->rad = rad;
            this->r = r;
            this->g = g;
            this->b = b;
        }

        void drawShape(){
            glColor3f(r,g,b);
            glBegin(GL_LINE_LOOP);

            for(int k =0; k<360; k++){
                float radians = (k * 3.14159265358979323846264338) / 180; 
                glVertex2f((x + cos(radians) * rad), (y + sin(radians) * rad));
                float cx = x + cos(radians) * rad; 
                float cy = y + sin(radians) * rad; 
            }

            glEnd();
        }

        void setColor(float r, float g, float b){
            this->r = r; 
            this->g = g; 
            this->b = b; 
        }

        void resize(float s){
            rad = rad * s;
        }
        

        bool inside(float mx, float my) {
    /* if (mx >= x-w && mx <= x + w && my <= cy && my>= (cy-2y)) {
        return true;
        } else {
        return false;
        } */

        float distance = sqrt((mx - x) * (mx -x) + (my-y) * (my-y));
        return distance <= rad; 
    }

    void ifSelected(){
        glColor3f(0,0,0);
        glPointSize(4);
        glBegin(GL_POINTS);
        glVertex2f(x,y);
        glEnd();
    }
    };

    struct Triangle{
        float x1, y1, x2, y2, x3, y3, r, g, b, w, y, h; 

        Triangle(){
            x1 =0; 
            y1 = 0; 
            x2 = 0.1; 
            y2 = 0.1; 
            x3 = -0.1; 
            y3 = 0.1; 
            r = 1; 
            g = 1; 
            b = 1;
        }

        Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b){
            this->x1 = x1; 
            this->y1 = y1; 
            this->x2 = x2; 
            this->y2 = y2;
            this->x3 = x3; 
            this->y3=y3;
            this->r = r;
            this->g = g; 
            this->b = b; 
        }

        void drawShape(){
            glColor3f(r,g,b);
            glBegin(GL_LINES);

            glVertex2f(x1,y1);
            glVertex2f(x2,y2);
            
            glVertex2f(x2,y2);
            glVertex2f(x3,y3);

            glVertex2f(x3,y3); 
            glVertex2f(x1,y1); 
        }

        void setColor(float r, float g, float b){
            this->r = r; 
            this->g = g; 
            this->b = b; 
        }

        void resize(float s){
            x2 = x1 + (s * (x2-x1));
            y2 = y1 + (s * (y2-y1));
            x3 = x1 + (s * (x3 - x1));
            y3 = y1 + (s * (y3-y1));
        }

        bool inside(float mx, float my) {
        if (mx >= x1 && mx <= x3 && my >= y1 && my <= y2) {
        return true;
        } else {
        return false;
        }
        }

        void ifSelected(){
            float triCenterX = (x1 + x2 + x3) / 3;
            float triCenterY = (y1+y2+y3) / 3; 
            glColor3f(0,0,0);
            glPointSize(4);
            glBegin(GL_POINTS);
            glVertex2f(triCenterX, triCenterY);
            glEnd();
        }
    };

    #endif