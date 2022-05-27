#include <stopWatch.h>

uint64_t getStopWatchTicks()
{
    return syscall(SYS_STOPWATCHTICKS_ID, 0, 0, 0, 0);
}

static uint64_t secAux = 0;
static uint64_t minAux = 0;
// static uint64_t swTicksAux = 0;
// static uint64_t dsecAux1 = 0;
// static uint64_t dsecAux2 = 0;
// static int pause = 1;

void setStopWatch(int option)
{
    // if (option == RESET)
    //     dsecAux1 = 0;
    // else
    //     pause = !pause;

    syscall(SYS_STOPWATCH_ID, option, 0, 0, 0);
    return;
}

void initStopWatch()
{
    secAux = 0;
    minAux = 0;
    setCursor(0, 30);
    printf("Las teclas para accionar el cronomentro son las siguientes:\n\n");
    printf("Tecla 'p' : PLAY / PAUSE\n");
    printf("Tecla 'r' : RESET\n");
    setCursor(WIDTH / 7, 200);
    printf("CRONOMETRO:");
    setCursor(((WIDTH / 7) + (14 * CHAR_WIDTH)), 200);
    printf("00::00::00");
    // changeCursorState(0);
    setStopWatch(RESET);
    return;
}

void stopWatch()
{
    uint64_t swTicks = getStopWatchTicks();

    uint64_t dsec = swTicks % 100;

    if (dsec < 10)
    {
        setCursor(((WIDTH / 7) + (22 * CHAR_WIDTH)), 200);
        printf("0%d", dsec);
        // changeCursorState(0);
    }
    else
    {
        setCursor(((WIDTH / 7) + (22 * CHAR_WIDTH)), 200);
        printf("%d", dsec);
        // changeCursorState(0);
    }
    // if (!pause)
    // {
    //     swTicksAux ++;

    //     dsecAux1++;
    //     if (dsecAux1 > dsecAux2 + 55 * 5)
    //     {
    //         dsecAux2 = dsecAux1;
    //         uint64_t dsec = dsecAux1 % 100;
    //         setCursor(((WIDTH / 7) + (22 * CHAR_WIDTH)), 200);
    //         printf("%d", dsec);
    //     }
    // }

    uint64_t sec = swTicks / 18;
    uint64_t min = sec / 60;
    sec = sec % 60;

    if (sec != secAux)
    {
        secAux = sec;

        if (sec < 10)
        {
            setCursor(((WIDTH / 7) + (18 * CHAR_WIDTH)), 200);
            printf("0%d::", sec);
            // changeCursorState(0);
        }
        else
        {
            setCursor(((WIDTH / 7) + (18 * CHAR_WIDTH)), 200);
            printf("%d::", sec);
            // changeCursorState(0);
        }
    }

    if (min != minAux)
    {
        setCursor(((WIDTH / 7) + (14 * CHAR_WIDTH)), 200);
        printf("0%d::", min);
        // changeCursorState(0);
        minAux = min;
    }

    // changeCursorState(0);
    return;
}