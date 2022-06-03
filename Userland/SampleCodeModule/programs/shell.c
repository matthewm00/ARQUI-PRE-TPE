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

static int getCommandArgs(char *userInput, char *argv[MAX_ARGUMENTS]);
static void shellExecute();
static void initializeCommands();
static int getCommandIdx(char *command);
static void help(int argc, char **argv);
static void helpTest(int argc, char **argv);
static void helpShell(int argc, char **argv);
static void printHelpTable();
static void printHelpTestTable();

static int findPipe(int argc, char **argv);
static void initializePipe(int pipeIndex, int argc, char **argv);
static int handlePipe(int pipeIndex, int argc, char **argv);
static int runPipeCmd(int argc, char **argv, int fdin, int fdout, int foreground);

static int pipeId = 70;

static t_command commands[COMMAND_COUNT] = {
    {&help, "/help", "Listado de comandos"},
    {&clear, "/clear", "Limpia la pantalla actual"},
    {&getInfoReg, "/inforeg",
     "Estado de todos los resgitros, use    Ctrl + R para capturar los mismos"},
    {&exit, "/exit", "Finaliza la ejecucion"},
    {&opCode, "/opcode", "Excepcion opcode invalido"},
    {&getCurrentDayTime, "/date&time", "Fecha y hora actual"},
    {&getMem, "/printmem",
     "Volcado de memoria de 32 bytes a      partir de direccion de memoria en "
     "hexa"
     "ingresada como argumento."},
    {&divZero, "/divzero", "Excepcion division por cero"},
    {&games, "/games", "4 ventanas que cuentan con los juegos sudoku y ahorcado, un cronometro y un timer"},
    {&memStatusWrapper, "/mem", "Imprime el estado de la memoria"},
    {&semStatusWrapper, "/sem", "Imprime el estado de los semaforos"},
    {&processStatusWrapper, "/ps", "Imprime el estado de los procesos"},
    {&setPriorityWrapper, "/nice", "Cambia la prioridad de un proceso"},
    {&killProcessWrapper, "/kill", "Mata un proceso"},
    {&blockProcessWrapper, "/block", "Bloquea un proceso"},
    {&unblockProcessWrapper, "/unblock", "Desbloquea un proceso"},
    {&cat, "/cat", "Imprime el texto ingresado luego de   ejecutar el comando"},
    {&loop, "/loop", "Imprime un saludo cada 3 segundos"},
    {&pipeStatusWrapper, "/pipe", "Imprime el estado de los pipes"},
    {&filter, "/filter",
     "Filtra las vocales del texto ingresadoluego de ejecutar el comando"},
    {&wc, "/wc",
     "Cantidad de lineas del texto ingresadoluego de ejecutar el comando"},
    {&philoProblem, "/phylo", "Problema de filosofos comensales"},

    // limite
    {&testMemoryWrapper, "/memtest", "Testeo de memory manager"},
    {&testProcessesWrapper, "/proctest", "Testeo de process manager"},
    {&testPriorityWrapper, "/priotest", "Testeo de prioridad process manager"},
    {&testSyncWrapper, "/semtest", "Testeo de semaforos con uso"},
    {&testNoSyncWrapper, "/nosemtest", "Testeo de semaforos sin uso"},
    {&helpTest, "/helptest", "Instrucciones acerca de los tests"},
    {&helpShell, "/helpshell", "Instrucciones acerca de la shell"},
};

static t_shell shellData;

void startShell(int argc, char **argv)
{
  printf("\n         Sistemas Operativos --- 1Q 2022\n\n");
  printf("\n  Utilice el comando /help para obtener un manual de "
         "usuario.\n\n\n\n");
  strcpy(shellData.userName, "User");
  initializeCommands();
  killProcess(USERLAND_INIT_PID);
  shellExecute();
}

void printUser()
{
  int len = strlen(shellData.userName);
  len += 4;
  printf("$ ");
  sendUserData(shellData.userName, len);
  printf(" > ");
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

static void shellExecute()
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

    argc = getCommandArgs(userInput, argv);

    if (argc == -1)
    {
      printf(
          "\nIngreso argumentos de mas.\nLa maxima cantidad de argumentos "
          "permitida es: %d.\n\n",
          MAX_ARGUMENTS);
    }

    pipeIndex = findPipe(argc, argv);

    if (pipeIndex >= 0)
    {
      initializePipe(pipeIndex, argc, argv);
      continue;
    }

    if (argv[argc - 1][0] == '&')
    {
      foreground = BACKGROUND;
      argc--;
    }

    int commandIdx = getCommandIdx(argv[0]);

    if (commandIdx >= 0)
    {
      newProcess(
          (void (*)(int, char **))shellData.commands[commandIdx].commandFn,
          argc, (char **)argv, foreground, NULL);
    }
    else
    {
      printf("\nComando invalido: use /help\n\n");
    }
  }
}

static int getCommandArgs(char *userInput, char **argv)
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

static int findPipe(int argc, char **argv)
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
  int pipe = handlePipe(pipeIndex, argc, argv);
  if (pipe == -1)
  {
    printf("\nUno de los comandos es invalido. Use /help.\n\n");
    return;
  }
}

static int handlePipe(int pipeIndex, int argc, char **argv)
{
  char *currentArgv[MAX_ARGUMENTS];
  int currentArgc = 0;
  int pids[2];

  int pipe = pipeOpen(pipeId++);
  if (pipe == -1)
  {
    printf("\nError creando pipe.\n");
    return -2;
  }

  for (int i = pipeIndex + 1, j = 0; i < argc; i++, j++)
  {
    currentArgv[j] = argv[i];
    currentArgc++;
  }

  pids[0] = runPipeCmd(currentArgc, currentArgv, pipe, 1, BACKGROUND);
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

  pids[1] = runPipeCmd(currentArgc, currentArgv, 0, pipe, FOREGROUND);
  if (pids[1] == -1)
  {
    pipeClose(pipe);
    return -1;
  }

  int endOfFile = EOF;
  pipeWrite(pipe, (char *)&endOfFile);

  pipeClose(pipe);
  putChar('\n');
  return 1;
}

static int runPipeCmd(int argc, char **argv, int fdin, int fdout, int foreground)
{
  int fd[2];
  int commandIdx = getCommandIdx(argv[0]);
  if (commandIdx == -1)
  {
    return -1;
  }

  fd[0] = fdin;
  fd[1] = fdout;

  return newProcess(shellData.commands[commandIdx].commandFn, argc, argv,
                    foreground, fd);
}

static void printHelpTable()
{
  printf("\n\n\nLista de comandos\n");

  for (int i = 0; i < TEST_COMMAND_START; i++)
  {
    printRow(shellData.commands[i].name, shellData.commands[i].description, 1);
  }
}

static void printHelpTestTable()
{
  printf("\n\n\nLista de tests\n");
  for (int i = TEST_COMMAND_START; i < COMMAND_COUNT - 2; i++)
  {
    printRow(shellData.commands[i].name, shellData.commands[i].description, 1);
  }
}

static int getCommandIdx(char *command)
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
  printf("Instructivo para manejo de la shell");
  printf("Use Ctrl + C para terminar el proceso actual.\n");
  printf("Use Ctrl + S para capturar el valor de los registros\n");
  printf(
      "Use Ctrl + D para obtener resultados en comandos como \n/wc o "
      "/filter\n");
  printf("\n");
}

static void helpTest(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  printHelpTestTable();
}