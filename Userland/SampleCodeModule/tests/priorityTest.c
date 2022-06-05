// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <priorityTest.h>
#include <stdint.h>
#include <userSyscalls.h>

#define TOTAL_PROCESSES 3

void testPriority()
{
  uint64_t pids[TOTAL_PROCESSES];
  uint64_t i;

  for (i = 0; i < TOTAL_PROCESSES; i++)
  {
    char *argv[] = {"Idle Process"};
    pids[i] = createProcess(&idleProcess, 1, argv, BACKGROUND, NULL);
  }

  busyWait(TOTAL_PROCESSES * MAJOR_WAIT);

  printf("\nCHANGING PRIORITIES...\n\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
  {
    switch (i % 3)
    {
    case 0:
      setPriority(pids[i], 1);
      break;
    case 1:
      setPriority(pids[i], 25);
      break;
    case 2:
      setPriority(pids[i], 50);
      break;
    }
  }

  busyWait(TOTAL_PROCESSES * MAJOR_WAIT);

  printf("\n\nBLOCKING...\n\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
  {
    blockProcess(pids[i]);
  }

  printf("\nCHANGING PRIORITIES WHILE BLOCKED...\n\n");
  for (i = 0; i < TOTAL_PROCESSES; i++)
  {
    setPriority(pids[i], 25);
  }

  printf("\nUNBLOCKING...\n\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
  {
    unblockProcess(pids[i]);
  }

  busyWait(TOTAL_PROCESSES * MAJOR_WAIT);
  printf("\nKILLING...\n\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
  {
    killProcess(pids[i]);
  }
}
