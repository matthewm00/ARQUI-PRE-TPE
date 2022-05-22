// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <pipes.h>
#include <prints.h>
#include <semaphores.h>

#define MAX_PIPES 8

t_pipe pipes[MAX_PIPES];

int initialSemId = 1000;

static int createPipe(int pipeId);
static int pipeWriter(char c, int idx);
static int getNewIndex();
static int getIndex(int pipeId);
