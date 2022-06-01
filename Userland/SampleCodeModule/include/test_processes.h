#ifndef TEST_PROCESSES_H
#define TEST_PRORCESSES_H

#include <test_util.h>

enum State
{
  RUNNING,
  WAITING,
  KILLED
};

typedef struct P_rq
{
  int32_t pid;
  enum State state;
} p_rq;

int64_t test_processes(uint64_t argc, char *argv[]);

#endif