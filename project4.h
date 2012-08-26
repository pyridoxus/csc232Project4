//This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
