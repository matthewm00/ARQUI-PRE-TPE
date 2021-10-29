#include <videoDriver.h>

struct vbe_mode_info_structure
{
    uint16_t attributes;  // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;     // deprecated
    uint8_t window_b;     // deprecated
    uint16_t granularity; // deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr; // deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;        // number of bytes per horizontal line
    uint16_t width;        // width in pixels
    uint16_t height;       // height in pixels
    uint8_t w_char;        // unused...
    uint8_t y_char;        // ...
    uint8_t planes;
    uint8_t bpp;   // bits per pixel in this mode
    uint8_t banks; // deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direct_color_attributes;

    uint32_t framebuffer; // physical address of the linear frame buffer; write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size; // size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];
} __attribute__((packed));

static struct vbe_mode_info_structure *screenData = (void *)0x5C00;

// Retorna un puntero de la posicion en pantalla a escribir
char *getPosition(uint32_t x, uint32_t y)
{
    return (char *)(((uint64_t)(screenData->framebuffer)) + (x + screenData->width * y) * 3);
    // casteo a uint64 para evitar warning
}
int getScreenWidth()
{
    return screenData->width;
}

int getScreenHeight()
{
    return screenData->height;
}

void drawPixel(int x, int y, int color)
{
    char *pos = getPosition(x, y);

    int r = (color >> 16) & 0x0000FF;
    int g = (color >> 8) & 0x0000FF;
    int b = color & 0x0000FF;

    *pos = b;
    pos++;
    *pos = g;
    pos++;
    *pos = r;
}

// usa font.c
void drawLetter(int key, int x, int y, int color, int background_color)
{
    unsigned char *letter = charBitmap(key);

    for (int i = 0; i < CHAR_WIDTH; i++)
    {
        for (int j = 0; j < CHAR_HEIGHT; j++)
        {
            if ((letter[j] >> (CHAR_WIDTH - i)) & 0x01)
            {
                drawPixel(x + i, j + y, color);
            }
            else
            {
                drawPixel(x + i, j + y, background_color);
            }
        }
    }
}

void drawRectangle(int x, int y, int color, int width, int height)
{

    for (int i = x; i < x + width; i++)
    {
        for (int j = y; j < y + height; j++)
        {
            drawPixel(i, j, color);
        }
    }
}

typedef struct
{
    uint32_t posX;
    uint32_t posY;
    uint32_t height;
    uint32_t width;
    uint64_t backgroundColor;
    uint64_t fontColor;
} t_screen;

t_screen screens[4];
t_screen *currentScreen;

void clearLineOnScreen()
{
    for (int y = 0; y < currentScreen->height; y++)
    {
        for (int x = 0; x < currentScreen->width; x++)
        {
            drawPixel(x + currentScreen->posX, currentScreen->posY + y, BLACK);
        }
    }
}

void deleteLast()
{
    if (currentScreen->posX)
    {
        for (int j = 0; j < CHAR_HEIGHT; j++)
        {
            for (int i = 0; i < CHAR_WIDTH; i++)
            {
                drawPixel(currentScreen->posX - i, currentScreen->posY + j, BLACK);
            }
        }
        currentScreen->posX -= CHAR_WIDTH;
    }
    return;
}

// retorna el color (en formato hexadecimal) del pixel
int getColorOfPixel(int x, int y)
{
    char *pos = getPosition(x, y);
    return ((pos[2] & 0xFF) << 16) + ((pos[1] & 0xFF) << 8) + (pos[0] & 0xFF);
}

void newLine(uint32_t width, uint32_t height, uint64_t fontColor, uint64_t background_color)
{
    // lleno fondo
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < screenData->width; x++)
        {
            drawPixel(x, y, BLACK);
        }
    }
    //  muevo lo anterior hacia arriba
    for (int y = 0; y < screenData->height - height; y++)
    {
        for (int x = 0; x < screenData->width; x++)
        {
            int color = getColorOfPixel(x, y);
            drawPixel(x, y, getColorOfPixel(x, y + height));
            drawPixel(x, y + height, color);
        }
    }
    currentScreen->posX = 0;
    return;
}

void initVideoDriver(uint64_t backgroundColor, uint64_t fontColor)
{
    t_screen screen1;
    screen1.backgroundColor = backgroundColor;
    screen1.fontColor = fontColor;
    screen1.posX = 0;
    screen1.posY = 0;
    screen1.height = screenData->height;
    screen1.width = screenData->width / 2 - 3 * CHAR_WIDTH - 2 * CHAR_WIDTH;
    screens[0] = screen1;

    // t_screen screen2;
    // screen2.backgroundColor = backgroundColor;
    // screen2.fontColor = fontColor;
    // screen2.posX = 0;
    // screen2.posY = 0;
    // screen2.height = screenData->height;
    // screen2.width = screenData->width / 2 - 2 * CHAR_WIDTH - 4 * CHAR_WIDTH;
    // screens[1] = screen2;

    // separateMainScreen();
}
void separateMainScreen()
{
    for (int y = 0; y < screenData->height; y++)
    {
        for (int x = 0; x < 2 * CHAR_WIDTH; x++)
        {
            drawPixel(screenData->width / 2 - CHAR_WIDTH + x, y, DARK_RED);
        }
    }
}
void changeScreen(int index)
{
    currentScreen = &screens[index];
}

void print(char *buff, uint64_t length, uint64_t fontColor, uint64_t backgroundColor)
{
    for (int i = 0; i < length; i++)
    {
        if (buff[i] == '\n' || currentScreen->posX == currentScreen->width) // si se introdujo un \n o se llego al final de la pantalla
        {
            newLine(CHAR_WIDTH, CHAR_HEIGHT, fontColor, backgroundColor); // sigue en una nueva linea, mueve lo anterior para arriba, elimina la de mas arriba si es necesario
        }
        else if (buff[i] == '\b') // backspace
        {
            deleteLast();
        }
        else
        {
            drawLetter(buff[i], currentScreen->posX, currentScreen->posY, fontColor, backgroundColor);
            currentScreen->posX += CHAR_WIDTH;
        }
    }
    return;
}
