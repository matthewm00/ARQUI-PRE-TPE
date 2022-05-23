#include <syscalls.h>

#define REGISTER_AMOUNT 19

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
	for (int i = 0; str[i] != 0 && i < len; i++)
		printChar(str[i], ftColor, bgColor, 1);
}

uint64_t sys_read()
{
	return getCharFromBuffer();
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

int mallocWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
	return (uint64_t)malloc((size_t)rsi);
}

int freeWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
	free((void *)rsi);
	return 0;
}

int memDumpWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
	memoryDump();
	return 0;
}

int newProcessWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
	return newProcess((void (*)(int, char **))rsi, (int)rdx, (char **)rcx, (int)r8);
}

int killProcessWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
	return killProcess(rsi);
}

int getProcessPIDWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
	return getProcessPID();
}

int processStatusWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
	printProcessStatus();
	return 0;
}

int blockProcessWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
	return blockProcess(rsi);
}

int setStateWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
	return setState(rsi, (t_state)rdx);
}

int yieldWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
	yield();
	return 0;
}

int setPriorityWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
	setPriority(rsi, (int)rdx);
	return 0;
}

int readyProcessWrapper(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8)
{
	return readyProcess(rsi);
}