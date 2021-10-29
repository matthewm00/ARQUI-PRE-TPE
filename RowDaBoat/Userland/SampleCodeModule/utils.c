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

int strlen(char *str)
{
    int size = 0;
    for (int i = 0; str[i] != 0; i++)
    {
        size++;
    }
    return size;
}

void *memcpy(void *destination, const void *source, uint64_t length)
{
    /*
     * memcpy does not support overlapping buffers, so always do it
     * forwards. (Don't change this without adjusting memmove.)
     *
     * For speedy copying, optimize the common case where both pointers
     * and the length are word-aligned, and copy word-at-a-time instead
     * of byte-at-a-time. Otherwise, copy by bytes.
     *
     * The alignment logic below should be portable. We rely on
     * the compiler to be reasonably intelligent about optimizing
     * the divides and modulos out. Fortunately, it is.
     */
    uint64_t i;

    if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
        (uint64_t)source % sizeof(uint32_t) == 0 &&
        length % sizeof(uint32_t) == 0)
    {
        uint32_t *d = (uint32_t *)destination;
        const uint32_t *s = (const uint32_t *)source;

        for (i = 0; i < length / sizeof(uint32_t); i++)
            d[i] = s[i];
    }
    else
    {
        uint8_t *d = (uint8_t *)destination;
        const uint8_t *s = (const uint8_t *)source;

        for (i = 0; i < length; i++)
            d[i] = s[i];
    }

    return destination;
}

int isNum(char *str)
{
    int index = 0;
    if (str[index] == '.')
    {
        return 0;
    }
    if (str[index] == '-')
    {
        index++;
    }
    if (!IS_DIGIT(str[index]))
    {
        return 0;
    }
    for (; str[index] != 0 && str[index] != '.'; index++)
    {
        if (!IS_DIGIT(str[index]))
        {
            return 0;
        }
    }
    if (str[index] == '.')
    {
        index++;
        for (; str[index] != 0; index++)
        {
            if (!IS_DIGIT(str[index]))
            {
                return 0;
            }
        }
    }
    return 1;
}