// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <RTCID.h>
#include <commands.h>
#include <infoReg.h>
#include <libc.h>
#include <memoryTest.h>
#include <priorityTest.h>
#include <processTest.h>
#include <semaphoreTest.h>
#include <shell.h>
#include <stdint.h>
#include <userSyscalls.h>
#include <games.h>

#define YEAR 20  // digitos de su año (excepto los ultimos dos)
#define BYTES 32 // Cantidad de bytes para el mem dump
#define WAIT_SECONDS_LOOP 2

static char *registerNames[] = {
    "R15: ", "R14: ", "R13: ", "R12: ", "R11: ", "R10: ",
    "R9: ", "R8: ", "RSI: ", "RDI: ", "RBP: ", "RDX: ",
    "RCX: ", "RBX: ", "RAX: ", "RIP: ", "RSP: "};

void getCurrentDayTime(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  printf("\nFecha de hoy: ");
  uint64_t result = _syscall(SYS_RTC_ID, DAY_RTC_ID, 0, 0, 0, 0);
  printf("%d", result);
  putChar('/');

  result = _syscall(SYS_RTC_ID, MONTH_RTC_ID, 0, 0, 0, 0);
  printf("%d", result);
  putChar('/');

  result = _syscall(SYS_RTC_ID, YEAR_RTC_ID, 0, 0, 0, 0);
  printf("%d", YEAR);
  printf("%d\n", result);

  printf("\nHora: ");
  result = _syscall(SYS_RTC_ID, HOUR_RTC_ID, 0, 0, 0, 0);
  printf("%d", result);
  putChar(':');

  result = _syscall(SYS_RTC_ID, MINUTE_RTC_ID, 0, 0, 0, 0);
  if (result < 10)
  {
    putChar('0');
  }
  printf("%d", result);
  putChar(':');

  result = _syscall(SYS_RTC_ID, SECOND_RTC_ID, 0, 0, 0, 0);
  if (result < 10)
  {
    putChar('0');
  }
  printf("%d\n\n", result);
}

void getInfoReg(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  uint64_t *registers = (uint64_t *)_syscall(SYS_INFOREG_ID, 0, 0, 0, 0, 0);
  newLine();
  for (int i = 0; i < REGISTER_AMOUNT; i++)
  {
    printf("%s", registerNames[i]);
    printf("%x\n\n", registers[i]);
  }
  newLine();
}

void getMem(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 2) == -1)
  {
    return;
  }
  uint64_t memDir = strToHex(argv[1]);
  if (memDir == -1)
  {
    printf("\nEl argumento ingresado es invalido. Use /help.\n\n");
    return;
  }

  printf("\nDump de 32 bytes a partir de la direccion: %s\n\n", argv[1]);
  uint8_t buffer[BYTES];
  char print[10];
  (void)_syscall(SYS_PRINTMEM_ID, memDir, (uint64_t)buffer, BYTES, 0, 0);
  for (int i = 0; i < BYTES; i++)
  {
    if (i == 16)
    {
      newLine();
    }
    intToStr(buffer[i], print, 16);
    printf("%s ", print);
  }
  newLine();
  newLine();
}

void divZero(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  int x = 3;
  int y = 0;
  x = x / y;
}

// https://mudongliang.github.io/x86/html/file_module_x86_id_318.html
void opCode(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  _opcodeExp();
}

void clear(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  (void)_syscall(SYS_CLEAR_ID, 0, 0, 0, 0, 0);
}
void exit(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  printf("\nMuchas gracias por utilizar DOG-OS, esperamos su regreso.\n");
  printf("\nUsted cerro el TP, el mismo ya no funcionara.\n\n");
  (void)_syscall(SYS_EXIT_ID, 0, 0, 0, 0, 0);
}

void changeFtColour(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 2) == -1)
  {
    return;
  }
  int aux = strToInt(argv[1], 0);
  switch (aux)
  {
  case 1:
    setFTC(WHITE);
    break;
  case 2:
    setFTC(BLACK);
    break;
  case 3:
    setFTC(RED);
    break;
  case 4:
    setFTC(GREEN);
    break;
  case 5:
    setFTC(BLUE);
    break;
  default:
    printf("\nEl codigo de color que ingreso es invalido. Use /help.\n\n");
    break;
  }
}

void changeBgColour(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 2) == -1)
  {
    return;
  }
  int aux = strToInt(argv[1], 0);
  switch (aux)
  {
  case 1:
    setBGC(WHITE);
    break;
  case 2:
    setBGC(BLACK);
    break;
  case 3:
    setBGC(RED);
    break;
  case 4:
    setBGC(GREEN);
    break;
  case 5:
    setBGC(BLUE);
    break;
  default:
    printf("\nEl codigo de color que ingreso es invalido. Use /help.\n\n");
    break;
  }
}

void memStatusWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  memStatus();
}

void semStatusWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  semStatus();
}

void processStatusWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  processStatus();
}

void killProcessWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 2) == -1)
  {
    return;
  }
  int pid = strToInt(argv[1], 0);
  killProcess(pid);
}

void setPriorityWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 3) == -1)
  {
    return;
  }
  int pid = strToInt(argv[1], 0);
  int priority = strToInt(argv[2], 0);
  setPriority(pid, priority);
}

void blockProcessWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 2) == -1)
  {
    return;
  }
  int pid = strToInt(argv[1], 0);
  blockProcess(pid);
}

void unblockProcessWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 2) == -1)
  {
    return;
  }
  int pid = strToInt(argv[1], 0);
  unblockProcess(pid);
}

void testNoSyncWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  testNoSync();
}

void testSyncWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  testSync();
}

void testProcessesWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  testProcesses();
}
void filter(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  char c;
  char filterString[BUFFER_SIZE] = {0};
  int i = 0;
  while ((c = getChar()) != EOF)
  {
    putChar(c);
    if (!isVowel(c))
    {
      filterString[i++] = (char)c;
    }
  }
  printf("\n%s\n", filterString);
}

void testPriorityWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  testPriority();
}

void testMemoryWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  testMemory();
}

void cat(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  int c;
  char catString[BUFFER_SIZE] = {0};
  int i = 0;
  while ((c = getChar()) != EOF)
  {
    putChar(c);
    catString[i++] = (char)c;
  }
  printf("%s", catString);
}

void loop(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  int pid = getProcessPID();
  while (1)
  {
    printf("Soy el proceso %d\n", pid);
  }
}

void pipeStatusWrapper(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  pipeStatus();
}

void wc(int argc, char **argv)
{
  if (checkArgCount(argc, 1) == -1)
  {
    return;
  }
  char c;
  int lineCount = 1;
  while ((c = getChar()) != EOF)
  {
    putChar(c);
    if (c == '\n')
    {
      lineCount++;
    }
  }
  printf("\n\nCantidad de lineas: %d\n", lineCount);
}

int checkArgcWrapper(int argc, int argumentsPermitted)
{
  if (argc != argumentsPermitted)
  {
    printf("\nCantidad invalida de argumentos.\n\n");
    return -1;
  }
  return 0;
}

void games(int argc, char **argv)
{
  if (argc != 1)
  {
    printf("\nCantidad invalida de argumentos.\n\n");
    return;
  }
  clear(argc, argv);
  startGames();
  clear(argc, argv);
  printf("Volviendo a la shell...\n");
  return;
}