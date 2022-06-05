// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <commands.h>
#include <libc.h>
#include <memoryTest.h>
#include <phylo.h>
#include <priorityTest.h>
#include <processTest.h>
#include <semaphoreTest.h>
#include <shell.h>
#include <stdint.h>
#include <userSyscalls.h>

#define USERLAND_INIT_PID 1

static int getCommands(char *userInput, char *argv[MAX_ARGUMENTS]);
static void initializeCommands();
static int getCommandIndex(char *command);
static void help(int argc, char **argv);
static void helpTest(int argc, char **argv);
static void helpShell(int argc, char **argv);
static void printHelpTable();
static void printHelpTestTable();

static int getPipeIndex(int argc, char **argv);
static void initializePipe(int pipeIndex, int argc, char **argv);
static int pipeDispatch(int pipeIndex, int argc, char **argv);
static int pipeRunCommand(int argc, char **argv, int fdin, int fdout, int foreground);

static int pipeId = 70;

static t_command commands[COMMAND_COUNT] = {
    {&help, "/help", "Listado de comandos."},
    {&clear, "/clear", "Limpia la pantalla actual."},
    {&getInfoReg, "/inforeg", "Estado de todos los resgitros, use Ctrl + R  para capturar el valor de los mismos."},
    {&exit, "/exit", "Finaliza la ejecucion."},
    {&opCode, "/opcode", "Excepcion opcode invalido."},
    {&getCurrentDayTime, "/date&time", "Fecha y hora actual."},
    {&getMem, "/printmem", "Volcado de memoria de 32 bytes a partir de   la direccion de memoria en hexa ingresada    como argumento."},
    {&divZero, "/divzero", "Excepcion division por cero."},
    {&games, "/games", "4 ventanas que cuentan con los juegos sudoku y ahorcado, un cronometro y un timer."},
    {&memStatusWrapper, "/mem", "Imprime el estado de la memoria."},
    {&semStatusWrapper, "/sem", "Imprime el estado de los semaforos."},
    {&processStatusWrapper, "/ps", "Imprime el estado de los procesos."},
    {&setPriorityWrapper, "/nice", "Cambia la prioridad de un proceso."},
    {&killProcessWrapper, "/kill", "Mata un proceso."},
    {&blockProcessWrapper, "/block", "Bloquea un proceso."},
    {&unblockProcessWrapper, "/unblock", "Desbloquea un proceso."},
    {&cat, "/cat", "Imprime el texto ingresado luego de ejecutar el comando."},
    {&loop, "/loop", "Imprime un saludo cada X segundos."},
    {&pipeStatusWrapper, "/pipe", "Imprime el estado de los pipes."},
    {&filter, "/filter", "Filtra las vocales del texto ingresado luego de ejecutar el comando."},
    {&wc, "/wc", "Cantidad de lineas del texto ingresado luego de ejecutar el comando."},
    {&phyloProblem, "/phylo", "Problema de los filosofos comensales."},
    {&testMemoryWrapper, "/memtest", "Testeo de memory manager."},
    {&testProcessesWrapper, "/proctest", "Testeo de process manager."},
    {&testPriorityWrapper, "/priotest", "Testeo de prioridad process manager."},
    {&testSyncWrapper, "/semtest", "Testeo de semaforos con uso."},
    {&testNoSyncWrapper, "/nosemtest", "Testeo de semaforos sin uso."},
    {&helpTest, "/helptest", "Instrucciones acerca de los tests."},
    {&helpShell, "/helpshell", "Instrucciones acerca de la shell."},
};

static t_shell shellData;

void initialize(int argc, char **argv)
{
  printf("\n                   Sistemas Operativos --- 1Q 2022\n\n");
  printf("\n  Utilice el comando /help para acceder al manual de usuario.\n\n\n");
  strcpy(shellData.userName, "User");
  initializeCommands();
  killProcess(USERLAND_INIT_PID);
  shellExecute();
}

void printUser()
{
  char peso[] = "$ ";
  char pico[] = " > ";
  int len = strlen(shellData.userName);
  len += 4;
  _syscall(SYS_WRITE_ID, (uint64_t)peso, 2, BLACK, GREEN, 0);
  _syscall(SYS_WRITE_ID, (uint64_t)shellData.userName, len + 1, BLACK, GREEN, 0);
  _syscall(SYS_WRITE_ID, (uint64_t)pico, 3, BLACK, GREEN, 0);
}

static void initializeCommands()
{
  for (int i = 0; i < COMMAND_COUNT; i++)
  {
    shellData.commands[i].commandFn = commands[i].commandFn;
    shellData.commands[i].name = commands[i].name;
    shellData.commands[i].description = commands[i].description;
  }
}

void shellExecute()
{
  char userInput[BUFFER_SIZE] = {0};
  int foreground;

  while (1)
  {
    printUser();
    int argc;
    int pipeIndex;
    userInput[0] = 0;
    char *argv[MAX_ARGUMENTS] = {0};
    foreground = FOREGROUND;

    scanf("%s", userInput);

    argc = getCommands(userInput, argv);

    if (argc == -1)
    {
      printf("\nError en el ingreso de argumentos\n\n");
    }

    pipeIndex = getPipeIndex(argc, argv);

    if (pipeIndex != -1)
    {
      initializePipe(pipeIndex, argc, argv);
      continue;
    }

    if (argv[argc - 1][0] == '&')
    {
      foreground = BACKGROUND;
      argc--;
    }

    int commandIdx = getCommandIndex(argv[0]);

    if (commandIdx >= 0)
    {
      createProcess(
          (void (*)(int, char **))shellData.commands[commandIdx].commandFn,
          argc, (char **)argv, foreground, NULL);
    }
    else
    {
      printf("\nComando invalido: use /help\n\n");
    }
  }
}

static int getCommands(char *userInput, char **argv)
{
  int argc = 0;

  if (*userInput != ' ' && *userInput != '\0')
  {
    argv[argc++] = userInput;
  }

  while (*userInput != 0)
  {
    if (*userInput == ' ')
    {
      *userInput = 0;
      if ((*(userInput + 1) != ' ') && (*(userInput + 1) != 0))
      {
        if (argc >= MAX_ARGUMENTS)
        {
          return -1;
        }
        argv[argc++] = userInput + 1;
      }
    }
    userInput++;
  }
  return argc;
}

static int getPipeIndex(int argc, char **argv)
{
  for (int i = 0; i < argc; i++)
  {
    if (strcmp(argv[i], "|") == 0)
    {
      return i;
    }
  }
  return -1;
}

static void initializePipe(int pipeIndex, int argc, char **argv)
{
  if (pipeIndex == 0 || pipeIndex == argc - 1)
  {
    printf("\nPipe (|) debe ser usado entre dos comandos.\n\n");
    return;
  }
  int pipe = pipeDispatch(pipeIndex, argc, argv);
  if (pipe == -1)
  {
    printf("\nComando invalido. Use /help.\n\n");
    return;
  }
}

static int pipeDispatch(int pipeIndex, int argc, char **argv)
{
  char *currentArgv[MAX_ARGUMENTS];
  int currentArgc = 0;
  int pids[2];

  int pipe = pipeOpen(pipeId++);
  if (pipe == -1)
  {
    printf("\nError creando pipe.\n");
    return -1;
  }

  for (int i = pipeIndex + 1, j = 0; i < argc; i++, j++)
  {
    currentArgv[j] = argv[i];
    currentArgc++;
  }

  pids[0] = pipeRunCommand(currentArgc, currentArgv, pipe, 1, BACKGROUND);
  if (pids[0] == -1)
  {
    pipeClose(pipe);
    return -1;
  }

  currentArgc = 0;
  for (int i = 0; i < pipeIndex; i++)
  {
    currentArgv[i] = argv[i];
    currentArgc++;
  }

  pids[1] = pipeRunCommand(currentArgc, currentArgv, 0, pipe, FOREGROUND);
  if (pids[1] == -1)
  {
    pipeClose(pipe);
    return -1;
  }

  int endOfFile = EOF;
  pipeWrite(pipe, (char *)&endOfFile);

  wait(pids[0]);

  pipeClose(pipe);
  putChar('\n');
  return 1;
}

static int pipeRunCommand(int argc, char **argv, int fdin, int fdout, int foreground)
{
  int fd[2];
  int commandIdx = getCommandIndex(argv[0]);
  if (commandIdx == -1)
  {
    return -1;
  }

  fd[0] = fdin;
  fd[1] = fdout;

  return createProcess(shellData.commands[commandIdx].commandFn, argc, argv,
                       foreground, fd);
}

static void printHelpTable()
{
  printf("\nLista de comandos\n");

  for (int i = 0; i < TEST_COMMAND_START; i++)
  {
    printRow(shellData.commands[i].name, shellData.commands[i].description, 1);
  }
  printRow("/helptest", "Obtener informacion de los tests.", 1);
  printRow("/helpshell", "Obtener informacion de la shell.", 1);
  printf("\n");
}

static void printHelpTestTable()
{
  printf("\nLista de tests\n");
  int count = 0;
  for (int i = TEST_COMMAND_START; count < TEST_COMMAND_COUNT; i++)
  {
    printRow(shellData.commands[i].name, shellData.commands[i].description, 1);
    count++;
  }
}

static int getCommandIndex(char *command)
{
  for (int i = 0; i < COMMAND_COUNT; i++)
  {
    if ((strcmp(shellData.commands[i].name, command)) == 0)
    {
      return i;
    }
  }
  return -1;
}

static void help(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }

  printHelpTable();
}

static void helpShell(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  printf("\nInstructivo para manejo de la shell\n");
  printf("Ejemplos de uso:  /c1 | /c2   /c1 &   /c1 arg1\n");
  printf("Ctrl + C para terminar el proceso actual.\n");
  printf("Ctrl + S para capturar el valor de los registros\n");
  printf("Ctrl + D para obtener los resultados de /cat , /wc y /filter\n");
}

static void helpTest(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  printHelpTestTable();
}