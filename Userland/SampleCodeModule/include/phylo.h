#ifndef _PHYLO_H
#define _PHYLO_H

#define INITIAL_PHYLOS 5
#define MAX_PHYLOS 10

#define PHYLO_SEM_ID 2000
#define MUTEX_SEM_ID 3000
#define THINK_EAT_WAIT_SECONDS 1
#define PHYLO_HEADER_WIDTH 41
#define PHYLO_HEADER_HEIGHT 8
#define FRONTEND_WAIT_SECONDS 2

void phyloProblem(int argc, char **argv);


void thinkOrEat();
void phyloMain(int argc, char **argv);
void takeForks(int i);
void putForks(int i);
void test(int i);
int addPhylo();
int removePhilo();
void printTable(int argc, char **argv);

#endif