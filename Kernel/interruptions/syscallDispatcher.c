#include <syscallDispatcher.h>

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

        // nuevos:

    case SYS_MALLOC_ID:
        return (uint64_t)malloc((size_t)rsi);
        break;
    case SYS_FREE_ID:
        free((void *)rsi);
        return 0;
        break;
    case SYS_MEMORY_STATUS_ID:
        memoryDump();
        return 0;
        break;
    case SYS_NEW_PROCESS_ID:
        return newProcess((void (*)(int, char **))rsi, (int)rdx, (char **)rcx, (int)r8);
        break;
    case SYS_KILL_PROCESS_ID:
        return killProcess(rsi);
        break;
    case SYS_PROCESS_PID_ID:
        return getProcessPID();
        break;
    case SYS_PROCESS_STATUS_ID:
        printProcessStatus();
        return 0;
        break;
    case SYS_BLOCK_PROCESS_ID:
        return blockProcess(rsi);
        break;
    case SYS_CHANGE_PROCESS_STATE_ID:
        return setState(rsi, (t_state)rdx);
        break;
    case SYS_YIELD_ID:
        yield();
        return 0;
        break;
    case SYS_SET_PRIORITY_ID:
        setPriority(rsi, (int)rdx);
        return 0;
        break;
    case SYS_UNBLOCK_PROCESS_ID:
        return readyProcess(rsi);
        break;
    case SYS_SEM_OPEN_ID:
        break;
    case SYS_SEM_POST_ID:
        break;
    case SYS_SEM_WAIT_ID:
        break;
    case SYS_SEM_CLOSE_ID:
        break;
    case SYS_SEM_STATUS_ID:
        break;
    case SYS_SEC_ELAPSED_ID:
        break;
    case SYS_PIPE_STATUS_ID:
        break;
    case SYS_PIPE_OPEN_ID:
        break;
    case SYS_PIPE_CLOSE_ID:
        break;
    case SYS_PIPE_WRITE_ID:
        break;
    case SYS_PIPE_READ_ID:
        break;
    case SYS_WAIT_ID:
        break;

    default:
        break;
    }
    return 0;
}
