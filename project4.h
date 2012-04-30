#ifndef PROJECT4_H_
#define PROJECT4_H_

using namespace std;
#include "DataReader.h"
using namespace DataFileReader;
#include "GLSL.h"

#define MAX_STR                   256
GLuint texName;                   // texture name
GLuint shaderProgram1;            // shader program handle
GLint TexUnit = 0;                // texture unit shader attribute
GLint TexUnitLocation;            // texture unit shader attribute location
GLubyte *texels;
DataReader *dr;
double tx, ty, tz;
int axis;
float fov = 30.0;
float aspect = 1.333;
float nearClip = 0.01;
float farClip = 10000.0;

GLubyte *buildTexture();
// Callback function
void myDraw(void);
void keyboard( unsigned char, int, int );
void specialKeyFunc( int key, int x, int y );
void menu( int );
void drawCage(void);
void setup(int argc, char *argv[]);
void showMenu(void);

#endif /* PROJECT4_H_ */
