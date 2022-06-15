#ifndef LIBC_H
#define LIBC_H

#include <colors.h>
#include <stdint.h>

#define C1_WIDTH 15
#define C2_WIDTH 45
#define TABLE_WIDHT (C1_WIDTH + C2_WIDTH + 3)
#define EOF 96
#define COL1_WIDTH 13
#define COL2_WIDTH 38
void setBGC(t_color colour);
void setFTC(t_color colour);
int scanf(char *str, ...);
void printf(char *str, ...);
void printc(t_color color, char *str, ...);
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
void newLine();
int readText();
int strToHex(const char *str);
void sendUserData(char *userName, int len);
void setFirstChange(int number);
void *memset(void *destination, int32_t c, uint64_t length);
int isVowel(char c);
void sleep(int seconds);
void printRow(char *str1, char *str2, int firstRow);
void printCol(char *str, int width);
#endif