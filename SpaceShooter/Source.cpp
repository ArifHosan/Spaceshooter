#include <stdlib.h>
#include <glut.h>
#include <gl/GL.h>
#include <iostream>
#include "SpaceshipU1.h"
#include "SpaceshipU2.h"
#include "SpaceshipE1.h"

#include "GenerateTexture.h"

using namespace std;
 
double _angle = 0.0; // rotating angle of the road (cylinder)
double _angleWheel = 0.0; // rotating angle of wheels (torus)

double center_x, center_y = 0.0; // Object co-ordinates in 3D
double center_z = -10.0; // Object z co-ordinates in 3D to make it visible

						 // Camera Position with co-ordinates in 3D
double eye_x = 0.0;
double eye_y = 6.0;
double eye_z = 5.0;

double angle_axis_x = 0.0;
double angle_axis_y = 1.0;
double angle_axis_z = 0.0;


void DrawU1() {
	SpaceshipModel_U1* spaceship1 = new SpaceshipModel_U1(1, "G2 G2 G2", "Pluto");

	glPushMatrix();
	glRotatef(_angle, angle_axis_x, angle_axis_y, angle_axis_z);
	spaceship1->DrawModel();
	glPopMatrix();

	delete spaceship1;
}

void DrawU2() {
	SpaceshipModel_U2* spaceship2 = new SpaceshipModel_U2(1, "G2 G2 G2", "Pluto");

	glPushMatrix();
	glRotatef(_angle, angle_axis_x, angle_axis_y, angle_axis_z);
	spaceship2->DrawModel();
	glPopMatrix();

	delete spaceship2;
}

void DrawE1() {
	SpaceshipModel_E1* spaceship2 = new SpaceshipModel_E1(1, "G2 G2 G2", "Pluto");

	glPushMatrix();
	glRotatef(_angle, angle_axis_x, angle_axis_y, angle_axis_z);
		spaceship2->DrawModel();
	glPopMatrix();

	delete spaceship2;
}

void DrawSpaceshipModel() {

	DrawU1();

	//DrawE1();

}

// Main Draw Function
void Draw() {
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Changed to automatically calculate the depth of the objects
	glEnable(GL_DEPTH_TEST);
	// ---------------------------------------------------------------------------------------------------------------

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye_x, eye_y, eye_z, center_x, center_y, center_z, 0.0, 1.0, 0.0); // Camera Initialization in 3D Perspective (Editable)

	glPushMatrix();
	glTranslatef(0.0, 0.0, -7.0); // Placing the road in the 3D Perspective to make it visible
	DrawSpaceshipModel(); // Drawing the spaceship model
	glPopMatrix();


	glFlush();
}



// Rotation Updating Function
void update(int val) {
	_angle += 0.2; // rotation angle for road
	_angleWheel += -0.5; // rotation angle for wheels (Which is opposite of the road)

	glutPostRedisplay();
	glutTimerFunc(5, update, 0);
}

// Move Screen Function - Left, Right, Up & Down (By Changing Object's position from the camera)
void MoveScreen(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		center_x -= 0.10;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		center_x += 0.10;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		center_y -= 0.10;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		center_y += 0.10;
		glutPostRedisplay();
		break;
	}
}


// Move Camera Function - left & right (By changing the camera position to look in side views of the scene)
void MoveCamera(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		eye_x -= 0.20;
		//eye_z = 1.0;
		glutPostRedisplay();
		break;
	case 'd':
		eye_x += 0.20;
		//eye_z = 1.0;
		glutPostRedisplay();
		break;
	case 'u':
		angle_axis_x = 1.0;
		angle_axis_y = 0.0;
		angle_axis_z = 0.0;

		glutPostRedisplay();
		break;
	case 's':
		angle_axis_x = 0.0;
		angle_axis_y = 1.0;
		angle_axis_z = 0.0;

		glutPostRedisplay();
		break;
	case 'p':
		angle_axis_x = 0.0;
		angle_axis_y = 0.0;
		angle_axis_z = 1.0;

		glutPostRedisplay();
		break;
	}
}

// Zoom In & Zoom Out Function - Mouse Left Button & Right Button (By Changing the camera postion along z axis to make the scene bigger and smaller)
void ZoomInOut(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
	{
		eye_z += 1.00;
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		eye_z -= 1.00;
	}

	glutPostRedisplay();
}

// Setting up the light Function
void LightSettings() {
	float lightAmbient[4] = { 0.0, 0.0, 0.0, 1.0 }; // No Artificial ambient color
	float lightDiffuse[4] = { 1.0, 1.0, 1.0, 1.0 }; // pure diffuse 
	float lightSpecular[4] = { 1.0, 1.0, 1.0, 0.25 }; // pure specular with little bit of adjusted smoothness

	float lightPosition[4] = { 17.0, 10.0, 0.0, 1.0 }; // setting up the light position

	glEnable(GL_LIGHTING); // Enabling the light system
	glEnable(GL_LIGHT0); // Using LIGHT0 by enabling it


	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient); // defining ambient color for LIGHT0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse); // defining diffuse color for LIGHT0
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular); // defining specular color for LIGHT0

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); // defining light position for LIGHT0


													  // for existing amount of ambient and diffusal on object 
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// -----------------------------------------------------

	float materialSpecular[4] = { 1.0, 1.0, 1.0, 1.0 }; // pure specular 
	float materialShininess[1] = { 50.0 }; // shininess for each materials

	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular); // defining specular color for objects
	glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess); // defining shininess for objects
	
}


void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);

	gluPerspective(45.0, 1.00, 1.0, 20.0); // Making 3D Perspective with aspect ratio, near, far and angle
}

int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("OpenGL Project");
	Initialize();

	// Set the lighiting
	LightSettings();

	// Draw Objects
	glutDisplayFunc(Draw);

	// Animate Objects
	//glutTimerFunc(5, update, 0);

	// Action Events
	glutSpecialFunc(MoveScreen);
	glutKeyboardFunc(MoveCamera);
	glutMouseFunc(ZoomInOut);

	glutMainLoop();
	return 0;
}