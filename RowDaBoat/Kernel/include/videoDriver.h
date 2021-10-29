#ifndef _VIDEO_DRIVER_H_
#define _VIDEO_DRIVER_H_

#include <stdint.h>
#include <font.h>

#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define RED 0x0000FF
#define BLUE 0xFF0000
#define GREEN 0x00FF00
#define DARK_RED 0x001BB5

void initVideoDriver(uint64_t backgroundColor, uint64_t fontColor);
void separateMainScreen();
void changeScreen(int index);
void drawLetter(int key, int x, int y, int color, int background_color);
void drawPixel(int x, int y, int color);
char *getPosition(uint32_t x, uint32_t y);
void drawRectangle(int x, int y, int color, int width, int height);
int getScreenWidth();
int getScreenHeight();
void newLine(uint32_t width, uint32_t height, uint64_t fontColor, uint64_t backgroundColor);
int getColorOfPixel(int x, int y);
void deleteLast();
void clearLineOnScreen();
void print(char *buff, uint64_t length, uint64_t fontColor, uint64_t backgroundColor);

#endif