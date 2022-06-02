// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <lib.h>
#include <memoryManager.h>
#include <processManager.h>
#include <semaphores.h>

t_semaphore *semaphores;

static t_semaphore *getSemaphore(uint32_t id);
static t_semaphore *createSemaphore(uint32_t id, uint64_t initialValue);
static void addSemaphoreToList(t_semaphore *newSem);
static void unblockSemProcess(t_semaphore *sem);
static void removeSemaphore(t_semaphore *sem);
static void blockedProcessesDump(int *blockedProcesses,
                                 uint16_t blockedProcessesAmount);

int semOpen(uint32_t id, uint64_t initialValue) {
  t_semaphore *semaphore = getSemaphore(id);

  if (semaphore == NULL) {
    semaphore = createSemaphore(id, initialValue);
    if (semaphore == NULL) {
      return -1;
    }
  }

  if (semaphore->listeningProcesses >= MAX_BLOCKED_PROCESSES) {
    return -1;
  }

  semaphore->listeningProcesses++;
  return id;
}

int semWait(uint32_t id) {
  t_semaphore *sem;
  if ((sem = getSemaphore(id)) == NULL) {
    return -1;
  }

  acquire(&(sem->lock));
  if (sem->value > 0) {
    sem->value--;
    release(&(sem->lock));
  } else {
    int currentPID = getProcessPID();
    sem->blockedProcesses[sem->blockedProcessesAmount++] = currentPID;
    release(&(sem->lock));
    blockProcess(currentPID);
  }
  return 0;
}

int semPost(uint32_t id) {
  t_semaphore *sem;
  if ((sem = getSemaphore(id)) == NULL) {
    return -1;
  }

  acquire(&(sem->lock));
  if (sem->blockedProcessesAmount > 0) {
    unblockSemProcess(sem);
  } else {
    sem->value++;
  }

  release(&(sem->lock));
  return 0;
}

int semClose(uint32_t id) {
  t_semaphore *sem;
  if ((sem = getSemaphore(id)) == NULL) {
    return -1;
  }

  if (sem->listeningProcesses > 0) {
    sem->listeningProcesses--;
  }

  if (sem->listeningProcesses == 0) {
    removeSemaphore(sem);
  }

  return 0;
}

void semStatus() {
  printf("\nActive Semaphore Status\n\n");
  t_semaphore *sem = semaphores;
  while (sem) {
    printf("Semaphore ID: %d\n", sem->id);
    printf("     Value: %d\n", sem->value);
    printf("     Attached processes amount: %d\n", sem->listeningProcesses);
    printf("     Blocked processes amount: %d\n", sem->blockedProcessesAmount);
    printf("     Blocked processes:\n");
    blockedProcessesDump(sem->blockedProcesses, sem->blockedProcessesAmount);
    sem = sem->next;
  }
}

static void blockedProcessesDump(int *blockedProcesses,
                                 uint16_t blockedProcessesAmount) {
  for (int i = 0; i < blockedProcessesAmount; i++) {
    printf("         PID: %d\n", blockedProcesses[i]);
  }
  printf("\n");
}

static void removeSemaphore(t_semaphore *sem) {
  t_semaphore *semListAux = semaphores;
  if (sem == semListAux) {
    semaphores = semListAux->next;
  } else {
    while (semListAux->next != sem) {
      semListAux = semListAux->next;
    }
    semListAux->next = sem->next;
  }
  free(sem);
}

static t_semaphore *createSemaphore(uint32_t id, uint64_t initialValue) {
  t_semaphore *newSem = malloc(sizeof(t_semaphore));
  if (newSem != NULL) {
    newSem->id = id;
    newSem->value = initialValue;
    newSem->blockedProcessesAmount = 0;
    newSem->listeningProcesses = 0;
    newSem->lock = 0;
    newSem->next = NULL;
    addSemaphoreToList(newSem);
  }
  return newSem;
}

static void addSemaphoreToList(t_semaphore *newSem) {
  t_semaphore *tailSem = semaphores;
  if (tailSem == NULL) {
    semaphores = newSem;
  } else {
    while (tailSem->next != NULL) {
      tailSem = tailSem->next;
    }
    tailSem->next = newSem;
  }
}

static t_semaphore *getSemaphore(uint32_t id) {
  t_semaphore *result = semaphores;
  while (result) {
    if (result->id == id) {
      return result;
    }
    result = result->next;
  }
  return NULL;
}

static void unblockSemProcess(t_semaphore *sem) {
  int readyPID = sem->blockedProcesses[0];
  for (int i = 0; i < sem->blockedProcessesAmount - 1; i++) {
    sem->blockedProcesses[i] = sem->blockedProcesses[i + 1];
  }
  sem->blockedProcessesAmount--;
  readyProcess(readyPID);
}
