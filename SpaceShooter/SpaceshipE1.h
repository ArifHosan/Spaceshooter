#pragma once

#include <iostream>
#include "glut.h"
#include "SpaceshipsModel.h"
#include "GenerateTexture.h"

using namespace std;

class SpaceshipModel_E1 : SpaceshipModel {
private:


public:
	void DrawModel();
	
	SpaceshipModel_E1(unsigned short int ID, string NAME, string MOTHERLAND) : SpaceshipModel(ID, NAME, MOTHERLAND) {

	}

};

GLUquadricObj *quadratic = gluNewQuadric(); // New Quadric Object for Initializing cylinder
/*double clip_plane1[] = { 0.0,0.0,1.0,0.5 };
glClipPlane(GL_CLIP_PLANE1, clip_plane1);
glEnable(GL_CLIP_PLANE1);
glDisable(GL_CLIP_PLANE1);*/


void DrawSubWing() {
	
	// body
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(0.0, 0.0, 1.0);
	glScalef(1.0, 1.0, 1.0);
	gluCylinder(quadratic, 0.30, 0.25, 4.0, 100, 100);
	glPopMatrix();

	// Head
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(0.0, 1.0, 1.0);
	glScalef(1.0, 1.0, 1.0);
	glutSolidSphere(0.25, 100, 100);
	glPopMatrix();

	// Back
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(0.0, 1.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	gluCylinder(quadratic, 0.25, 0.20, 4.0, 100, 100);
	glPopMatrix();
	
}

void DrawMainWing() {

	

	
	
	
	
	// body
	glPushMatrix();
	glTranslatef(0, 0, 0);
	//glColor3f(0.0, 0.0, 1.0);
	glScalef(1.0, 1.0, 1.0);
	GenerateTexture* newfitex = new GenerateTexture("camo.bmp");
	
	gluQuadricTexture(newfitex->getQuadricObject(), 1);
	gluCylinder(newfitex->getQuadricObject(), 0.80, 0.50, 4.0, 100, 100);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDeleteTextures(1, newfitex->getTexture());
	//glDisable(GL_TEXTURE_2D);
	delete newfitex;
	glPopMatrix();
	glutPostRedisplay();
	
	// Head
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(0.0, 1.0, 1.0);
	glScalef(1.0, 1.0, 1.0);
	glutSolidSphere(0.80, 100, 100);
	glPopMatrix();

	// Back
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(0.0, 1.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	gluCylinder(quadratic, 0.45, 0.45, 4.0, 10, 10);
	glPopMatrix();

}

void DrawSubJunction() {
	glPushMatrix();
	glColor3f(0.50, 1.0, 1.0);
	glScalef(4.0, 0.20, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void DrawMainJunction() {
	glPushMatrix();
	glColor3f(0.50, 1.0, 1.0);
	glScalef(0.80, 0.80, 0.50);
	glutSolidCube(1.0);
	glPopMatrix();
}

void DrawWholeBody() {

	// bottom
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glScalef(1.0, 0.20, 1.0);
	glutSolidSphere(4.0, 100, 100);
	glPopMatrix();

	// mid
	glPushMatrix();
	glTranslatef(0.0, 0.20, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glScalef(1.0, 0.30, 1.0);
	glutSolidSphere(3.50, 100, 100);
	glPopMatrix();

	// top
	glPushMatrix();
	glTranslatef(0.0, 0.30, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glScalef(1.0, 0.50, 1.0);
	glutSolidSphere(2.50, 100, 100);
	glPopMatrix();

	// Cylinder
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glColor3f(0.50, 1.0, 0.70);
	glScalef(1.0, 1.0, 1.0);
	gluCylinder(quadratic, 4.0, 3.90, 0.50, 100, 100);
	glPopMatrix();

	// Bottom Surface
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glScalef(1.0, 0.0, 1.0);
	glutSolidSphere(4.0, 100, 100);
	glPopMatrix();
	
}


void SpaceshipModel_E1::DrawModel()
{
	

	

	glPushMatrix();
	glTranslatef(0.0, 1.80, -2.80);
	DrawWholeBody();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.0, 3.0, 0.0);
	DrawSubWing();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0, 3.0, 0.0);
	DrawSubWing();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	DrawMainWing();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 1.50, 2.0);
	glRotatef(60.0, 0.0, 0.0, 1.0);
	glRotatef(30.0, 0.0, 1.0, 0.0);
	DrawSubJunction();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 1.50, 2.0);
	glRotatef(-60.0, 0.0, 0.0, 1.0);
	glRotatef(-30.0, 0.0, 1.0, 0.0);
	DrawSubJunction();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.03, 1.0, 0.70);
	DrawMainJunction();
	glPopMatrix();
}