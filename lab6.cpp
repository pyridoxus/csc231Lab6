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

// Light properties
GLfloat light_diffuse[] = { 0.7, 0.7, 0.2, 1.0 };
GLfloat light_ambient[] = { 0.05, 0.05, 0.05, 1.0 };

// Light object properties
GLfloat ob_diffuse_on[] = { 0.7, 0.7, 0.2, 1.0 };
GLfloat ob_diffuse_off[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat ob_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat ob_ambient_on[] = { 7.0, 7.0, 2.0, 1.0 };
GLfloat ob_ambient_off[] = { 7.0, 7.0, 7.0, 1.0 };

// Specify material properties
GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
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
void clickableScene(int x, int y);
void showInstructions(void);

void showInstructions(void)
{
	cout << "To move the light, follow these instructions:" << endl;
	cout << "Left Arrow:  translate along -x axis" << endl;
	cout << "Right Arrow: translate along +x axis" << endl;
	cout << "Down Arrow:  translate along -y axis" << endl;
	cout << "Up Arrow:    translate along +y axis" << endl;
	cout << "Page Up:     translate along -z axis" << endl;
	cout << "Page Down:   translate along +z axis" << endl;
	cout << "q:           quit program" << endl;
	return;
}

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
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  // Enable lighting model
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // Callbacks
  glutDisplayFunc( myDraw );
  glutKeyboardFunc( keyboard );
	glutSpecialFunc( arrow );
  glutMouseFunc( mousePress );

  showInstructions();
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
  if(glIsEnabled(GL_LIGHT0))
  {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ob_diffuse_on);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ob_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ob_ambient_on);
    glutSolidSphere( 0.5, 10, 10 );
  }
  else
  {
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ob_diffuse_off);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ob_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ob_ambient_off);
		glutWireSphere(0.5, 10, 10);
  }
  glPopMatrix();
  glPushMatrix();
  glLoadName( SPHERE );      // Load picking id
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  // Draw object
  glutSolidSphere( 3.0, 100, 100 );

  glPopMatrix();
  // Swap buffers
  glutSwapBuffers();
  return;
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
  return;
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
  return;
}

// Mouse press callback
void mousePress( int button, int state, int x, int y )
{
	if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) clickableScene(x, y);
  return;
}

void clickableScene(int x, int y)
{
// Pick objects if left button down
	GLuint selectBuffer[ SELECT_BUFSIZE ];     // selections
	GLuint *ptr, names;
	int hits, i;
	unsigned int j;

	// Viewport information
	GLint viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );

	// Selection mode
	glSelectBuffer( SELECT_BUFSIZE, selectBuffer );
	glRenderMode( GL_SELECT );

	// Initialize name stack
	glInitNames();
	glPushName(-1);

	// Save transformation matrix
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	// Save original projection (viewing volume)
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();

	// New picking viewing volume (area == 5 pixels)
	glLoadIdentity();
	gluPickMatrix(GLdouble(x), GLdouble(viewport[3] - y),	5.0, 5.0, viewport);
	gluPerspective( fov, aspect, nearClip, farClip );

	// Draw scene
	myDraw();

	// Restore original projection (viewing volume)
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	// Restore original modelview matrix
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	// Swap buffers
	glutSwapBuffers();

	// End select mode
	hits = glRenderMode( GL_RENDER );

	// Process hits
	lightPicked = 0;
	ptr = (GLuint *)selectBuffer;
	for (i = 0; i < hits; i++)
	{
		 // First item - number of names of stack during hit
		 names = *ptr;
		 ptr++;
// Remaining items - hit records
		 for (j = 0; j < names; j++)
		 {
				if( ptr[2] == LIGHT )
				{
				  if(glIsEnabled(GL_LIGHT0))
					  glDisable(GL_LIGHT0);
				  else
					  glEnable(GL_LIGHT0);
				  lightPicked = 1;
				}
				if( ptr[2] == SPHERE ) spherePicked = 1;
				ptr += 3;
		 }
	}
	// Redisplay
	glutPostRedisplay();
	return;
}
