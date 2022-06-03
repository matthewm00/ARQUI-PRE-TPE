#include <syscalls.h>

static uint64_t registers[REGISTER_AMOUNT] = {0};

static int BCDtoInt(uint64_t number)
{

	return ((number & 0xF0) >> 4) * 10 + (number & 0xF);
}

// https://wiki.osdev.org/CMOS#Format_of_Bytes
uint8_t getCurrentTime(uint64_t rtcID)
{
	uint8_t x = _getRTCInfo(rtcID);
	// uint8_t result = ((x / 16) * 10) + (x & 0xf);
	// return result;
	return BCDtoInt(x);
}

void getMem(uint64_t direc, uint8_t *buffer, uint64_t bytes)
{
	for (uint8_t i = 0; i < bytes; i++)
	{
		buffer[i] = (uint8_t)_getMem(direc + i);
	}
}

void sys_write(char *str, uint8_t len, t_color bgColor, t_color ftColor)
{
	if (str == 0 || len <= 0 || bgColor < 0 || ftColor < 0)
		return;

	int outputFD = getCurrentProcessOutputFD();

	if (outputFD == 1)
	{
		for (int i = 0; str[i] != 0 && i < len; i++)
			printChar(str[i], ftColor, bgColor, 1);
	}
	else
	{
		pipeWrite(outputFD, str);
	}
}

uint64_t sys_read()
{
	int inputFD = getCurrentProcessInputFD();
	if (inputFD == 0)
	{
		if (currentProcessIsForeground() == 1)
		{
			return getCharFromBuffer();
		}
		else
			return -1;
	}
	return pipeRead(inputFD);
}

uint64_t *getRegisters()
{
	return registers;
}

void saveRegisters(uint64_t *rsp)
{
	for (int i = 0; i < REGISTER_AMOUNT; i++)
	{
		registers[i] = rsp[i];
	}
}

uint8_t getDecimalTime(uint64_t type)
{
	switch (type)
	{
	case 0:
	{
		return BCDtoInt(getHour());
	}
	case 1:
	{
		return BCDtoInt(getMins());
	}
	default:
	{
		return BCDtoInt(getSeconds());
	}
	}
}