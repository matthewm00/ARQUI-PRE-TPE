#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H

#include <stdint.h>

void keyboardHandler();
void putCharInBuffer(char c);
uint64_t dumpBuffer(char *dest, int size);
char removeCharFromBuffer();
uint8_t _getKey(void);
uint8_t _hasKey(void);
char getCharFromBuffer(); // MODO HLT
void clearBuffer();
void cleanKeyboardBuffer();
int bufferSize();

#endif