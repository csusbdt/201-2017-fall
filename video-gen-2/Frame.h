#pragma once

#include <stdio.h>

#define W 720
#define H 480

typedef unsigned char byte;

class Frame {
public:
	Frame() { throw "static class"; }
	static void clear();
	static void write(FILE * file);

	static int w;
	static int h;
	static byte data[H][W][3];
};

