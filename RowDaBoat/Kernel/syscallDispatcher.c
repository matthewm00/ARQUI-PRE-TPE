#include <syscallDispatcher.h>

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    switch (rdi)
    {
    case READ:
        read((uint64_t *)rsi, rdx);
        break;

    case WRITE:
        write((uint64_t *)rsi, rdx, rcx, r8);
        break;

    case RTC_TIME:
        // return getCurrentTime((uint8_t)rsi);
        break;

    case PRINTMEM:
        // getMem(rsi, (uint8_t *)rdx, rcx);
        break;

    case INFOREG:
        saveRegistersASM();
        return getRegisters();
        break;

    case CLEAR:
        clearScreen();
        break;

    case EXIT:
        exit();
        break;

    default:
        break;
    }
    return 0;
}

void read(uint64_t *buff, uint64_t length)
{
    char *keyboardBuffer = getKeyboardBuffer();

    for (int i = 0; i < length && keyboardBuffer[i] != 0; i++)
    {
        ((char *)buff)[i] = keyboardBuffer[i];
    }

    clearBuffer();
}

void write(uint64_t *buff, uint64_t length, uint64_t fontColor, uint64_t background_color)
{
    if (length <= 0 || fontColor < 0 || background_color < 0)
    {
        return;
    }
    for (int i = 0; buff[i] != 0 && i < length; i++)
        printChar(buff[i], fontColor, background_color, 1);
}
