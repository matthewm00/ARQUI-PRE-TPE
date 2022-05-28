// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <userSyscalls.h>

uint64_t syscall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
  return _syscall(rdi, rsi, rdx, rcx, r8, 0);
}

int newProcess(void (*entryPoint)(int, char **), int argc, char **argv, int foreground, int *fd)
{
  return _syscall(SYS_NEW_PROCESS_ID, (uint64_t)entryPoint, argc,
                  (uint64_t)argv, (uint64_t)foreground, (uint64_t)fd);
}

int killProcess(uint64_t pid)
{
  return syscall(SYS_KILL_PROCESS_ID, pid, 0, 0, 0);
}

int getProcessPID() { return syscall(SYS_PROCESS_PID_ID, 0, 0, 0, 0); }

void processStatus() { (void)syscall(SYS_PROCESS_STATUS_ID, 0, 0, 0, 0); }

int blockProcess(uint64_t pid)
{
  return syscall(SYS_BLOCK_PROCESS_ID, pid, 0, 0, 0);
}

int unblockProcess(uint64_t pid)
{
  return syscall(SYS_UNBLOCK_PROCESS_ID, pid, 0, 0, 0);
}

int setState(uint64_t pid, t_state newState)
{
  return syscall(SYS_CHANGE_PROCESS_STATE_ID, pid, (uint64_t)newState, 0, 0);
}

void yield() { (void)syscall(SYS_YIELD_ID, 0, 0, 0, 0); }

void setPriority(uint64_t pid, int newPriority)
{
  (void)syscall(SYS_SET_PRIORITY_ID, pid, newPriority, 0, 0);
}

void *malloc(uint64_t size)
{
  return (void *)syscall(SYS_MALLOC_ID, size, 0, 0, 0);
}

void free(void *address)
{
  (void)syscall(SYS_FREE_ID, (uint64_t)address, 0, 0, 0);
}

int semOpen(uint32_t id, uint64_t initialValue)
{
  return syscall(SYS_SEM_OPEN_ID, (uint64_t)id, initialValue, 0, 0);
}

int semWait(uint32_t id)
{
  return syscall(SYS_SEM_WAIT_ID, (uint64_t)id, 0, 0, 0);
}

int semPost(uint32_t id)
{
  return syscall(SYS_SEM_POST_ID, (uint64_t)id, 0, 0, 0);
}

int semClose(uint32_t id)
{
  return syscall(SYS_SEM_CLOSE_ID, (uint64_t)id, 0, 0, 0);
}

void semStatus() { (void)syscall(SYS_SEM_STATUS_ID, 0, 0, 0, 0); }

void memStatus() { (void)syscall(SYS_MEMORY_STATUS_ID, 0, 0, 0, 0); }

int getSecondsElapsed() { return syscall(SYS_SEC_ELAPSED_ID, 0, 0, 0, 0); }

void pipeStatus() { (void)syscall(SYS_PIPE_STATUS_ID, 0, 0, 0, 0); }

int pipeOpen(int pipeID)
{
  return syscall(SYS_PIPE_OPEN_ID, (uint64_t)pipeID, 0, 0, 0);
}

int pipeClose(int pipeID)
{
  return syscall(SYS_PIPE_CLOSE_ID, (uint64_t)pipeID, 0, 0, 0);
}

int pipeWrite(int pipeID, char *str)
{
  return syscall(SYS_PIPE_WRITE_ID, (uint64_t)pipeID, (uint64_t)str, 0, 0);
}

int pipeRead(int pipeID)
{
  return syscall(SYS_PIPE_READ_ID, (uint64_t)pipeID, 0, 0, 0);
}

void wait(int pipeID)
{
  (void)syscall(SYS_WAIT_ID, (uint64_t)pipeID, 0, 0, 0);
}