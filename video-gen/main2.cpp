/*
Pieces of code taken from: 
https://batchloaf.wordpress.com/2017/02/12/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg-part-2-video/
*/

#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>

using namespace std;

const int W = 720;
const int H = 480;

unsigned char frame[H][W][3] = { 0 };

void resetFrame() {
	for (int y = 0; y < H; ++y) {
		for (int x = 0; x < W; ++x) {
			frame[y][x][0] = 0;
			frame[y][x][1] = 0;
			frame[y][x][2] = 0;
		}
	}
}

void paintRect(	
	int x0, 
	int y0, 
	int x1, 
	int y1,
	unsigned char r, 
	unsigned char g, 
	unsigned char b
){
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
		cout << "arguments: <duration>" << endl; 
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
		paintRect(0 + 10 * i, 0 + 15 * i, 20 + 10 * i, 10 + 15 * i, 0x00, 0xff, 0x00);
		fwrite(frame, 3, H*W, pipe);
		resetFrame();
	}

	fflush(pipe);
	pclose(pipe);

	cout << "Done." << endl;
	return 0;
}

