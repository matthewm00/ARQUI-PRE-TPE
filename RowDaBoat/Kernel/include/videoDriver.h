#ifndef _VIDEO_DRIVER_H_
#define _VIDEO_DRIVER_H_

#include <stdint.h>
#include <font.h>
#include <time.h>
typedef enum
{
    BLACK = 0x000000,
    WHITE = 0xFFFFFF,
    RED = 0xFF0001,
    BLUE = 0x0000FF,
    GREEN = 0x00FF00
} t_color;

// PRE TP MODO TEXTO
//  void printChar(char character, int colour);
//  void printString(const char * string);

void putPixel(int x, int y, int colour);
void printChar(char c, t_color fontColour, t_color bgColour, int stop);
void initializeVideo();
void clearScreen();
void newLine();
void deleteChar();
void clearLine();
void scrollDown();
void divideScreen(t_color color);
void changeCurrentScreen(int screen_number);
void cursor();
void stopCursor();
#endif