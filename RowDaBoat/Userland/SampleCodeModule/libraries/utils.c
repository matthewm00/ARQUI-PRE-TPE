#include <libC.h>

static int ishexdigit(char ch)
{
    return IS_DIGIT(ch) || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f');
}

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
int strToHex(const char *str)
{
    int val = 0;
    while (*str != 0)
    {
        if (!ishexdigit(*str))
        {
            return -1;
        }
        if (IS_DIGIT(*str))
        {
            val = val * 16 + *str++ - '0';
        }
        else if (*str >= 'A' && *str <= 'F')
        {
            val = val * 16 + *str++ - 'A' + 10;
        }
        else
        {
            val = val * 16 + *str++ - 'a' + 10;
        }
    }
    return val;
}

// Iterative function to implement itoa() function in C
char *intToStr(int value, char *buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32)
    {
        return buffer;
    }

    // consider the absolute value of the number
    int n = ABS(value);

    int i = 0;
    while (n)
    {
        int r = n % base;

        if (r >= 10)
        {
            buffer[i++] = 65 + (r - 10);
        }
        else
        {
            buffer[i++] = 48 + r;
        }

        n = n / base;
    }

    // if the number is 0
    if (i == 0)
    {
        buffer[i++] = '0';
    }

    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10)
    {
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // null terminate string

    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

// function to reverse buffer[i..j]
char *reverse(char *buffer, int i, int j)
{
    while (i < j)
        swap(&buffer[i++], &buffer[j--]);

    return buffer;
}
void swap(char *x, char *y)
{
    char t = *x;
    *x = *y;
    *y = t;
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