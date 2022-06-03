#ifndef _PHYLO_H
#define _PHYLO_H

#include <colors.h>

#define INITIAL_PHILOS 5
#define MAX_PHILOS 10

#define FILO_SEM_ID 2000
#define MUTEX_SEM_ID 3000
#define THINK_EAT_WAIT_SECONDS 1
#define PHYLO_HEADER_WIDTH 41
#define PHYLO_HEADER_HEIGHT 8
#define FRONTEND_WAIT_SECONDS 2

<<<<<<< HEAD
void philoProblem(int argc, char **argv);
=======
void phyloProblem(int argc, char **argv);

void thinkOrEat();
void phyloMain(int argc, char **argv);
void takeForks(int i);
void putForks(int i);
void test(int i);
int addPhylo();
int removePhylo();
void printTable(int argc, char **argv);
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a

#endif