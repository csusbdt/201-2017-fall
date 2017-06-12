#include <cassert>
#include "global.h"

using namespace std;

static double speed = 25; // pixels per second

void write_frame(double t) {
	clear_frame();
	draw_rect(0 + t * speed, 0 + t * speed, 10, 10, 0x00, 0xff, 0x00);
}

