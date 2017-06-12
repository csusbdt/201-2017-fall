#include "global.h"
#include <algorithm>

using namespace std;

unsigned char frame[H][W][3] = { 0 };

void clear_frame() {
	memset(frame, 1, sizeof(frame));
}

int frame_clamp_x(int x) {
	if (x < 0) return 0;
	else if (x > W) return W;
	else return x;
}

int frame_clamp_y(int y) {
	if (y < 0) return 0;
	else if (y > H) return H;
	else return y;
}

void draw_rect(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b) {
	// Constrain rectangle to frame.
	int x0 = frame_clamp_x(x);
	int x1 = frame_clamp_x(x + w);
	int y0 = frame_clamp_y(y);
	int y1 = frame_clamp_y(y + h);

	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
}

