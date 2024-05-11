#ifndef TEXTURE_RECT
#define TEXTURE_RECT
#include <GL/freeglut.h>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

struct TextureRect{
    float x;
    float y;
    float w;
    float h;
    std::string filename;

    unsigned char * data; // String
    int image_w = 100;
    int image_h = 100;
    int bitdepth = 4;
    GLuint texture;


    TextureRect(){}

    TextureRect(std::string filename, float x, float y, float w, float h){
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->filename = filename;

        // Start texture load
        data = stbi_load("assets/pencil.png", &image_w, &image_h, &bitdepth, STBI_rgb_alpha);

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
    }

    void draw(){
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
    }

};


#endif