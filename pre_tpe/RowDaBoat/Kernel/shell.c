#include <shell.h>

typedef struct
{
    uint32_t posX;
    uint32_t posY;
} t_screen;

t_screen screen = {0, 0};

typedef struct
{
    uint32_t posX;
    uint32_t posY;
    uint32_t setted;
} t_cursor;

t_cursor cursor = {0, 0, 0};

void print(char *buff, uint64_t length, uint64_t fontColor, uint64_t backgroundColor)
{
}