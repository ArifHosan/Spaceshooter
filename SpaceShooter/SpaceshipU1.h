#pragma once

#include <iostream>
#include "glut.h"
#include "SpaceshipsModel.h"
#include "imageloader.h"
#include "GenerateTexture.h"

using namespace std;

class SpaceshipModel_U1 : SpaceshipModel {
private:
	string PrePath;

public:
	void DrawModel();
	void DrawLeftFireArm();
	void DrawRightFireArm();
	void DrawOuterBody();
	void DrawInnerBody();
	void DrawBlockers();
	

	SpaceshipModel_U1(unsigned short int ID, string NAME, string MOTHERLAND) : SpaceshipModel(ID, NAME, MOTHERLAND) {
		this->PrePath = "Textures/SpaceshipU1/";
	}
};

GLUquadricObj *quadratico = quadratico = gluNewQuadric(); // New Quadric Object for Initializing cylinder

void SpaceshipModel_U1::DrawLeftFireArm() {
	


	// 1st Part
	glPushMatrix();
		glTranslatef(-1, 0, 0);
		//glColor3f(0.0, 0.0, 1.0);
		//GenerateTexture* newTex = new GenerateTexture((this->PrePath += "U1_FireArm_Body.bmp").c_str());
		GenerateTexture* newTex1 = new GenerateTexture("Textures/SpaceshipU1/U1_Arm_Body1.bmp");

		gluQuadricTexture(newTex1->getQuadricObject(), 1);
		gluCylinder(newTex1->getQuadricObject(), 0.40, 0.50, 2.0, 10, 10);

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		delete newTex1;
	glPopMatrix();

	// 2nd Part
	glPushMatrix();
	glTranslatef(-1, 0, 2.0);
	//glColor3f(1.0, 0.0, 0.0);
	GenerateTexture* newTex2 = new GenerateTexture("Textures/SpaceshipU1/U1_Arm_Mid.bmp");

	gluQuadricTexture(newTex2->getQuadricObject(), 1);
	gluCylinder(newTex2->getQuadricObject(), 0.50, 0.40, 0.40, 10, 10);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	delete newTex2;
	glPopMatrix();


	// 3rd Part
	glPushMatrix();
	glTranslatef(-1, 0, 2.10);
	glColor3f(0.0, 1.0, 0.0);
	gluCylinder(quadratico, 0.40, 0.40, 1.0, 10, 10);
	glPopMatrix();

	// 4th Part
	glPushMatrix();
	glTranslatef(-1, 0, 2.90);
	glColor3f(1.0, 1.0, 1.0);
	gluCylinder(quadratico, 0.39, 0.39, 0.60, 10, 10);
	glPopMatrix();

}

void SpaceshipModel_U1::DrawRightFireArm() {
	this->DrawLeftFireArm();
}

void SpaceshipModel_U1::DrawOuterBody() {
	glPushMatrix();
	glTranslatef(0, 0, 0.90);
	glColor3f(0.50, 0.70, 0.0);
	glScalef(5.00, 6.0, 20.0);
	glutSolidTorus(0.02, 0.40, 100, 100);
	//gluCylinder(quadratic, 2.00, 2.00, 0.60, 100, 100);
	glPopMatrix();

	/*
	//Triangle
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 4.00);
	glColor3f(1.50, 0.70, 0.0);
	glBegin(GL_TRIANGLES); //Begin triangle coordinates
						   
	glVertex3f(-0.5f, 0.5f, -3.0f);
	glVertex3f(-1.0f, 1.5f, -3.0f);
	glVertex3f(-1.5f, 0.5f, -3.0f);
	glEnd(); 
	glPopMatrix();
	*/
}

void SpaceshipModel_U1::DrawInnerBody() {
	glPushMatrix();
	glTranslatef(-2.0, 0, 0.90);
	glColor3f(0.50, 0.70, 0.0);
	gluCylinder(quadratico, 0.50, 0.50, 0.60, 100, 100);
	glPopMatrix();

	// right wings
	glPushMatrix();
	glTranslatef(-0.70, 0, 0.90);
	glScalef(1.00, 0.2, 0.50);
	glColor3f(0.50, 0.50, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	// left wings
	glPushMatrix();
	glTranslatef(-3.30, 0, 0.90);
	glScalef(1.00, 0.2, 0.50);
	glColor3f(0.50, 0.50, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	// Main Body
	// Back Part
	glPushMatrix();
	glTranslatef(-2.00, 0, 0.90);
	glScalef(1.75, 0.50, 2.0);
	glColor3f(0.75, 0.50, 0.50);
	glutSolidCone(0.50, 2.0, 100, 100);
	glPopMatrix();

	// Back Part 2
	glPushMatrix();
	glTranslatef(-2.00, 0, 0.90);
	glRotatef(90.0f, 0.0, 0.0, 1.0);
	glScalef(1.75, 0.50, 2.0);
	glColor3f(0.75, 0.50, 0.50);
	glutSolidCone(0.50, 2.0, 100, 100);
	glPopMatrix();

	// Front Part

	// Bottom Plate
	glPushMatrix();
	glTranslatef(-2.00, 0, 0.0);
	glScalef(1.50, 0.20, 2.0);
	glColor3f(0.75, 0.50, 0.50);
	glutSolidCube(1.0);
	glPopMatrix();

	// Mid Plate
	glPushMatrix();
	glTranslatef(-2.00, 0.50, 0.0);
	glScalef(0.50, 1.00, 2.0);
	glColor3f(0.75, 0.50, 0.50);
	glutSolidCube(1.0);
	glPopMatrix();
	
	// round plate
	glPushMatrix();
	glTranslatef(-2.00, 0.50, -0.10);
	glScalef(1.00, 1.00, 7.0);
	glColor3f(1.00, 1.00, 0.00);
	glutSolidTorus(0.20, 0.50, 100, 100);
	glPopMatrix();

	// Front Cone
	glPushMatrix();
	glTranslatef(-2.00, 0, 0.90);
	glRotatef(180.0f, 1.0, 0.0, 0.0);
	glScalef(1.75, 2.00, 2.0);
	glColor3f(0.75, 0.50, 0.50);
	glutSolidCone(0.50, 2.0, 100, 100);
	glPopMatrix();


}

void SpaceshipModel_U1::DrawBlockers() {
	// right blocker
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glScalef(0.75, 0.75, 0.20);
	glColor3f(1.00, 0.50, 1.00);
	glutSolidTorus(0.20, 0.30, 100, 100);
	glPopMatrix();

	// left blocker
	glPushMatrix();
	glTranslatef(-4.0, 0.0, 0.0);
	glScalef(0.75, 0.75, 0.20);
	glColor3f(1.00, 0.50, 1.00);
	glutSolidTorus(0.20, 0.30, 100, 100);
	glPopMatrix();
}

void SpaceshipModel_U1::DrawModel()
{
	// Collision Area
	//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	/*glPushMatrix();
	glTranslatef(0.0, 1.50, -0.10);
	glColor4f(1.0, 1.0, 1.0, 0.0);
	glutWireSphere(3.0, 100, 100);
	glPopMatrix();*/

	//glClear(GL_COLOR_BUFFER_BIT);

	// Spaceship
	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glPushMatrix();
	glTranslatef(-1.0, 1.50, 0.0);
	DrawLeftFireArm();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 1.50, 0.0);
	DrawRightFireArm();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 1.50, 0.0);
	DrawOuterBody();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0, 1.50, 0.0);
	DrawInnerBody();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0, 1.50, 0.0);
	DrawBlockers();
	glPopMatrix();
}

