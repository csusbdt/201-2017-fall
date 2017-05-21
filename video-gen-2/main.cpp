/*! \mainpage Video Generation System
 *
 * This system uses the following coordinate system:
 * ~~~~
 *    (0, 0)               (w, 0)
 *      +--------------------+
 *      |                    |
 *      |                    |
 *      |                    |
 *      +--------------------+
 *    (0, h)               (w, h)
 * ~~~~
 *
 */

#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include "Frame.h"
#include "Rect.h"

using namespace std;

class Main {
public: 
        static int run(int argc, char * argv[]);
};

int Main::run(int argc, char * argv[]) {
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
		Frame::clear();
		Rect rect(0 + 10 * i, 0 + 15 * i, 20, 10);
		rect.paint(0x00, 0xff, 0x00);
		Frame::write(pipe);
	}

	fflush(pipe);
	pclose(pipe);

	cout << "Done." << endl;

	return 0;
}

int main(int argc, char * argv[]) { 
	return Main::run(argc, argv);
}

