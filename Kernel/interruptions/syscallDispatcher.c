// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <keyboardDriver.h>
#include <memoryManager.h>
#include <pipes.h>
#include <processManager.h>
#include <processManagerQueue.h>
#include <semaphores.h>
#include <syscallDispatcher.h>
#include <syscalls.h>
#include <time.h>
#include <videoDriver.h>

<<<<<<< HEAD
=======
// uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
// {
//     switch (rdi)
//     {
//     case SYS_WRITE_ID:
//         sys_write((char *)(rsi), (uint8_t)(rdx), (t_color)(rcx), (t_color)(r8));
//         break;
//     case SYS_RTC_ID:
//         return getCurrentTime((uint8_t)rsi);
//         break;
//     case SYS_READ_ID:
//         return sys_read();
//         break;
//     case SYS_PRINTMEM_ID:
//         getMem(rsi, (uint8_t *)rdx, rcx);
//         break;
//     case SYS_INFOREG_ID:
//         return (uint64_t)getRegisters();
//         break;
//     case SYS_CLEAR_ID:
//         clearScreen();
//         break;
//     case SYS_EXIT_ID:
//         _exit(0);
//         break;
//     case SYS_GAMES_ID:
//         divideScreen(rsi);
//     case SYS_TIME_ID:
//         return ticks_elapsed();
//         break;
//     case SYS_CURSOR_ID:
//         setCursor(rsi, rdx); // pasa la posicion donde imprimir
//         break;
//     case SYS_CURSORSTATE_ID:
//         changeCursorState(rsi);
//         break;
//     case SYS_STOPWATCH_ID:
//         setStopwatch(rsi); // prende o apaga el cronometro
//         break;
//     case SYS_STOPWATCHTICKS_ID:
//         return getStopwatchTicks();
//         break;

//         // nuevos:

//     case SYS_MALLOC_ID:
//         return (uint64_t)malloc((size_t)rsi);
//         break;
//     case SYS_FREE_ID:
//         free((void *)rsi);
//         return 0;
//         break;
//     case SYS_MEMORY_STATUS_ID:
//         memoryDump();
//         return 0;
//         break;
//     case SYS_NEW_PROCESS_ID:
//         return newProcess((void (*)(int, char **))rsi, (int)rdx, (char **)rcx, (int)r8, (int *)r9);
//         break;
//     case SYS_KILL_PROCESS_ID:
//         return killProcess(rsi);
//         break;
//     case SYS_PROCESS_PID_ID:
//         return getProcessPID();
//         break;
//     case SYS_PROCESS_STATUS_ID:
//         printProcessStatus();
//         return 0;
//         break;
//     case SYS_BLOCK_PROCESS_ID:
//         return blockProcess(rsi);
//         break;
//     case SYS_CHANGE_PROCESS_STATE_ID:
//         return setState(rsi, (t_state)rdx);
//         break;
//     case SYS_YIELD_ID:
//         yield();
//         return 0;
//         break;
//     case SYS_SET_PRIORITY_ID:
//         setPriority(rsi, (int)rdx);
//         return 0;
//         break;
//     case SYS_UNBLOCK_PROCESS_ID:
//         return readyProcess(rsi);
//         break;
//     case SYS_SEM_OPEN_ID:
//         return semOpen(rsi, rdx);
//         break;
//     case SYS_SEM_POST_ID:
//         return semWait(rsi);
//         break;
//     case SYS_SEM_WAIT_ID:
//         return semPost(rsi);
//         break;
//     case SYS_SEM_CLOSE_ID:
//         return semClose(rsi);
//         break;
//     case SYS_SEM_STATUS_ID:
//         semStatus();
//         break;
//     case SYS_SEC_ELAPSED_ID:
//         return seconds_elapsed();
//         break;
//     case SYS_PIPE_STATUS_ID:
//         pipeStatus();
//         break;
//     case SYS_PIPE_OPEN_ID:
//         return pipeOpen((int)rsi);
//         break;
//     case SYS_PIPE_CLOSE_ID:
//         return pipeClose((int)rsi);
//         break;
//     case SYS_PIPE_WRITE_ID:
//         return pipeWrite((int)rsi, (char *)rdx);
//         break;
//     case SYS_PIPE_READ_ID:
//         return pipeRead((int)rsi);
//         break;
//     case SYS_WAIT_ID:
//         wait((int)rsi);
//         break;
//     default:
//         break;
//     }
//     return 0;
// }

>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
typedef int (*functionPointer)(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                               uint64_t r8, uint64_t r9);

static int getCurrentTimeWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                                 uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  return getCurrentTime((uint8_t)rsi);
=======
    return getCurrentTime((uint8_t)rsi);
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int sysWriteWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                           uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  sysWrite((char *)(rsi), (uint8_t)(rdx), (t_color)(rcx), (t_color)(r8),
           (int)r9);
  return 0;
=======
    sys_write((char *)(rsi), (uint8_t)(rdx), (t_color)(rcx), (t_color)(r8));
    return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int sysReadWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                          uint64_t r9)
{
<<<<<<< HEAD
  return sysRead();
=======
    return sys_read();
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int getRegistersWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                               uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  return (uint64_t)getRegisters();
=======
    return (uint64_t)getRegisters();
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int getMemWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                         uint64_t r9)
{
<<<<<<< HEAD
  getMem(rsi, (uint8_t *)rdx, rcx);
  return 0;
=======
    getMem(rsi, (uint8_t *)rdx, rcx);
    return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int clearScreenWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                              uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  clearScreen();
  return 0;
=======
    clearScreen();
    return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int exitWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                       uint64_t r9)
{
<<<<<<< HEAD
  _exit();
  return 0;
=======
    _exit();
    return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int mallocWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                         uint64_t r9)
{
<<<<<<< HEAD
  return (uint64_t)malloc((size_t)rsi);
=======
    return (uint64_t)malloc((size_t)rsi);
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int freeWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                       uint64_t r9)
{
<<<<<<< HEAD
  free((void *)rsi);
  return 0;
=======
    free((void *)rsi);
    return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int memDumpWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                          uint64_t r9)
{
<<<<<<< HEAD
  memoryDump();
  return 0;
=======
    memoryDump();
    return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int newProcessWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                             uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  return newProcess((void (*)(int, char **))rsi, (int)rdx, (char **)rcx,
                    (int)r8, (int *)r9);
=======
    return newProcess((void (*)(int, char **))rsi, (int)rdx, (char **)rcx,
                      (int)r8, (int *)r9);
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int killProcessWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                              uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  return killProcess(rsi);
=======
    return killProcess(rsi);
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int getProcessPIDWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                                uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  return getProcessPID();
=======
    return getProcessPID();
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int processStatusWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                                uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  printProcessStatus();
  return 0;
=======
    printProcessStatus();
    return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int blockProcessWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                               uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  return blockProcess(rsi);
=======
    return blockProcess(rsi);
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int setStateWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                           uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  return setState(rsi, (t_state)rdx);
=======
    return setState(rsi, (t_state)rdx);
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int yieldWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                        uint64_t r9)
{
<<<<<<< HEAD
  yield();
  return 0;
=======
    yield();
    return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int setPriorityWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                              uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  setPriority(rsi, (int)rdx);
  return 0;
=======
    setPriority(rsi, (int)rdx);
    return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int readyProcessWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                               uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  return readyProcess(rsi);
=======
    return readyProcess(rsi);
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int semOpenWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                          uint64_t r9)
{
<<<<<<< HEAD
  return semOpen((uint32_t)rsi, rdx);
=======
    return semOpen((uint32_t)rsi, rdx);
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int semPostWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                          uint64_t r9)
{
<<<<<<< HEAD
  return semPost((uint32_t)rsi);
=======
    return semPost((uint32_t)rsi);
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int semWaitWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                          uint64_t r9)
{
<<<<<<< HEAD
  return semWait((uint32_t)rsi);
=======
    return semWait((uint32_t)rsi);
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int semCloseWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                           uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  return semClose((uint32_t)rsi);
=======
    return semClose((uint32_t)rsi);
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int semStatusWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                            uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  semStatus();
  return 0;
=======
    semStatus();
    return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int getSecondsElapsedWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                                    uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  return secondsElapsed();
=======
    return seconds_elapsed();
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int pipeStatusWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                             uint64_t r8, uint64_t r9)
{
<<<<<<< HEAD
  pipeStatus();
  return 0;
}

static int pipeOpenWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                           uint64_t r8, uint64_t r9)
{
  return pipeOpen((int)rsi);
}

static int pipeCloseWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                            uint64_t r8, uint64_t r9)
{
  return pipeClose((int)rsi);
}

static int pipeWriteWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                            uint64_t r8, uint64_t r9)
{
  return pipeWrite((int)rsi, (char *)rdx);
}

static int pipeReadWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                           uint64_t r8, uint64_t r9)
{
  return pipeRead((int)rsi);
}

static int waitWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                       uint64_t r9)
{
  wait((int)rsi);
  return 0;
}

static int gamesWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                        uint64_t r8, uint64_t r9)
{
  divideScreen(rsi);
  return 0;
}

static int timeWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                       uint64_t r8, uint64_t r9)
{
  return ticksElapsed();
}

static int cursorWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                         uint64_t r8, uint64_t r9)
{
  setCursor(rsi, rdx); // pasa la posicion donde imprimir
  return 0;
}
static int cursorStateWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                              uint64_t r8, uint64_t r9)
{
  changeCursorState(rsi);
  return 0;
}
static int stopwatchWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                            uint64_t r8, uint64_t r9)
{
  setStopwatch(rsi);
  return 0;
}
static int stopwatchticksWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                                 uint64_t r8, uint64_t r9)
{
  return getStopwatchTicks();
}

static functionPointer syscall[] = {
    getCurrentTimeWrapper,
    sysReadWrapper,
    sysWriteWrapper,
    getRegistersWrapper,
    getMemWrapper,
    clearScreenWrapper,
    exitWrapper,

    gamesWrapper,
    timeWrapper,
    cursorWrapper,
    cursorStateWrapper,
    stopwatchWrapper,
    stopwatchticksWrapper,

    mallocWrapper,
    freeWrapper,
    memDumpWrapper,
    newProcessWrapper,
    killProcessWrapper,
    getProcessPIDWrapper,
    processStatusWrapper,
    blockProcessWrapper,
    setStateWrapper,
    yieldWrapper,
    setPriorityWrapper,
    readyProcessWrapper,
    semOpenWrapper,
    semPostWrapper,
    semWaitWrapper,
    semCloseWrapper,
    semStatusWrapper,
    getSecondsElapsedWrapper,
    pipeStatusWrapper,
    pipeOpenWrapper,
    pipeCloseWrapper,
    pipeWriteWrapper,
    pipeReadWrapper,
    waitWrapper,
};

int syscallSelector(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx,
                    uint64_t r8, uint64_t r9)
{
  return syscall[rdi](rsi, rdx, rcx, r8, r9);
=======
    pipeStatus();
    return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static int pipeOpenWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                           uint64_t r8, uint64_t r9)
{
    return pipeOpen((int)rsi);
}

static int pipeCloseWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                            uint64_t r8, uint64_t r9)
{
    return pipeClose((int)rsi);
}

static int pipeWriteWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                            uint64_t r8, uint64_t r9)
{
    return pipeWrite((int)rsi, (char *)rdx);
}

static int pipeReadWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                           uint64_t r8, uint64_t r9)
{
    return pipeRead((int)rsi);
}

static int waitWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                       uint64_t r9)
{
    wait((int)rsi);
    return 0;
}

static int gamesWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                        uint64_t r8, uint64_t r9)
{
    divideScreen(rsi);
    return 0;
}

static int timeWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                       uint64_t r8, uint64_t r9)
{
    return ticks_elapsed();
}

static int cursorWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                         uint64_t r8, uint64_t r9)
{
    setCursor(rsi, rdx); // pasa la posicion donde imprimir
    return 0;
}
static int cursorStateWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                              uint64_t r8, uint64_t r9)
{
    changeCursorState(rsi);
    return 0;
}
static int stopwatchWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                            uint64_t r8, uint64_t r9)
{
    setStopwatch(rsi);
    return 0;
}
static int stopwatchticksWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                                 uint64_t r8, uint64_t r9)
{
    return getStopwatchTicks();
}

static functionPointer syscall[] = {
    getCurrentTimeWrapper,
    sysReadWrapper,
    sysWriteWrapper,
    getRegistersWrapper,
    getMemWrapper,
    clearScreenWrapper,
    exitWrapper,

    gamesWrapper,
    timeWrapper,
    cursorWrapper,
    cursorStateWrapper,
    stopwatchWrapper,
    stopwatchticksWrapper,

    mallocWrapper,
    freeWrapper,
    memDumpWrapper,
    newProcessWrapper,
    killProcessWrapper,
    getProcessPIDWrapper,
    processStatusWrapper,
    blockProcessWrapper,
    setStateWrapper,
    yieldWrapper,
    setPriorityWrapper,
    readyProcessWrapper,
    semOpenWrapper,
    semPostWrapper,
    semWaitWrapper,
    semCloseWrapper,
    semStatusWrapper,
    getSecondsElapsedWrapper,
    pipeStatusWrapper,
    pipeOpenWrapper,
    pipeCloseWrapper,
    pipeWriteWrapper,
    pipeReadWrapper,
    waitWrapper,
};

int syscallSelector(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx,
                    uint64_t r8, uint64_t r9)
{
    return syscall[rdi](rsi, rdx, rcx, r8, r9);
}