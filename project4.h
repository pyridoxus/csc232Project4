#ifndef LAB8_H_
#define LAB8_H_

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

GLubyte *buildTexture();
// Callback function
void myDraw(void);

void setup(int argc, char *argv[]);

#endif
/*
 * project4.h
 *
 *  Created on: Apr 29, 2012
 *      Author: pyridoxus
 */

#ifndef PROJECT4_H_
#define PROJECT4_H_




#endif /* PROJECT4_H_ */
