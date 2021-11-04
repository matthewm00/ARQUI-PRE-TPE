#include <time.h>

static unsigned long ticks = 0;
static unsigned long ticksCronometro = 0;
static int cron = 0;

void timer_handler()
{
	ticks++;
	ticksCronometro++;
	if (cron)
	{
		// posicion donde se imprime el cronometro:
		setCursor(WIDTH / 4 * CHAR_WIDTH, 2);

		sys_write("STOPWATCH: ", 11, BLACK, WHITE, 0);

		printIntDec(ticksCronometro / 18);

		stopCursor();
	}
}

int ticks_elapsed()
{
	return ticks;
}

int seconds_elapsed()
{
	return ticks / 18;
}

void setStopwatch(int activate)
{
	if (activate)
	{
		ticksCronometro = 0;
		cron = 1;
	}
	else
	{
		cron = 0;
	}
}

int getSecondsStopwatch()
{
	char buffer[10];
	return uintToBase(ticksCronometro / 18, buffer, 10);
}
