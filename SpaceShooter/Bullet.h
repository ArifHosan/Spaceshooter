#pragma once
#ifndef BULLET_H
#define BULLET_H
#include "Structs.h"
#include "Asteroid.h"
#include "glut.h"
class Bullet
{
public:
	double speed = 0.2;
	Location location;
	Dimension dim;
	GLuint textureId;
	void move();
	Bullet();
	void render();
	bool hasCollide(Asteroid a);
	~Bullet();
};


#endif // !BULLET_H
