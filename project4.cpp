#include "project4.h"

int main( int argc, char *argv[] )
{
// Put the file paths back to a flatter system because I do not know if
// Windows will barf at the forward slashes and I do not have time to make this
// code check which OS it's using.
//	char temp[256];
//	string dataFileName(getcwd(temp, 255));
//	string colorFileName(getcwd(temp, 255));
//	dataFileName.append("Elevation.bin");
//	colorFileName.append("rainbow.pal");

//	string  dataFileName("Elevation.bin");
//	string  colorFileName("livingston.pal");
	string  dataFileName("BuckyBall.bin");
	string  colorFileName("rainbow.pal");
	cout << "Data file: " << dataFileName << endl;
	cout << "Color file: " << colorFileName << endl;
//	cout << "Setting up data reader" << endl;
	dr = new DataReader(dataFileName, colorFileName);
//	cout << "Building texture" << endl;
	texels = buildTexture();	// texels allocated here
//	cout << "Everything appears to work" << endl;
	setup(argc, argv);
	free(texels);
	free(dr);
	return 0;
}

GLubyte *buildTexture(void)
{
	unsigned int i, j;
	Color c;
	texels = new GLubyte[ dr->getGeoSize() ];	// texels is global

	cout.precision(6);
	// For each data value
	for( j = 0, i = 0; i < dr->getGeoSize() >> 2; ++i, j+=4 )
		{
			c = dr->at(i);
			// Assign data in r,g,b texture memory
			texels[j+0] = (GLubyte)(c.r * 255);
			texels[j+1] = (GLubyte)(c.g * 255);
			texels[j+2] = (GLubyte)(c.b * 255);
			texels[j+3] = 255;
//			cout << c.r << ", " << c.g << ", " << c.b << ", " << c.a << endl;
		}

	return texels;
}

void setup(int argc, char *argv[])
{
// Put the file paths back to a flatter system because I do not know if
// Windows will barf at the forward slashes and I do not have time to make this
// code check which OS it's using.
//	char temp[256];
//	string vertFileName(getcwd(temp, 255));
//	string fragFileName(getcwd(temp, 255));
//	vertFileName.append("/source/sample2d.vert");
//	fragFileName.append("/source/sample2d.frag");
	string vertFileName("sample3d.vert");
	string fragFileName("sample3d.frag");
	tx = ty = tz = axis = 0.0;

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize( 800, 600 );

	glutCreateWindow( "Craig McCulloch's Project 4" );

	// Resolves which OpenGL extensions are supported by hardware
	if( glewInit() != GLEW_OK )    {
		cerr << "Error reported by glewInit" << endl;
		exit(1);
	}

	// Orthographic projection
	// Projection
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( fov, aspect, nearClip, farClip );
	gluLookAt(1.7, 1.5, 2.3, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
	// Viewing
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef(-0.5, -0.5, -0.7);

	// Specify 3D RGBA texture
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glGenTextures( (unsigned int)1, (unsigned int *)&texName );
	glBindTexture( (unsigned int)GL_TEXTURE_3D, (unsigned int)texName );
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage3D( GL_TEXTURE_3D, 0, GL_RGBA, dr->getX(), dr->getY(), dr->getZ(),
			0, GL_RGBA, GL_UNSIGNED_BYTE, texels );

	// Create shader program
	shaderProgram1 = CreateProgram( vertFileName.c_str(), fragFileName.c_str() );

	// Locate address of shader sampler variable
	TexUnitLocation = glGetUniformLocation( shaderProgram1, "TexUnit" );

	// Assign sampler variable value texture unit 0
	glUniform1i( TexUnitLocation, TexUnit );

	// Callbacks
	glutDisplayFunc( myDraw );
	glutKeyboardFunc( keyboard );
	glutSpecialFunc( specialKeyFunc );

	glutCreateMenu( menu );
	glutAddMenuEntry( "View XY plane (or 'z' key)", 0 );
	glutAddMenuEntry( "View XZ plane (or 'y' key)", 1 );
	glutAddMenuEntry( "View YZ plane (or 'x' key)", 2 );
	glutAddMenuEntry( "Quit (or 'q' key)", 3 );
	glutAttachMenu( GLUT_RIGHT_BUTTON );

	// Main loop
	glutMainLoop();

}

// Display callback
void myDraw(void)
{
  // Clear the screen
  glClearColor( 0.0, 0.0, 0.0, 1.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  // Apply shader program
  glUseProgram( shaderProgram1 );

//  glColor3f(1.0, 0.5, 0.25);
//  cout << dr->getX() << endl;
//  cout << dr->getY() << endl;

  // Draw polygon with data dimensions
  glUseProgram( shaderProgram1 );
  glBegin( GL_POLYGON );
	switch(axis)
	{
		case 2:	// view yz plane (move along x)
			glTexCoord3f( tx, 0.0, 0.0 );
			glVertex3f( tx, 0.0, 0.0 );
			glTexCoord3f( tx, 1.0, 0.0 );
			glVertex3f( tx, 1.0, 0.0 );
			glTexCoord3f( tx, 1.0, 1.0 );
			glVertex3f( tx, 1.0, 1.0 );
			glTexCoord3f( tx, 0.0, 1.0 );
			glVertex3f( tx, 0.0, 1.0 );
		break;
		case 1:	// view xz plane (move along y)
			glTexCoord3f( 0.0, ty, 0.0 );
			glVertex3f( 0.0, ty, 0.0 );
			glTexCoord3f( 1.0, ty, 0.0 );
			glVertex3f( 1.0, ty, 0.0 );
			glTexCoord3f( 1.0, ty, 1.0 );
			glVertex3f( 1.0, ty, 1.0 );
			glTexCoord3f( 0.0, ty, 1.0 );
			glVertex3f( 0.0, ty, 1.0 );
		break;
		case 0:	// view xy plane (move along z)
			glTexCoord3f( 0.0, 0.0, tz );
			glVertex3f( 0.0, 0.0, tz );
			glTexCoord3f( 1.0, 0.0, tz );
			glVertex3f( 1.0, 0.0, tz );
			glTexCoord3f( 1.0, 1.0, tz );
			glVertex3f( 1.0, 1.0, tz );
			glTexCoord3f( 0.0, 1.0, tz );
			glVertex3f( 0.0, 1.0, tz );
		break;
	}
  glEnd();

  drawCage();

  // Swap buffers
  glutSwapBuffers();
}

void keyboard( unsigned char key, int x, int y )
{
	switch(key)
	{
		case 'x':
		case 'X':
			axis = 2;	// view yz plane (move along x)
		break;
		case 'y':
		case 'Y':
			axis = 1;	// view xz plane (move along y)
		break;
		case 'z':
		case 'Z':
			axis = 0;	// view xy plane (move along z)
		break;
		case 'q':
			exit(1);
		break;
	}
	// Redraw the scene
  glutPostRedisplay();
	return;
}

void specialKeyFunc( int key, int x, int y )
{
	double a;
	switch(key)
	{
		case GLUT_KEY_DOWN:
			a = -0.01;
		break;
		case GLUT_KEY_UP:
			a = 0.01;
		break;
	}
	switch(axis)
	{
		case 2:
			tx += a;
			if(tx < 0.0) tx = 0.0;
			if(tx > 1.0) tx = 1.0;
		break;
		case 1:
			ty += a;
			if(ty < 0.0) ty = 0.0;
			if(ty > 1.0) ty = 1.0;
		break;
		case 0:
			tz += a;
			if(tz < 0.0) tz = 0.0;
			if(tz > 1.0) tz = 1.0;
		break;
	}
	cout << "Axis: " << axis << " tx: " << tx << " ty: ";
	cout << ty << " tz: " << tz << endl;
	// Redraw the scene
  glutPostRedisplay();
	return;
}

void menu( int value )
{
	switch(value)
	{
		case 0:
		case 1:
		case 2:
			axis = value;
		break;
		case 3:
			exit(1);
		break;
	}
  // Redraw the scene
  glutPostRedisplay();
	return;
}

void drawCage(void)
{
	glUseProgram( 0 );
	glLineWidth(0.0);
	glColor3f( 1.0, 1.0, 1.0);
	glEnable (GL_LINE_SMOOTH);
	glBegin( GL_LINE_LOOP );
	glVertex3f( 0.0, 0.0, 0.0 );
	glVertex3f( 1.0, 0.0, 0.0 );
	glVertex3f( 1.0, 1.0, 0.0 );
	glVertex3f( 0.0, 1.0, 0.0 );
	glEnd();
	glBegin( GL_LINE_LOOP );
	glVertex3f( 0.0, 0.0, 1.0 );
	glVertex3f( 1.0, 0.0, 1.0 );
	glVertex3f( 1.0, 1.0, 1.0 );
	glVertex3f( 0.0, 1.0, 1.0 );
	glEnd();
	glBegin( GL_LINES );
	glVertex3f( 0.0, 0.0, 0.0 );
	glVertex3f( 0.0, 0.0, 1.0 );
	glVertex3f( 1.0, 0.0, 0.0 );
	glVertex3f( 1.0, 0.0, 1.0 );
	glVertex3f( 1.0, 1.0, 0.0 );
	glVertex3f( 1.0, 1.0, 1.0 );
	glVertex3f( 0.0, 1.0, 0.0 );
	glVertex3f( 0.0, 1.0, 1.0 );
	glEnd();
	// Border around the slice
	glBegin( GL_LINE_LOOP );
	switch(axis)
	{
		case 2:	// view yz plane (move along x)
			glVertex3f( tx, 0.0, 0.0 );
			glVertex3f( tx, 1.0, 0.0 );
			glVertex3f( tx, 1.0, 1.0 );
			glVertex3f( tx, 0.0, 1.0 );
		break;
		case 1:	// view xz plane (move along y)
			glVertex3f( 0.0, ty, 0.0 );
			glVertex3f( 1.0, ty, 0.0 );
			glVertex3f( 1.0, ty, 1.0 );
			glVertex3f( 0.0, ty, 1.0 );
		break;
		case 0:	// view xy plane (move along z)
			glVertex3f( 0.0, 0.0, tz );
			glVertex3f( 1.0, 0.0, tz );
			glVertex3f( 1.0, 1.0, tz );
			glVertex3f( 0.0, 1.0, tz );
		break;
	}
	glEnd();
	return;
}
