#include "Rect.h"
#include "Frame.h"

void Rect::paint(byte r, byte g, byte b) {
	// Convert to integer and constrain to frame.
	int x0 = x;
	int y0 = y;
	int x1 = x + w;
	int y1 = y + h;
	if (x0 < 0) x0 = 0;
	if (y0 < 0) y0 = 0;
	if (x1 > W) x1 = Frame::w;
	if (y1 > H) y1 = Frame::h;
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			Frame::data[y][x][0] = r;
			Frame::data[y][x][1] = g;
			Frame::data[y][x][2] = b;
		}
	}
}

