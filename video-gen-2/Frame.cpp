#include <cstring>
#include "Frame.h"

int Frame::w = W;
int Frame::h = H;
byte Frame::data[H][W][3];

void Frame::clear() {
	memset(data, 0, sizeof(data));
}

void Frame::write(FILE * file) {
	fwrite(data, 3, Frame::h * Frame::w, file);
}

