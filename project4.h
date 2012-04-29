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

GLubyte *buildTexture();
// Callback function
void myDraw(void);
void keyboard( unsigned char, int, int );
void specialKeyFunc( int key, int x, int y );
void menu( int );

void setup(int argc, char *argv[]);

#endif /* PROJECT4_H_ */
