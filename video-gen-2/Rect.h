#pragma once

typedef unsigned char byte;

class Rect {
public:
	Rect(double x, double y, double w, double h) 
	: x(x), y(y), w(w), h(h) {}

	void paint(byte r, byte g, byte b);

	double x;	
	double y;	
	double w;	
	double h;	
};

