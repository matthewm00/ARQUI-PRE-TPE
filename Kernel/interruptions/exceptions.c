#include <prints.h>
#include <colors.h>
#include <syscalls.h>
#include <lib.h>

#define ZERO_EXCEPTION_ID 0
#define INVOP_EXCEPTION_ID 6

#define REGISTER_AMOUNT 19

static char *registerNames[] = {
	"R15: ", "R14: ", "R13: ", "R12: ", "R11: ", "R10: ", "R9: ",
	"R8: ", "RSI: ", "RDI: ", "RBP: ", "RDX: ", "RCX: ", "RBX: ",
	"RAX: ", "RIP: ", "CS: ", "FLAGS: ", "RSP: "};

static void zero_division();
static void inv_op_code();
static void printRegs(uint64_t *rsp);

void exceptionDispatcher(int exception, uint64_t rsp)
{
	switch (exception)
	{
	case ZERO_EXCEPTION_ID:
		zero_division();
		break;
	case INVOP_EXCEPTION_ID:
		inv_op_code();
		break;
	}
	printRegs((uint64_t *)rsp);
	return;
}

static void zero_division()
{
	printLine();
	sys_write("Exception 0: division by zero is undefined\n", 43, BLACK, RED);
	printLine();
	printLine();
}

static void inv_op_code()
{
	printLine();
	sys_write("Exception 6: invalid opcode\n", 28, BLACK, RED);
	printLine();
	printLine();
}

static int strlen(char *str)
{
	int size = 0;
	for (int i = 0; str[i] != 0; i++)
	{
		size++;
	}
	return size;
}

static void printRegs(uint64_t *rsp)
{
	for (int i = 0; i < REGISTER_AMOUNT; i++)
	{
		sys_write(registerNames[i], strlen(registerNames[i]), BLACK, WHITE);
		printIntHex(rsp[i]);
		printLine();
		printLine();
	}
}
