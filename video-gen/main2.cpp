/*
This program runs ffmpeg to convert raw video frames into an MPEG 4 video.
It does this by writing frame data directly into the standard input stream of ffmpeg.

Pieces of code taken from: 
https://batchloaf.wordpress.com/2017/02/12/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg-part-2-video/
*/

#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>

using namespace std;

const int W = 720;
const int H = 480;

unsigned char frame[H][W][3] = { 0 };

void paintRect(	
	int x0, 
	int y0, 
	int x1, 
	int y1,
	unsigned char r, 
	unsigned char g, 
	unsigned char b
){
	// Constrain rectangle to frame.
	x0 = max(x0, 0);
	x0 = min(x0, W);
	y0 = max(y0, 0);
	y0 = min(y0, H);
	x1 = max(x1, 0);
	x1 = min(x1, W);
	y1 = max(y1, 0);
	y1 = min(y1, H);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
}

int main(int argc, char * argv[]) {
	if (argc != 2) {
		cout << "arguments: <duration in frames>" << endl; 
		return 1;
	}
	int duration = stoi(argv[1]);

	stringstream cmd;
	cmd << "ffmpeg "           ;
        cmd << "-y "               ;
        cmd << "-hide_banner "     ;
        cmd << "-f rawvideo "      ;
        cmd << "-pix_fmt rgb24 "   ;
        cmd << "-s:v 720x480 "     ;
        cmd << "-r 60 "            ;
        cmd << "-i - "             ;
        cmd << "-pix_fmt yuv420p " ;  // to render with Quicktime
        cmd << "-vcodec mpeg4 "    ;
        cmd << "-an "              ;  // no audio
        cmd << "-q:v 5 "           ;  // quality level; 1 <= q <= 32
        cmd << "output.mp4"        ;

	FILE * pipe = popen(cmd.str().c_str(), "w");

	for (int i = 0; i < duration; ++i) {
		memset(frame, 0, sizeof(frame));
		paintRect(0 + 10 * i, 0 + 15 * i, 20 + 10 * i, 10 + 15 * i, 0x00, 0xff, 0x00);
		fwrite(frame, 3, H*W, pipe);
	}

	fflush(pipe);
	pclose(pipe);

	cout << "Done." << endl;

	return 0;
}

