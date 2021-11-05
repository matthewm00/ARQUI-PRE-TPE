#include <time.h>

static unsigned long ticks = 0;
static unsigned long ticksCronometro = 0;
int cron = 0;
void timer_handler()
{
	ticks++;
	ticksCronometro++;

	// if (cron)
	// {
	// 	// posicion donde se imprime el cronometro:
	// 	setCursor(WIDTH / 4 * CHAR_WIDTH, 2);

	// printIntDec(ticksCronometro);

	// 	stopCursor();
	// }
	// if (time)
	// {
	// 	printTime();
	// }
}

int ticks_elapsed()
{
	return ticks;
}

int seconds_elapsed()
{
	return ticks / 18;
}

void setStopwatch()
{
	cron = 1;
	ticksCronometro = 0;
}

int getStopwatchTicks()
{
	return ticksCronometro;
}

// void setTime(int activate)
// {
// 	time = activate;
// }

// uint64_t hourAux;
// uint64_t minAux;
// uint64_t secAux;

// void printTime()
// {
// 	uint64_t hour = getCurrentTime(HOUR_RTC_ID);
// 	uint64_t minutes = getCurrentTime(MINUTE_RTC_ID);
// 	uint64_t seconds = getCurrentTime(SECOND_RTC_ID);

// 	if (hour != hourAux)
// 	{
// 		if (hour < 10)
// 		{
// 			setCursor(800, 70);
// 			printf(" 0%d::", hour);
// 			sys_write()
// 		}
// 		else
// 		{
// 			setCursor(800, 70);
// 			printf(" %d::", hour);
// 		}
// 		hourAux = hour;
// 	}
// 	if (minutes != minAux)
// 	{
// 		if (minutes < 10)
// 		{
// 			setCursor(800 + 5 * CHAR_WIDTH, 70);
// 			printf("0%d::", minutes);
// 		}
// 		else
// 		{
// 			setCursor(800 + 5 * CHAR_WIDTH, 70);
// 			printf("%d::", minutes);
// 		}
// 		minAux = minutes;
// 	}
// 	if (seconds != secAux)
// 	{
// 		if (seconds < 10)
// 		{
// 			setCursor(800 + 9 * CHAR_WIDTH, 70);
// 			printf("0%d", seconds);
// 		}
// 		else
// 		{
// 			setCursor(800 + 9 * CHAR_WIDTH, 70);
// 			printf("%d", seconds);
// 		}
// 		secAux = seconds;
// 	}
// }
