#include <games.h>

static void clearScreen()
{
    _syscall(SYS_CLEAR_ID, 0, 0, 0, 0, 0);
}

static void divideScreen()
{
    _syscall(SYS_GAMES_ID, WHITE, 0, 0, 0, 0);
}

void changeCursorState(int state)
{
    _syscall(SYS_CURSORSTATE_ID, state, 0, 0, 0, 0);
}

static uint64_t getTicks()
{
    return _syscall(SYS_TIME_ID, 0, 0, 0, 0, 0);
}

void setCursor(uint64_t x, uint64_t y)
{
    _syscall(SYS_CURSOR_ID, x, y, 0, 0, 0);
}

uint64_t hourAux = 0;
uint64_t minAux = 0;
uint64_t secAux = 0;
uint64_t ticksAux = 0;

int startGames()
{
    clearScreen();
    divideScreen();
    changeCursorState(0);

    baseSudoku();
    startHangman();
    initStopWatch();

    int exit = 0;

    while (!exit)
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
            changeCursorState(0);
        }
        else if (c == 'r')
        {
            setStopWatch(RESET);
        }
        else if (c == 'p')
        {
            setStopWatch(PAUSE);
        }
        else if (c == '0')
        {
            exit = 1;
        }
        stopWatch();
    }

    clearScreen();
    changeCursorState(1);
    printf("Volviendo a la shell...\n");

    return 0;
}

void printTime()
{
    uint64_t ticks = getTicks();

    if (ticks / 18 <= ticksAux / 18)
        return;

    uint64_t hour = _syscall(SYS_RTC_ID, HOUR_RTC_ID, 0, 0, 0, 0);
    uint64_t minutes = _syscall(SYS_RTC_ID, MINUTE_RTC_ID, 0, 0, 0, 0);
    uint64_t seconds = _syscall(SYS_RTC_ID, SECOND_RTC_ID, 0, 0, 0, 0);
    ticksAux = ticks;

    if (hour != hourAux)
    {
        if (hour < 10)
        {
            setCursor(800, 70);
            printf(" 0%d::", hour);
            changeCursorState(0);
        }
        else
        {
            setCursor(800, 70);
            printf(" %d::", hour);
            changeCursorState(0);
        }
        hourAux = hour;
    }
    if (minutes != minAux)
    {
        if (minutes < 10)
        {
            setCursor(800 + 5 * CHAR_WIDTH, 70);
            printf("0%d::", minutes);
            changeCursorState(0);
        }
        else
        {
            setCursor(800 + 5 * CHAR_WIDTH, 70);
            printf("%d::", minutes);
            changeCursorState(0);
        }
        minAux = minutes;
    }
    if (seconds != secAux)
    {
        if (seconds < 10)
        {
            setCursor(800 + 9 * CHAR_WIDTH, 70);
            printf("0%d", seconds);
            changeCursorState(0);
        }
        else
        {
            setCursor(800 + 9 * CHAR_WIDTH, 70);
            printf("%d", seconds);
            changeCursorState(0);
        }
        secAux = seconds;
    }
}