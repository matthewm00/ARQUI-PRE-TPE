#ifndef _TIME_H_
#define _TIME_H_

#define RESET 0
#define PAUSE 1

void timerHandler();
int ticksElapsed();
int secondsElapsed();

void setStopwatch(int option);
int getStopwatchTicks();

#endif
