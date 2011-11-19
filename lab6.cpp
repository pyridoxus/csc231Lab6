/**********************************************************************
Lab 6

Description
-----------
Write a program to draw a solid GLUT primitive with an OpenGL material
lit with a single yellow point light. For selection purposes, draw the point
light in the scene as a simple, non-lit GLUT primitive. Allow the user to
toggle the point light on and off by selecting the light using the left mouse
button (using OpenGL selection). Draw the light as a white, wire primitive
when off and as a colored, solid primitive when on. Allow the user to translate
the light using the following special function keyboard controls:

Left Arrow  (GLUT_KEY_LEFT):			translate along -x axis
Right Arrow (GLUT_KEY_RIGHT):			translate along +x axis
Down Arrow  (GLUT_KEY_DOWN):			translate along -y axis
Up Arrow    (GLUT_KEY_UP):			  translate along +y axis
Page Up     (GLUT_KEY_PAGE_UP):   translate along -z axis
Page Down   (GLUT_KEY_PAGE_DOWN): translate along +z axis

Provide documentation describing your keyboard controls.
************************************************************************/

#include <iostream>
using namespace std;
#include <GL/glut.h>

float fov = 45.0;
float aspect = 1.333;
float nearClip = 0.01;
float farClip = 10000.0;

// Callback functions
void myDraw();
void keyboard( unsigned char, int, int );
void arrow( int, int, int );
void menu( int );
void mousePress( int, int, int, int );

int main( int argc, char **argv )
{
  // Initialize window system
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowSize( 640, 480 );
  glutCreateWindow( "Lab 7" );

  // Background color
  glClearColor( 0.0, 0.0, 0.0, 1.0 );

  // Projection and viewing
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( fov, aspect, nearClip, farClip );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glTranslatef( 0, 0, -20 );

  // Hidden surface
  glEnable( GL_DEPTH_TEST );

	// Specify shading model
  glShadeModel(GL_SMOOTH);

	// Define light
  GLfloat light_position[] = { 0.0, 1.0, 1.0, 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  // Enable lighting model
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // Callbacks
  glutDisplayFunc( myDraw );
  glutKeyboardFunc( keyboard );
	glutSpecialFunc( arrow );
  glutMouseFunc( mousePress );

  // Main loop
  glutMainLoop();
  return 0;
}

// Display callback
void myDraw()
{
	// Specify material properties

  // Clear
  glClearColor( 0.0, 0.0, 0.0, 1.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Draw light


  // Draw object


  // Swap buffers
  glutSwapBuffers();
}

// Arrow keys callback
void arrow( int key, int x, int y )
{
  // Process entries

	// Redraw the scene
  glutPostRedisplay();
}

// Keyboard callback
void keyboard( unsigned char key, int x, int y )
{
  // Process entries

  // Redraw the scene
  glutPostRedisplay();
}

// Mouse press callback
void mousePress( int button, int state, int x, int y )
{
  // Pick objects if left button down

}

