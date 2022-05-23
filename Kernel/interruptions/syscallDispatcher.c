#include <syscallDispatcher.h>

static int mallocWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                         uint64_t r9)
{
    return (uint64_t)malloc((size_t)rsi);
}

static int freeWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                       uint64_t r9)
{
    free((void *)rsi);
    return 0;
}

static int memDumpWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                          uint64_t r9)
{
    memoryDump();
    return 0;
}

static int newProcessWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                             uint64_t r8, uint64_t r9)
{
    return newProcess((void (*)(int, char **))rsi, (int)rdx, (char **)rcx,
                      (int)r8, (int *)r9);
}

static int killProcessWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                              uint64_t r8, uint64_t r9)
{
    return killProcess(rsi);
}

static int getProcessPIDWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                                uint64_t r8, uint64_t r9)
{
    return getProcessPID();
}

static int processStatusWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                                uint64_t r8, uint64_t r9)
{
    printProcessStatus();
    return 0;
}

static int blockProcessWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                               uint64_t r8, uint64_t r9)
{
    return blockProcess(rsi);
}

static int setStateWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                           uint64_t r8, uint64_t r9)
{
    return setState(rsi, (t_state)rdx);
}

static int yieldWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8,
                        uint64_t r9)
{
    yield();
    return 0;
}

static int setPriorityWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                              uint64_t r8, uint64_t r9)
{
    setPriority(rsi, (int)rdx);
    return 0;
}

static int readyProcessWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx,
                               uint64_t r8, uint64_t r9)
{
    return readyProcess(rsi);
}

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
    switch (rdi)
    {
    case SYS_WRITE_ID:
        sys_write((char *)(rsi), (uint8_t)(rdx), (t_color)(rcx), (t_color)(r8));
        break;
    case SYS_RTC_ID:
        return getCurrentTime((uint8_t)rsi);
        break;
    case SYS_READ_ID:
        return sys_read();
        break;
    case SYS_PRINTMEM_ID:
        getMem(rsi, (uint8_t *)rdx, rcx);
        break;
    case SYS_INFOREG_ID:
        return (uint64_t)getRegisters();
        break;
    case SYS_CLEAR_ID:
        clearScreen();
        break;
    case SYS_EXIT_ID:
        _exit(0);
        break;
    case SYS_GAMES_ID:
        divideScreen(rsi);
    case SYS_TIME_ID:
        return ticks_elapsed();
        break;
    case SYS_CURSOR_ID:
        setCursor(rsi, rdx); // pasa la posicion donde imprimir
        break;
    case SYS_CURSORSTATE_ID:
        changeCursorState(rsi);
        break;
    case SYS_STOPWATCH_ID:
        setStopwatch(rsi); // prende o apaga el cronometro
        break;
    case SYS_STOPWATCHTICKS_ID:
        return getStopwatchTicks();
        break;
    default:
        break;
    }
    return 0;
}
