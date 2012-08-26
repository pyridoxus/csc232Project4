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
#include "GLSL.h"
using namespace std;
// Function to create shader program
GLuint CreateProgram( string vertfname, string fragfname )
{
  // Create vertex and fragment shaders
  GLuint vertShader = CreateShader( GL_VERTEX_SHADER,   vertfname );
  GLuint fragShader = CreateShader( GL_FRAGMENT_SHADER, fragfname );

  // Attach shaders to shader program
  GLuint program = glCreateProgram();
  glAttachShader( program, vertShader );
  glAttachShader( program, fragShader );

  // Link shader program
  LinkProgram( program );

  // Return handle to program
  return program;
}

// Function to create shader object
GLuint CreateShader( GLenum type, string fname )
{
  // Create shader object
  GLuint shader = glCreateShader( type );

  // Read shader source file
  ifstream is;
       is.open( fname.c_str(), ios::in | ios::binary );
  long begin = is.tellg();              // size of file plus a byte for null termination
  is.seekg( 0, ios::end );
  long end = is.tellg();
       int bsize = end-begin+1;
  is.seekg( 0, ios::beg );
  char *str = new char[ bsize ];        // allocate read all bytes in file
  is.read( str, bsize-1 );
       str[ bsize-1] = '\0';
       is.close();

  // Load shader source into shader object
  glShaderSource( shader, 1, (const GLchar **)&str, NULL );
  if( str ) delete[] str;

  // Compile shader object and check for errors
  glCompileShader( shader );
  CheckGlErrors( "Compile Shader:");
  int status, infoLogLen;
  glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
  if( !status )
    {
      cerr << "Shader compilation error: " << fname.c_str() << endl;
      glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLogLen );
      if( infoLogLen > 0)
        {
          GLchar *infoLog = new GLchar[infoLogLen+1];
          glGetShaderInfoLog( shader, infoLogLen, NULL, infoLog);
          infoLog[infoLogLen] = '\0';
          cerr << infoLog << endl;
          delete[] infoLog;
        }
      glDeleteShader( shader );
      exit(1);
    }
  CheckGlErrors("LoadShader:Compile 2");

  // Return handle to shader object
  return shader;
}

// Check OpenGL errors (from Graphics Shaders textbook)
void CheckGlErrors( const char* caller )
{
  unsigned int gle = glGetError();

  if( gle != GL_NO_ERROR )
    {
      fprintf( stderr, "GL Error discovered from caller %s: ", caller );
      switch (gle)
        {
        case GL_INVALID_ENUM:
          fprintf( stderr, "Invalid enum.\n" );
          break;
        case GL_INVALID_VALUE:
          fprintf( stderr, "Invalid value.\n" );
          break;
        case GL_INVALID_OPERATION:
          fprintf( stderr, "Invalid Operation.\n" );
          break;
        case GL_STACK_OVERFLOW:
          fprintf( stderr, "Stack overflow.\n" );
          break;
        case GL_STACK_UNDERFLOW:
          fprintf(stderr, "Stack underflow.\n" );
          break;
        case GL_OUT_OF_MEMORY:
          fprintf( stderr, "Out of memory.\n" );
          break;
        }
      return;
    }
}

// Link shader program (from Graphics Shaders textbook)
int LinkProgram( GLuint program )
{
  glLinkProgram( program );
  CheckGlErrors("LoadShader:Link 1");

  GLchar* infoLog;
  GLint infoLogLen;
  GLint linkStatus;
  glGetProgramiv( program, GL_LINK_STATUS, &linkStatus );
  CheckGlErrors("LoadShader:Link 2");

  if( linkStatus == 0 )
    {
      glGetProgramiv( program, GL_INFO_LOG_LENGTH, &infoLogLen );
      cerr << "Failed to link program -- Info Log Length = " << infoLogLen << endl;
      if( infoLogLen > 0 )
        {
          infoLog = new GLchar[infoLogLen+1];
          glGetProgramInfoLog( program, infoLogLen, NULL, infoLog );
          infoLog[infoLogLen] = '\0';
          cerr << "Info Log: " << infoLog << endl;
          delete[] infoLog;
        }
      glDeleteProgram( program );
      return 0;
    }
  return 1;
};




