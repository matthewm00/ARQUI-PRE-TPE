#ifndef GAMES_H
#define GAMES_H

#include <stdint.h>
#include <libc.h>
#include <syscalls.h>
#include <RTCID.h>
#include <sudoku.h>

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16
#define WIDTH 1024
#define HEIGHT 768

void startGames();
void hangman(char c);
void printTime();
void stopWatch();
void updateSecondsStopwatch();

void changeCursorState(int state);
void setCursor(uint64_t x, uint64_t y);
#endif