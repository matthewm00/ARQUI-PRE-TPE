#include <libC.h>

// https://www.techiedelight.com/implement-strcpy-function-c/
char *strcpy(char *destination, const char *source)
{
    char *ptr = destination;
    while (*source != 0)
    {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = 0;
    return ptr;
}

int strToInt(char *charValue)
{
    int toReturn = 0;
    for (int i = 0; charValue[i] != '\0'; ++i)
        toReturn = toReturn * 10 + charValue[i] - '0';

    return toReturn;
}

int numToStr(char *str, int num)
{
    int dim = 0;
    int negativo = 0;
    if (num == 0)
    {
        str[dim++] = num + '0';
    }
    if (num < 0)
    {
        negativo = 1;
        num *= -1;
    }

    while (num != 0)
    {
        int res = num % 10;
        str[dim++] = res + '0';
        num /= 10;
    }
    if (negativo)
    {
        str[dim++] = '-';
    }
    int i = 0;
    int j = dim - 1;
    while (i < j)
    {
        char aux = str[i];
        str[i] = str[j];
        str[j] = aux;
        j--;
        i++;
    }

    str[dim] = 0;
    return dim;
}

int strcmp(char *s1, char *s2)
{
    int cmp = 1;
    int i;
    for (i = 0; s1[i] != 0 && s2[i] != 0 && cmp; i++)
    {
        if (s1[i] != s2[i])
        {
            cmp = 0;
        }
    }

    if ((s1[i] == 0 && s2[i] != 0) || (s1[i] != 0 && s2[i] == 0))
    {
        cmp = 0;
    }
    return cmp;
}

uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base)
{
    char *p = buffer;
    char *p1, *p2;
    uint32_t digits = 0;

    // Calculate characters for each digit
    do
    {
        uint32_t remainder = value % base;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
        digits++;
    } while (value /= base);

    // Terminate string in buffer.
    *p = 0;

    // Reverse string in buffer.
    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

    return digits;
}

void parseHexa(char *buff, int dim)
{
    char auxStr[5] = "0x00";
    for (int j = 3; j >= 0 && dim != 0; j--)
    {
        auxStr[j] = buff[dim - 1];
        dim--;
    }
    for (int i = 0; i < 4; i++)
    {
        buff[i] = auxStr[i];
    }
}