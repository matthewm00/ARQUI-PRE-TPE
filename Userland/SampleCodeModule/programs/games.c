#include <games.h>

static void clearScreen()
{
    _syscall(SYS_CLEAR_ID, 0, 0, 0, 0, 0);
}
static void divideScreen()
{
    _syscall(SYS_GAMES_ID, WHITE, 0, 0, 0, 0);
}

static int setStopwatch = 0;
static int secondsStopwatch;

void startGames()
{
    clearScreen();
    divideScreen();

    while (1)
    {
        printTime();
        char c = getChar();
        if (c >= 'A' && c <= 'Z')
        {
            hangman(c);
        }
        else if (c >= '1' && c <= '9')
        {
            sudoku(c);
        }
        else if (c == 's') // boton que controla el prendido/apagado del cronometro
        {
            stopWatch(); // cuando activo esto se vuelve loco je
            // fijarse time.c en kernel
        }
        else if (c == '0')
        {
            clearScreen();
            printf("Volviendo a la shell...\n");
            return;
        }
    }
}

void hangman(char c)
{
}
void sudoku(char c)
{
}
void printTime()
{
    uint8_t hour = (uint8_t)_syscall(SYS_TIME_ID, 0, 0, 0, 0, 0);
    uint8_t minutes = (uint8_t)_syscall(SYS_TIME_ID, 1, 0, 0, 0, 0);
    uint8_t seconds = (uint8_t)_syscall(SYS_TIME_ID, 2, 0, 0, 0, 0);

    if (hour < 10)
    {
        printf(" 0%d:", hour);
    }
    else
    {
        printf(" %d:", hour);
    }
    if (minutes < 10)
    {
        printf("0%d:", minutes);
    }
    else
    {
        printf("%d:", minutes);
    }
    if (seconds < 10)
    {
        printf("0%d", seconds);
    }
    else
    {
        printf("%d", seconds);
    }
}

void stopWatch()
{
    setStopwatch = !setStopwatch;
    _syscall(SYS_STOPWATCH_ID, setStopwatch, 0, 0, 0, 0);
}

void updateSecondsStopwatch()
{
    secondsStopwatch = _syscall(SYS_STOPWATCHSEC_ID, 0, 0, 0, 0, 0);
}