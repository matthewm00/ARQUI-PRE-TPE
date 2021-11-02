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
	saveRegistersASM();
	printRegisters(registers);
}

void zero_division()
{
	write((uint64_t *)"Exception thrown: 0\n", 20, BLACK, RED);
	write((uint64_t *)"Type: Division by zero\n", 23, BLACK, RED);

	ncPrintString(0x000000, "Exception thrown: 0\n");
	ncPrintString(0x000000, "Type: Division by zero\n");
}
void invalid_OpCode()
{
	write((uint64_t *)"Exception thrown: 6\n", 20, BLACK, RED);
	write((uint64_t *)"Type: Invalid Operation Code\n", 29, BLACK, RED);

	ncPrintString(0x000000, "Exception thrown: 6\n");
	ncPrintString(0x000000, "Type: Invalid Operation Code\n");
}
void printRegisters(uint64_t *registers)
{
	saveRegistersASM();
	uint64_t *registersValue = getRegisters();
	// 17 o 19 registros?
	for (int i = 0; i < 17; i++)
	{
		write((uint64_t *)registerNames[i], 5, WHITE, BLACK);
		printIntHex(registersValue[i]);
	}
}