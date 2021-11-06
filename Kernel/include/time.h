#ifndef _TIME_H_
#define _TIME_H_

#include <videoDriver.h>
#include <fonts.h>
#include <syscalls.h>
#include <prints.h>
#include <stdint.h>

#define DAY_RTC_ID 0x07
#define MONTH_RTC_ID 0x08
#define YEAR_RTC_ID 0x09
#define HOUR_RTC_ID 0x04
#define MINUTE_RTC_ID 0x02
#define SECOND_RTC_ID 0x00

#define RESET 0
#define PAUSE 1

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
void setStopwatch(int option);
int getStopwatchTicks();
#endif
