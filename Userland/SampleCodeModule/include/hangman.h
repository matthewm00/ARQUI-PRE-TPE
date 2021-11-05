#ifndef HANGMAN_H
#define HANGMAN_H

#include <games.h>

#define WORD_LENGTH 11

void startHangman();
int repeatedLetter(char c);
void hangman(char c);
void printPlayerWord();

#endif