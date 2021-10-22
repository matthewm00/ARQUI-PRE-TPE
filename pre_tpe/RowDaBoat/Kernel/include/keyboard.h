#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define KEYS 59
#define ESC 0x01
#define DELETE_KEY 0x0E
#define DELETE_KEY_RELEASED 0xFFFFFFFFFFFFFF8E
#define R_HEXA_CODE 0x13
#define L_SHIFT 0x2A
#define R_SHIFT 0x36
#define CAPS_LCK 0x3A
#define CTRL 0x1D
#define SPACE_BAR 0x39
#define R_SHIFT_RELEASED 0xFFFFFFFFFFFFFFB6
#define L_SHIFT_RELEASED 0xFFFFFFFFFFFFFFAA
#define ESC_RELEASED 0x81

void keyboardHandler();

extern unsigned char hasKeyboardKey();
extern unsigned char readKeyboard();

#endif