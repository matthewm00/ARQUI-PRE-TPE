#ifndef _VIDEO_DRIVER_H_
#define _VIDEO_DRIVER_H_

#include <stdint.h>
#include <font.h>

void drawLetter(int key, int x, int y, int color, int background_color);
void drawPixel(int x, int y, int color);
char *getPosition(int x, int y);
void drawRectangle(int x, int y, int color, int width, int height);
int getScreenWidth();
int getScreenHeight();
#endif