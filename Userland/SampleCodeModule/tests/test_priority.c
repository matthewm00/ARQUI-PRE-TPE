
#include <test_priority.h>

void test_priority()
{
  int64_t pids[TOTAL_PROCESSES];
  uint64_t i;

  for (i = 0; i < TOTAL_PROCESSES; i++)
  {
    char *argv[] = {"Idle Process"};
    pids[i] = newProcess(&idleProcess, 1, argv, BACKGROUND, NULL);
  }

  bussy_wait(WAIT);
  printf("\nCHANGING PRIORITIES...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
  {
    switch (i % 3)
    {
    case 0:
      setPriority(pids[i], 1); // lowest priority
      break;
    case 1:
      setPriority(pids[i], 25); // medium priority
      break;
    case 2:
      setPriority(pids[i], 50); // highest priority
      break;
    }
  }

  bussy_wait(WAIT);
  printf("\nBLOCKING...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    blockProcess(pids[i]);

  printf("CHANGING PRIORITIES WHILE BLOCKED...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    setPriority(pids[i], 25);

  printf("UNBLOCKING...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    unblockProcess(pids[i]);

  bussy_wait(WAIT);
  printf("\nKILLING...\n");

  for (i = 0; i < TOTAL_PROCESSES; i++)
    killProcess(pids[i]);
}
