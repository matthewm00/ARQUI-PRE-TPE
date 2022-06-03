#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H

#include <stdint.h>

void keyboardHandler(uint64_t rsp);
void putCharInBuffer(char c);
uint64_t *getRegisters();
uint64_t dumpBuffer(char *dest, int size);
char removeCharFromBuffer();
void updateRegisters(uint64_t *rsp);
uint8_t _getKey(void);
uint8_t _hasKey(void);
char getChar(void);  // MODO HLT
void clearBuffer();
void cleanKeyboardBuffer();
int bufferSize();
int initializeKeyboard();

#endif