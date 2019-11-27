#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include<cstdlib>
#include "glut.h"
#include<iostream>
#include<string>
#include "Structs.h"

class Button
{
public:
	std::string name;
	std::string text;
	Location location;
	Dimension dim;
	Color col;
	GLuint textureId;
	void render();
	bool isClicked(int x, int y);
	Button();
	~Button();
};

#endif // !BUTTON_H


