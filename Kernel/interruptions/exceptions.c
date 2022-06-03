// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <colors.h>
#include <infoReg.h>
#include <prints.h>
#include <processManager.h>
#include <syscalls.h>
<<<<<<< HEAD
=======
#include <lib.h>
#include <processManager.h>
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a

#define ZERO_EXCEPTION_ID 0
#define INVOP_EXCEPTION_ID 6

<<<<<<< HEAD
static void zeroDivision();
static void invOpCode();
static void printRegs(uint64_t *rsp);

static char *registerNames[] = {
    "R15: ", "R14: ", "R13: ", "R12: ", "R11: ", "R10: ",
    "R9: ",  "R8: ",  "RSI: ", "RDI: ", "RBP: ", "RDX: ",
    "RCX: ", "RBX: ", "RAX: ", "RIP: ", "RSP: "};

void exceptionDispatcher(int exception, uint64_t rsp) {
  switch (exception) {
    case ZERO_EXCEPTION_ID:
      zeroDivision();
      break;
    case INVOP_EXCEPTION_ID:
      invOpCode();
      break;
  }
  printRegs((uint64_t *)rsp);
  killProcess(getProcessPID());
=======
#define REGISTER_AMOUNT 17

static char *registerNames[] = {
	"R15: ", "R14: ", "R13: ", "R12: ", "R11: ", "R10: ", "R9: ",
	"R8: ", "RSI: ", "RDI: ", "RBP: ", "RDX: ", "RCX: ", "RBX: ",
	"RAX: ", "RIP: ", "RSP: "};

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
	killProcess(getProcessPID());
	return;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static void zeroDivision() {
  printLine();
  sysWrite("Excecpion 0: No se puede dividir por cero.", 42, BLACK, RED, 0);
  printLine();
  printLine();
}

static void invOpCode() {
  printLine();
  sysWrite("Excecpion 6: Opcode invalido.", 29, BLACK, RED, 0);
  printLine();
  printLine();
}

static void printRegs(uint64_t *rsp) {
  for (int i = 0; i < REGISTER_AMOUNT; i++) {
    sysWrite(registerNames[i], strlen(registerNames[i]), BLACK, WHITE, 0);
    printIntHex(rsp[i]);
    printLine();
  }
  printLine();
}
