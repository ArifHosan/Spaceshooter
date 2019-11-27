#include "Asteroid.h"

void Asteroid::render() {
	//gluLookAt(ex, ey, ez, cx, cy, cz, 0, 1, 0);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glColor3f(1, 0, 1);
	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	GLUquadric *quad = gluNewQuadric();
	gluQuadricNormals(quad, GL_SMOOTH);
	gluQuadricTexture(quad, 1);
	
	glTranslatef(location.x, location.y, location.z);
	glRotatef(angle, 1, 1, 0);
	gluSphere(quad, radius, 20, 20);

	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_TEXTURE_GEN_S);
	//glDisable (GL_TEXTURE_GEN_T);
	glPopMatrix();
}

void Asteroid::move() {
	angle += 3;
	if (angle >= 360) angle -= 360;
	location.z += speed;
	//std::cout << location.z << std::endl;
}

bool Asteroid::shouldRemove() {
	return location.z >= -15;
}

bool Asteroid::hasCollide(double x) {
	return abs(this->location.x - x)<=this->radius+2 && this->location.z>=-24;
}

Asteroid::Asteroid(){
}


Asteroid::~Asteroid(){
}
