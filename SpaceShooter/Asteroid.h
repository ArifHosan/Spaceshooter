#pragma once
#include<iostream>
#include "glut.h"
#include<string>
#include "button.h"
using namespace std;
class Asteroid
{
public:
	double angle = 0;
	double radius;
	double speed=0.5;
	string name;
	string text;
	Location location;
	Color col;
	GLuint textureId;
	void render();
	void move();
	bool shouldRemove();
	bool hasCollide(double);
	Asteroid();
	~Asteroid();
};

