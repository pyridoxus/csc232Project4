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
