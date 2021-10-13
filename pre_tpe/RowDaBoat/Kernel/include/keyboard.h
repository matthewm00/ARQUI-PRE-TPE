#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

int getScanCode();
int isLetter(char c);
void pressedKey(char c);
char getKey();

#endif