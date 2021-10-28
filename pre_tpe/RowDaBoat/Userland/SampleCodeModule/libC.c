#include <libC.h>

int fontColor[1] = {0};
int backgroundColor[1] = {0};

void setFontColor(int color)
{
    *fontColor = color;
}
void setBackGroundColor(int color)
{
    *backgroundColor = color;
}

void putChar(char c)
{
    printf("%c", c);
}

char getChar()
{
    char c = 0;
    while (c == 0)
    {
        syscall(READ, &c, 1, 0, 0, 0, 0);
    }
    return c;
}
