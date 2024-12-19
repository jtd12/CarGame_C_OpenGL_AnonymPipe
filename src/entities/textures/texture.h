#ifndef TEXTURE_H
#define TEXTURE_H
#include<GL/gl.h>
#include<GL/glu.h>

#define GL_BGR 0x80E0



extern GLuint texture_;
extern int hudTex;
extern int hudTex2;
extern int hudTex3;
extern int hudTex4;
// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath);




#endif
