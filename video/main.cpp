// https://github.com/csusbdt/genvideo/wiki/Problem-2

#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstdio>
#include <stdint.h>

typedef unsigned char byte;

using namespace std;

#define W 720
#define H 480

const double frames_per_second = 30;
const double duration_in_seconds = 2.4;

unsigned char frame[H][W][3];

void clear_frame() { memset(frame, 0, sizeof(frame)); }
void draw_rect(int x, int y, int w, int h, byte r, byte g, byte b);

void draw_frame(double t) {
	clear_frame();
	const double pps = 120; // pixels per second
	draw_rect(0 + t * pps, 0 + t * pps, 20, 10, 0x00, 0xff, 0x00);
}

// Constrain point to frame.
void clamp(int * x, int * y) {
	if (*x < 0) *x = 0; else if (*x > W) *x = W;
	if (*y < 0) *y = 0; else if (*y > H) *y = H;
}

void draw_rect(int x, int y, int w, int h, byte r, byte g, byte b) {
	int x0 = x;
	int x1 = x + w;
	int y0 = y;
	int y1 = y + h;
	clamp(&x0, &y0);
	clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
}

int main(int argc, char * argv[]) {
	FILE * result = freopen(0, "wb", stdout);
	if (result == 0) {
		perror("Error reopening stdout");
		exit(1);
	}

	int num_frames = duration_in_seconds * frames_per_second;

	for (int i = 0; i < num_frames; ++i) {
		double time_in_seconds = i / (double) frames_per_second;
		draw_frame(time_in_seconds);
		fwrite(frame, 3, W * H, stdout);
	}

	return 0;
}
