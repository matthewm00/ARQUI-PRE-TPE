#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <games.h>

#define RESET 0
#define PAUSE 1

uint64_t getStopWatchTicks();
void setStopWatch(int option);

void initStopWatch();
void stopWatch();

#endif