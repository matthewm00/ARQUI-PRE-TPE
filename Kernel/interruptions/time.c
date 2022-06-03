// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <time.h>

static unsigned long ticks = 0;
static unsigned long ticksCronometro = 0;
int cron = 0;

void timerHandler()
{
    ticks++;
    if (cron)
    {
        ticksCronometro++;
    }
}

int ticksElapsed() { return ticks; }

int secondsElapsed() { return ticks / 18; }

void setStopwatch(int option)
{
    if (option == RESET)
    {
        cron = 1;
        ticksCronometro = 0;
    }
    else if (option == PAUSE && cron == 0)
    {
        cron = 1; // pause / play
    }
    else
        cron = 0; // pauso los ticks
}

int getStopwatchTicks()
{
    return ticksCronometro;
}