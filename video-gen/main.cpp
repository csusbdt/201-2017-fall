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
#include "global.h"

using namespace std;

static const double frames_per_second = 30;
static const int duration_in_seconds = 15;

int main(int argc, char * argv[]) {
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

	int num_frames = duration_in_seconds * frames_per_second;

	for (int i = 0; i < num_frames; ++i) {
		double time_in_seconds = i / frames_per_second;
		write_frame(time_in_seconds);
		fwrite(frame, 3, W * H, pipe);
	}

	fflush(pipe);
	pclose(pipe);

	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;

	return 0;
}

