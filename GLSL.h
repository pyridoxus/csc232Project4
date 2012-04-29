#ifndef GLSL_H_
#define GLSL_H_

#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

// GLSL API functions
GLuint CreateProgram( std::string, std::string );
GLuint CreateShader( GLenum, std::string );
void CheckGlErrors( const char * );
int LinkProgram( GLuint );

#endif /* GLSL_H_ */
