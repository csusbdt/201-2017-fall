#pragma once

#define W 720
#define H 480

// main2.cpp
extern void write_frame(double t);

// frame.cpp
extern unsigned char frame[H][W][3];
extern void clear_frame();
extern void draw_rect(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b);

