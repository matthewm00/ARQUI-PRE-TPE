#ifndef _TIME_H_
#define _TIME_H_

#include <videoDriver.h>
#include <fonts.h>
#include <syscalls.h>
#include <prints.h>
#include <stdint.h>

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();

void setStopwatch(int activate);
int getSecondsStopwatch();
#endif
