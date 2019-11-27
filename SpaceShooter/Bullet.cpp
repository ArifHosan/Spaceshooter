#include "Bullet.h"

Bullet::Bullet()
{
}

void Bullet::render() {
	/*glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(location.x,location.y,location.z);
	glScaled(1,1,5);
	glutSolidSphere(0.2, 50, 50);
	glPopMatrix();*/
	glPushMatrix();
	glPushMatrix();
	//glRotatef(_angle, angle_axis_x, angle_axis_y, angle_axis_z);
	GLUquadric *quadratico = gluNewQuadric();
	// Head
	glTranslated(location.x, location.y, location.z);
	glPushMatrix();
	glTranslatef(0, 0, 1.10);
	glColor3f(0.0, 1.0, 0.0);
	gluCylinder(quadratico, 0.30, 0.50, 1.0, 10, 10);
	glPopMatrix();


	// Body
	glPushMatrix();
	glTranslatef(0, 0, 2.10);
	glColor3f(0.0, 1.0, 0.0);
	gluCylinder(quadratico, 0.50, 0.50, 3.0, 10, 10);
	glPopMatrix();

	// Back
	glPushMatrix();
	glTranslatef(0, 0, 5.10);
	glColor3f(1.0, 0.0, 0.0);
	glScalef(0.50, 0.50, 0.0);
	gluSphere(quadratico, 1.0, 10, 10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}

bool Bullet::hasCollide(Asteroid a) {
	return abs(this->location.x - a.location.x) <= a.radius && abs(this->location.z-a.location.z)<=a.radius;
}

void Bullet::move() {
	this->location.z -= speed;
}
Bullet::~Bullet()
{
}
