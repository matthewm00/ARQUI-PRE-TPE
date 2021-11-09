#include <syscallDispatcher.h>

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
    // updateRegisters();
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
        // antes estaba setTime(rsi);
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
