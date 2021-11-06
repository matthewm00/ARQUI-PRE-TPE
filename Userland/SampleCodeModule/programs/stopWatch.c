#include <stopWatch.h>

uint64_t getStopWatchTicks()
{
    return _syscall(SYS_STOPWATCHTICKS_ID, 0, 0, 0, 0, 0);
}

void setStopWatch(int option)
{
    _syscall(SYS_STOPWATCH_ID, option, 0, 0, 0, 0);
}

void initStopWatch()
{
    setCursor(0, 30);
    printf("Las teclas para accionar el cronomentro son las siguientes:\n\n");
    printf("Tecla 'p' : PLAY / PAUSE\n");
    printf("Tecla 'r' : RESET\n");
    setCursor(WIDTH / 7, 200);
    printf("CRONOMETRO:");
    changeCursorState(0);
    setStopWatch(RESET);
}

uint64_t swTicksAux = 0;

void stopWatch()
{
    uint64_t swTicks = getStopWatchTicks();
    char buffer[1];

    if (swTicks != swTicksAux)
    {
        setCursor(((WIDTH / 7) + (14 * CHAR_WIDTH)), 200);

        // printf("entre lmp");
        // changeCursorState(0);

        // printf(intToStr(swTicks, buffer, 10));

        printf("%d", swTicks / 18);

        changeCursorState(0);

        swTicksAux = swTicks;
    }
}