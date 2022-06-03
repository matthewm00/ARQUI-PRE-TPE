// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <libc.h>
#include <semaphoreTest.h>
#include <stdint.h>
#include <userSyscalls.h>

#define TOTAL_PAIR_PROCESSES 2
#define SEM_ID 55

int64_t global;
int64_t iterations = 0;

static void printUserPrompt() {
  iterations++;
  if (iterations == 2 * TOTAL_PAIR_PROCESSES) {
    iterations = 0;
    printUser();
  }
}

void slowInc(int64_t *p, int64_t inc) {
  int64_t aux = *p;
  aux += inc;
  yield();
  *p = aux;
}

void inc(int argc, char *argv[]) {
  uint64_t sem = strToInt(argv[1], 0);
  uint64_t value = strToInt(argv[2], 0);
  uint64_t N = strToInt(argv[3], 0);
  uint64_t i;

  if (sem && semOpen(SEM_ID, 1) == -1) {
    printf("ERROR OPENING SEM\n");
    return;
  }

  for (i = 0; i < N; i++) {
    if (sem && semWait(SEM_ID) != 0) {
      printf("ERROR WAITING SEM\n");
    }
    slowInc(&global, value);
    if (sem && semPost(SEM_ID) != 0) {
      printf("ERROR POSTING SEM\n");
    }
  }

  if (sem && semClose(SEM_ID) != 0) {
    printf("ERROR CLOSING SEM\n");
  }

  printf("\nFinal value: %d\n", global);
  printUserPrompt();
}

void testSync() {
  uint64_t i;

  global = 0;

  printf("CREATING PROCESSES...(WITH SEM)\n");

  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++) {
    char *argv1[] = {"inc process with sem", "1", "1", "10000"};
    newProcess(&inc, 4, argv1, BACKGROUND, NULL);
    char *argv2[] = {"inc process with sem", "1", "-1", "10000"};
    newProcess(&inc, 4, argv2, BACKGROUND, NULL);
  }
}

void testNoSync() {
  uint64_t i;

  global = 0;

  printf("CREATING PROCESSES...(WITHOUT SEM)\n");

  for (i = 0; i < TOTAL_PAIR_PROCESSES; i++) {
    char *argv1[] = {"inc process without sem", "0", "1", "10000"};
    newProcess(&inc, 4, argv1, BACKGROUND, NULL);
    char *argv2[] = {"inc process without sem", "0", "-1", "10000"};
    newProcess(&inc, 4, argv2, BACKGROUND, NULL);
  }
}
