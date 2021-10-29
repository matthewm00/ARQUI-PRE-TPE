#ifndef UTILS_H
#define UTILS_H

#define IS_LETTER(c) (c >= 'a' && c <= 'z' ? 1 : 0)
#define IS_OPERAND(c) (c == '+' || c == '-' || c == '*' || c == '%' || c == '(' || c == ')' ? 1 : 0)
#define IS_DIGIT(c) (c >= '0' && c <= '9' ? 1 : 0)
#define ABS(c) (c >= 0 ? c : c * -1)
#define MAX(a, b) (a > b ? a : b)

#include <stdint.h>
#include <stdarg.h>

int strToInt(char *charValue);
int numToStr(char *str, int num);
int strcmp(char *s1, char *s2);
uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base);
int numToBase(uint64_t value, uint_least32_t base, uint64_t *buffer);
char *strcpy(char *destination, const char *source);

void parseHexa(char *buff, int dim);
void printBase(uint64_t value, uint_least32_t base);
int strToHex(const char *str);
char *intToStr(int value, char *buffer, int base);
int strlen(char *str);
void *memcpy(void *destination, const void *source, uint64_t length);
int isNum(char *str);
char *reverse(char *buffer, int i, int j);
void swap(char *x, char *y);
#endif