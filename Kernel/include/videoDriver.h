#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H
#include <colors.h>
#include <time.h>
#include <stdint.h>

// PRE TP MODO TEXTO
//  void printChar(char character, int colour);
//  void printString(const char * string);

#define WIDTH 1024
#define HEIGHT 768
#define PIXEL_SIZE 3 // bytes por pixel

void putPixel(int x, int y, int colour);
void printChar(char c, t_color fontColour, t_color bgColour, int stop);
void initializeVideo();
void clearScreen();
void newLine();
void deleteChar();
void clearLine();
void scrollDown();
void divideScreen(t_color color);
// void changeCurrentScreen();
void cursor();
void stopCursor();
void setUsernameLen(int len);
void setCursor(uint64_t x, uint64_t y);
void changeCursorState(int state);
int isCursorOn();
#endif