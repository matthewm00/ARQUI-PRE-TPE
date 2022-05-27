#include <shell.h>
#include <libc.h>
#include <commands.h>
#include <stdint.h>

void initialize()
{
    printf("\n  Utilice el comando help para obtener el manual de usuario.\n\n\n\n");
    shellExecute();
}

static int getCommandArgs(char *userInput, char *command, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
    int argc = 0;
    int i = 0;
    for (i = 0; userInput[i] != 0 && userInput[i] != ' '; i++)
    {
        command[i] = userInput[i];
    }
    command[i] = 0;
    int argIdx = 0;

    for (int j = 0; j < MAX_ARGUMENTS; j++)
    {
        argv[j][0] = 0;
    }

    while (userInput[i] != 0 && argc < MAX_ARGUMENTS)
    {
        i++;
        argIdx = 0;
        for (; userInput[i] != ' ' && userInput[i] != 0; i++, argIdx++)
        {
            argv[argc][argIdx] = userInput[i];
        }
        argv[argc][argIdx] = 0;
        argc++;
    }
    if (argc == MAX_ARGUMENTS && userInput[i] != 0)
        return -1;
    return argc;
}

typedef struct t_command
{
    void (*commandFn)(int, char **);
    char *name;
    char *description;
} t_command;

t_command inforegg = {&getInfoReg, "a", "aa"};

void shellExecute()
{
    char command[BUFFER_SIZE] = {0};
    char argv[MAX_ARGUMENTS][BUFFER_SIZE];
    char userInput[BUFFER_SIZE] = {0};
    int argc = 0;
    int foreground = FOREGROUND;

    while (1)
    {
        printf("$> ");

        userInput[0] = 0;

        scanf("%s", userInput);

        argc = getCommandArgs(userInput, command, argv);

        if (argc == -1)
        {
            printf("\nIngreso argumentos de mas.\nLa maxima cantidad de argumentos permitida es: %d.\n\n", MAX_ARGUMENTS);
        }
        else if (strcmp("help", command) == 0)
        {
            // newProcess((void (*)(int, char **))help, argc, (char **)argv, foreground);
            help(argc, (char **)argv);
        }
        else if (strcmp("inforeg", command) == 0)
        {
            newProcess(&getInfoReg, argc, (char **)argv, foreground, NULL);
            // getInfoReg(argc, (char **)argv);
            //(void (*)(int, char **))
        }
        else if (strcmp("clear", command) == 0)
        {
            clear(argc, (char **)argv);
        }
        else if (strcmp("exit", command) == 0)
        {
            exit(argc, (char **)argv);
        }
        else if (strcmp("opcode", command) == 0)
        {
            opCode(argc, (char **)argv);
        }
        else if (strcmp("date", command) == 0)
        {
            getCurrentDayTime(argc, (char **)argv);
        }
        else if (strcmp("printmem", command) == 0)
        {
            getMem(argc, (char **)argv);
        }
        else if (strcmp("divzero", command) == 0)
        {
            divZero(argc, (char **)argv);
        }
        else if (strcmp("games", command) == 0)
        {
            games(argc, (char **)argv);
        }
        else if (strcmp("mem", command) == 0)
        {
            callMemStatus(argc, (char **)argv);
        }
        else if (strcmp("sem", command) == 0)
        {
            callSemStatus(argc, (char **)argv);
        }
        else if (strcmp("ps", command) == 0)
        {
            callProcessStatus(argc, (char **)argv);
        }
        else if (strcmp("nice", command) == 0)
        {
            callSetPriority(argc, (char **)argv);
        }
        else if (strcmp("kill", command) == 0)
        {
            callKillProcess(argc, (char **)argv);
        }
        else if (strcmp("block", command) == 0)
        {
            callBlockProcess(argc, (char **)argv);
        }
        else if (strcmp("unblock", command) == 0)
        {
            callUnblockProcess(argc, (char **)argv);
        }
        else if (strcmp("cat", command) == 0)
        {
            cat(argc, (char **)argv);
        }
        else if (strcmp("loop", command) == 0)
        {
            loop(argc, (char **)argv);
        }
        else if (strcmp("pipe", command) == 0) // falta
        {
            // callPipeStatus(argc, (char **)argv);
        }
        else if (strcmp("filter", command) == 0)
        {
            filter(argc, (char **)argv);
        }
        else if (strcmp("wc", command) == 0)
        {
            wc(argc, (char **)argv);
        }
        else if (strcmp("phylo", command) == 0) // falta
        {
            // phylo(argc, (char **)argv);
        }
        else
        {
            printf("\nComando invalido: use help\n\n");
        }
    }
    return;
}

// callMemStatus "mem", "Imprime el estado de la memoria"
//     callSemStatus, "sem", "Imprime el estado de los semaforos"
//     callProcessStatus, "ps", "Imprime el estado de los procesos"
//     callSetPriority, "nice", "Cambia la prioridad de un proceso"
//     callKillProcess, "kill", "Mata un proceso"
//     callBlockProcess, "block", "Bloquea un proceso"
//     callUnblockProcess, "unblock", "Desbloquea un proceso"
//     cat, "cat", "Imprime el texto ingresado luego de   ejecutar el comando"
//     loop, "loop", "Imprime un saludo cada 3 segundos"
//     callPipeStatus, "pipe", "Imprime el estado de los pipes"
//     filter "filter"
//      "Filtra las vocales del texto ingresadoluego de ejecutar el comando"
//     wc, "wc"
//      "Cantidad de lineas del texto ingresadoluego de ejecutar el comando"
//     phylo, "phylo", "Problema de filosofos comensales"