#pragma once

#include<iostream>
#include "glut.h"
#include "SpaceshipsModel.h"

using namespace std;

class SpaceshipModel_U2 : SpaceshipModel {
public:
	void DrawModel();

	SpaceshipModel_U2(unsigned short int ID, string NAME, string MOTHERLAND) : SpaceshipModel(ID, NAME, MOTHERLAND) {

	}

	//glTexCoord2f(0.0, 0.0);
};


void DrawLeftWing() {

	glPushMatrix();
	glTranslatef(-1, 0, 0);
	glColor3f(0.0, 0.0, 1.0);
	glScalef(3.0, 1.0, 3.0);
	glutSolidCube(1.0);
	glPopMatrix();

	

}

void DrawBody() {

	
}


void SpaceshipModel_U2::DrawModel()
{
	DrawBody();
	DrawLeftWing();
}