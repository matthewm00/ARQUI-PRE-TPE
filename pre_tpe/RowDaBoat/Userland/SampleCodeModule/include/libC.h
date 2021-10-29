#ifndef _LIB_C_H_
#define _LIB_C_H_

#include <stdint.h>
#include <stdarg.h>
#include <utils.h>

#define SCREEN_WIDTH 1024
#define BGR 3
typedef enum
{
    BLACK = 0x000000,
    WHITE = 0xFFFFFF,
    RED = 0x0000FF,
    BLUE = 0xFF0000,
    GREEN = 0x00FF00,
    DARK_RED = 0x001BB5
} t_colour;

typedef enum
{
    READ = 0,
    RTC_TIME = 1,
    WRITE = 3,
    GETCHAR = 4,
    CLEAR = 5,
    RUN = 7,
    EXIT = 8,
    INFOREG = 9
} syscallID;

extern void syscall(uint64_t syscallId, ...);

void putChar(char c);
char getChar();

void printf(const char *format, ...);
int scanf(const char *format, ...);

#endif