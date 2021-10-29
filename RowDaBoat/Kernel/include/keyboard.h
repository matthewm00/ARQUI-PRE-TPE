#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define KEYS 59
#define ESC 0x01
#define R_HEXA_CODE 0x13
#define L_SHIFT 0x2A
#define R_SHIFT 0x36
#define CAPS_LCK 0x3A
#define CTRL 0x1D
#define SPACE_BAR 0x39
#define R_SHIFT_RELEASED 0xB6
#define L_SHIFT_RELEASED 0xAA
#define ESC_RELEASED 0x81
#define IS_LETTER(c) (c >= 'a' && c <= 'z' ? 1 : 0)

void keyboardHandler();
void clearBuffer();
void checkBuffer();
char *getKeyboardBuffer();

extern unsigned int hasKeyboardKey();
extern unsigned int readKeyboard();

#endif