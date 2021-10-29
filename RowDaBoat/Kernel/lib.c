#include <lib.h>

static char buffer[64] = {'0'};

void *memset(void *destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char *dst = (char *)destination;

	while (length--)
		dst[length] = chr;

	return destination;
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

// BCD(Binary-coded decimal)
int BCDtoInt(uint64_t number)
{

	return ((number & 0xF0) >> 4) * 10 + (number & 0xF);
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