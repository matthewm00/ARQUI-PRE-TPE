#include <exceptionDispatcher.h>

void exceptionDispatcher(uint64_t exception, uint64_t *registers)
{
	switch (exception)
	{
	case ZERO_EXCEPTION_ID:
		zero_division();
		break;
	case INVALID_OPCODE_EXCEPTION_ID:
		invalid_OpCode();
		break;
	}
	// print registers
	printRegisters(*registers);
}

void zero_division()
{
}
void invalid_OpCode()
{
}
void printRegisters(uint64_t *registers)
{
}