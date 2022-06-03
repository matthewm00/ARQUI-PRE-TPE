#include <games.h>

static void divideScreen()
{
    _syscall(SYS_GAMES_ID, WHITE, 0, 0, 0, 0);
}

void changeCursorState(int state)
{
    _syscall(SYS_CURSORSTATE_ID, state, 0, 0, 0, 0);
}

void setCursor(uint64_t x, uint64_t y)
{
    _syscall(SYS_CURSOR_ID, x, y, 0, 0, 0);
}

uint64_t getTicks()
{
    return _syscall(SYS_TIME_ID, 0, 0, 0, 0, 0);
}

static uint64_t hourAux = 0;
static uint64_t minutesAux = 0;
static uint64_t secondsAux = 0;
static uint64_t ticksAux = 0;

static void resetTime()
{
    hourAux = 0;
    minutesAux = 0;
    secondsAux = 0;
    ticksAux = 0;
}
static void printTimeMsg()
{
    setCursor(530, 30);
    printf("La hora actual en Buenos Aires, Argentina (ART) es:\n");
    // changeCursorState(0);
}

int startGames()
{
    divideScreen();
    changeCursorState(0); // desactivamos el cursor
    setCursor(77, 1);
    printf("~~~ Pulse la tecla 0 para salir de games ~~~");

    resetTime();
    printTimeMsg();
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
            // changeCursorState(0);
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
    // resetTime();
    changeCursorState(1); // activamos el cursor
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

    if (hour != hourAux || (hour == 0 && hourAux == 0))
    {
        if (hour < 10)
        {
            setCursor(720, 200);
            printf(" 0%d::", hour);
            // changeCursorState(0);
        }
        else
        {
            setCursor(720, 200);
            printf(" %d::", hour);
            // changeCursorState(0);
        }
        hourAux = hour;
    }
    if (minutes != minutesAux || (minutes == 0 && minutesAux == 0))
    {
        if (minutes < 10)
        {
            setCursor(720 + 5 * CHAR_WIDTH, 200);
            printf("0%d::", minutes);
            // changeCursorState(0);
        }
        else
        {
            setCursor(720 + 5 * CHAR_WIDTH, 200);
            printf("%d::", minutes);
            // changeCursorState(0);
        }
        minutesAux = minutes;
    }
    if (seconds != secondsAux || (seconds == 0 && secondsAux == 0))
    {
        if (seconds < 10)
        {
            setCursor(720 + 9 * CHAR_WIDTH, 200);
            printf("0%d", seconds);
            // changeCursorState(0);
        }
        else
        {
            setCursor(720 + 9 * CHAR_WIDTH, 200);
            printf("%d", seconds);
            // changeCursorState(0);
        }
        secondsAux = seconds;
    }
    return;
}