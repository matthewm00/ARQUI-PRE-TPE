#include <syscallDispatcher.h>

uint64_t syscallDispatcher(uint64_t *r[REGISTERS])
{
    switch (*r[RAX])
    {
    case 0:
        read(r[RDI], *r[RSI]);
        break;

    case 1:
        // ver el tema de los registros
        write(r[RDI], *r[RSI], *r[RDX], *r[RCX]);
        break;

    default:
        break;
    }
}

void read(uint64_t *buff, uint64_t length)
{
    char *keyboardBuffer = getKeyboardBuffer();
    cleanBuffer();

    for (int i = 0; i < length && keyboardBuffer[i] != 0; i++)
    {
        if (keyboardBuffer[i] == SPACE_BAR)
        {
            ((char *)buff)[i] = ' ';
        }
        else if (L_SHIFT == keyboardBuffer[i] || R_SHIFT == keyboardBuffer[i] || R_SHIFT_RELEASED == keyboardBuffer[i] || L_SHIFT_RELEASED == keyboardBuffer[i])
        {
            ; /// chequear que no se agrega al buffer ningun shift, etc
            // para estas teclas solo se deberian prender los flags
        }
        else
        {
            ((char *)buff)[i] = keyboardBuffer[i];
        }
    }
}
void write(uint64_t *buff, uint64_t length, uint64_t fontColor, uint64_t background_color)
{
    if (length <= 0 || fontColor < 0 || background_color < 0)
    {
        return;
    }
    print((char *)buff, length, fontColor, background_color);
}
