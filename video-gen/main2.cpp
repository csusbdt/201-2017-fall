/*
Pieces of code taken from: 
https://batchloaf.wordpress.com/2017/02/12/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg-part-2-video/
*/

#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>

using namespace std;

const int w = 720;
const int h = 480;

unsigned char frame[w][h][3] = { 0 };

void resetFrame() {
	for (int i = 0; i < w; ++i) {
		for (int j = 0; j < h; ++j) {
			frame[i][j][0] = 0;
			frame[i][j][1] = 0;
			frame[i][j][2] = 0;
		}
	}
}

void paintRect(	
	int i0, 
	int j0, 
	int i1, 
	int j1,
	unsigned char r, 
	unsigned char g, 
	unsigned char b
){
	for (int i = i0; i < i1; ++i) {
		for (int j = j0; j < j1; ++j) {
			frame[i][j][0] = r;
			frame[i][j][1] = g;
			frame[i][j][2] = b;
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
        cmd << "-f rawvideo "      ;
        cmd << "-vcodec rawvideo " ;
        cmd << "-pix_fmt rgb24 "   ;
        cmd << "-s 720x480 "       ;
        cmd << "-r 25 "            ;
        cmd << "-i - "             ;
        cmd << "-f mp4 "           ;
        //cmd << "-q:v 5 "           ;
        cmd << "-an "              ;
        //cmd << "-vcodec mpeg4 "    ;
        cmd << "-vcodec h264 "    ;
        cmd << "output.mp4"        ;

	FILE * pipe = popen(cmd.str().c_str(), "w");

	for (int i = 0; i < duration; ++i) {
		paintRect(20, 10, 50, 48, 0xff, 0x00, 0x00);
		fwrite(frame, 1, h*w*3, pipe);
		resetFrame();
	}

	fflush(pipe);
	pclose(pipe);

	cout << "Done." << endl;
	return 0;
}

