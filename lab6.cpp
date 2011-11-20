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
#include <stdlib.h>
#define LIGHT 1
#define SPHERE 2
#define SELECT_BUFSIZE  10

float fov = 45.0;
float aspect = 1.333;
float nearClip = 0.01;
float farClip = 10000.0;

// Initial light position
GLfloat light_position[] = { 5.0, 5.0, 5.0, 0.0 };

// Light diffuse
GLfloat light_diffuse[] = { 0.7, 0.7, 0.2, 1.0 };

// Light object properties
// Other properties are the same as light_diffuse
GLfloat ob_diffuse[] = { 0.7, 0.7, 0.2, 1.0 };
GLfloat ob_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat ob_ambient[] = { 7.0, 7.0, 2.0, 1.0 };

// Specify material properties
GLfloat ambient[] = { 0.05, 0.05, 0.05, 1.0 };
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess[] = { 100.0 };

// Selection data
int lightPicked = 0;
int spherePicked = 0;	// Just for fun and debugging

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
  glutCreateWindow( "Lab 6" );

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
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
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
  // Clear
  glClearColor( 0.0, 0.0, 0.0, 1.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glPushMatrix();
  glLoadName( LIGHT );      // Load picking id
  glTranslatef( light_position[0], light_position[1], light_position[2] );
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	// Draw light
  glMaterialfv(GL_FRONT, GL_DIFFUSE, ob_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, ob_specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ob_ambient);
  if(glIsEnabled(GL_LIGHT0))
    glutSolidSphere( 0.5, 10, 10 );
  else
		glutWireSphere(1.0, 10, 10);
  glPopMatrix();
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  // Draw object
  glutSolidSphere( 3.0, 100, 100 );


  glPopMatrix();
  // Swap buffers
  glutSwapBuffers();
}

// Arrow keys callback
void arrow( int key, int x, int y )
{
  // Process entries
	switch(key)
	{
		case GLUT_KEY_LEFT:			// translate along -x axis
			light_position[0]--;
		break;
		case GLUT_KEY_RIGHT:		// translate along +x axis
			light_position[0]++;
		break;
		case GLUT_KEY_DOWN:			// translate along -y axis
			light_position[1]--;
		break;
		case GLUT_KEY_UP:			  // translate along +y axis
			light_position[1]++;
		break;
		case GLUT_KEY_PAGE_UP:  // translate along -z axis
			light_position[2]--;
		break;
		case GLUT_KEY_PAGE_DOWN:// translate along +z axis
			light_position[2]++;
		break;
	}
	// Redraw the scene
  glutPostRedisplay();
}

// Keyboard callback
void keyboard( unsigned char key, int x, int y )
{
  // Process entries
	switch(key)
	{
		case 'q':
			exit(1);
		break;
	}
  // Redraw the scene
  glutPostRedisplay();
}

// Mouse press callback
void mousePress( int button, int state, int x, int y )
{
  // Pick objects if left button down

}

