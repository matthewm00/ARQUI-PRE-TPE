#include <syscalls.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <infoReg.h>

static uint64_t registers[16] = {0};

// https://wiki.osdev.org/CMOS#Format_of_Bytes
uint8_t getCurrentTime(uint64_t rtcID)
{
	uint8_t x = _getRTCInfo(rtcID);
	uint8_t result = ((x / 16) * 10) + (x & 0xf);
	return result;
}

void getMem(uint64_t direc, uint8_t *buffer, uint64_t bytes)
{
	for (uint8_t i = 0; i < bytes; i++)
	{
		buffer[i] = (uint8_t)_getMem(direc + i);
	}
}

void sys_write(char *str, uint8_t len, t_color bgColor, t_color ftColor, int usrLen)
{
	if (str == 0 || len <= 0 || bgColor < 0 || ftColor < 0)
		return;
	if (usrLen > 1)
	{
		setUsernameLen(len);
	}
	for (int i = 0; str[i] != 0 && i < len; i++)
		printChar(str[i], ftColor, bgColor, 1);
}

uint64_t sys_read()
{
	return getChar();
}

uint64_t *getRegisters()
{
	_saveRegisters();
	return registers;
}

void saveRegisters(uint64_t *rsp)
{
	for (int i = 0; i < 16; i++)
	{
		registers[i] = rsp[i];
	}
}
