#pragma once
#ifndef STRUCTS_H
#define STRUCTS_H

struct Location {
	double x, y, z;
	Location(double xx, double yy, double zz) {
		x = xx;
		y = yy;
		z = zz;
	}
	Location() {
		x = 0;
		y = 0;
		z = 0;
	}
};

struct Dimension {
	double width, height;
	Dimension(double w, double h) {
		width = w;
		height = h;
	}
	Dimension() {
		width = 0;
		height = 0;
	}
};

struct Color {
	double r, g, b;
	Color() {
		r = 0;
		g = 0;
		b = 0;
	}
	Color(double a, double d, double c) {
		r = a;
		g = d;
		b = c;
	}
};


#endif


