#ifndef LIBC_H
#define LIBC_H

#include <colors.h>
#include <stdint.h>

#define EOF 96
#define COL1_WIDTH 13
#define COL2_WIDTH 38
void setBGC(t_color colour);
void setFTC(t_color colour);
int scanf(char *str, ...);
void printf(char *str, ...);
void putChar(char c);
char getChar();
int strlen(const char *s);
int strcmp(char string1[], char string2[]);
int strToInt(char *str, int *size);
char *intToStr(int value, char *buffer, int base);
void newLine();
char *reverse(char *buffer, int i, int j);
int abs(int num);
void swap(char *x, char *y);
char *strcpy(char *destination, const char *source);
int readText();
int strToHex(const char *str);
void printIntDec(uint64_t num);
uint64_t uintToBase(uint64_t value, char *buffer, uint32_t base);
void *memset(void *destination, int32_t c, uint64_t length);
void printRow(char *str1, char *str2, int firstRow);
void printCol(char *str, int width);
void sleep(int seconds);
int isVowel(char c);
#endif