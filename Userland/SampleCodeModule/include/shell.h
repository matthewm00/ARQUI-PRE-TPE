#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 100
#define MAX_ARGUMENTS 5
#define FOREGROUNG 1
#define BACKGROUND 0

void initialize();
void shellExecute();

void _setStack();
#endif