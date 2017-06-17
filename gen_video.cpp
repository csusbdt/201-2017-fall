/*
This program generates a playable video file of simple animations 
using the mpeg4 encoding.  It does this by writing raw video frames 
into a running instance of ffmpeg. 
*/

#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>

typedef unsigned char byte;

using namespace std;

#define W 720
#define H 480

const double frames_per_second = 30;
const int duration_in_seconds = 3;

unsigned char frame[H][W][3];

void clear_frame() { memset(frame, 1, sizeof(frame)); }
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
	const char * cmd = 
		"ffmpeg           "
		"-y               "
		"-hide_banner     "
		"-f rawvideo      " // input to be raw video data
		"-pix_fmt rgb24   "
		"-s:v 720x480     "
		"-r 60            " // frames per second
		"-i -             " // read data from the standard input stream
		"-pix_fmt yuv420p " // to render with Quicktime
		"-vcodec mpeg4    "
		"-an              " // no audio
		"-q:v 5           " // quality level; 1 <= q <= 32
		"output.mp4       ";

	FILE * pipe = popen(cmd, "w");

	int num_frames = duration_in_seconds * frames_per_second;

	for (int i = 0; i < num_frames; ++i) {
		double time_in_seconds = i / frames_per_second;
		draw_frame(time_in_seconds);
		fwrite(frame, 3, W * H, pipe);
	}

	fflush(pipe);
	pclose(pipe);

	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;

	return 0;
}
