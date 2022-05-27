#include <shell.h>
#include <libc.h>
#include <commands.h>
#include <stdint.h>

void initialize()
{
    printf("\n  Utilice el comando help para obtener el manual de usuario.\n\n\n\n");
    shellExecute();
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

typedef struct t_command
{
    void (*commandFn)(int, char **);
    char *name;
    char *description;
} t_command;

t_command inforegg = {&getInfoReg, "a", "aa"};

void shellExecute()
{
    char argv[MAX_ARGUMENTS][BUFFER_SIZE];
    char userInput[BUFFER_SIZE] = {0};
    int argc = 0;
    int foreground = FOREGROUND;

    while (1)
    {
        printf("$> ");

        userInput[0] = 0;

        scanf("%s", userInput);

        argc = getCommandArgs(userInput, argv);

        if (argc == -1)
        {
            printf("\nIngreso argumentos de mas.\nLa maxima cantidad de argumentos permitida es: %d.\n\n", MAX_ARGUMENTS);
            continue;
        }

        int pipeIdx = getPipeIdx(argc, argv);
        if (pipeIdx >= 0)
        {
            initPipe(pipeIdx, argc, argv);
            continue;
        }

        if (argv[argc - 1][0] == '&')
        {
            foreground = BACKGROUND;
            argc--;
        }

        if (strcmp("help", argv[0]) == 0)
        {
            // newProcess((void (*)(int, char **))help, argc, (char **)argv, foreground);
            help(argc, (char **)argv);
        }
        else if (strcmp("inforeg", argv[0]) == 0)
        {
            newProcess(&getInfoReg, argc, (char **)argv, foreground, NULL);
            // getInfoReg(argc, (char **)argv);
            //(void (*)(int, char **))
        }
        else if (strcmp("clear", argv[0]) == 0)
        {
            clear(argc, (char **)argv);
        }
        else if (strcmp("exit", argv[0]) == 0)
        {
            exit(argc, (char **)argv);
        }
        else if (strcmp("opcode", argv[0]) == 0)
        {
            opCode(argc, (char **)argv);
        }
        else if (strcmp("date", argv[0]) == 0)
        {
            getCurrentDayTime(argc, (char **)argv);
        }
        else if (strcmp("printmem", argv[0]) == 0)
        {
            getMem(argc, (char **)argv);
        }
        else if (strcmp("divzero", argv[0]) == 0)
        {
            divZero(argc, (char **)argv);
        }
        else if (strcmp("games", argv[0]) == 0)
        {
            games(argc, (char **)argv);
        }
        else if (strcmp("mem", argv[0]) == 0)
        {
            callMemStatus(argc, (char **)argv);
        }
        else if (strcmp("sem", argv[0]) == 0)
        {
            callSemStatus(argc, (char **)argv);
        }
        else if (strcmp("ps", argv[0]) == 0)
        {
            callProcessStatus(argc, (char **)argv);
        }
        else if (strcmp("nice", argv[0]) == 0)
        {
            callSetPriority(argc, (char **)argv);
        }
        else if (strcmp("kill", argv[0]) == 0)
        {
            callKillProcess(argc, (char **)argv);
        }
        else if (strcmp("block", argv[0]) == 0)
        {
            callBlockProcess(argc, (char **)argv);
        }
        else if (strcmp("unblock", argv[0]) == 0)
        {
            callUnblockProcess(argc, (char **)argv);
        }
        else if (strcmp("cat", argv[0]) == 0)
        {
            cat(argc, (char **)argv);
        }
        else if (strcmp("loop", argv[0]) == 0)
        {
            loop(argc, (char **)argv);
        }
        else if (strcmp("pipe", argv[0]) == 0) // falta
        {
            // callPipeStatus(argc, (char **)argv);
        }
        else if (strcmp("filter", argv[0]) == 0)
        {
            filter(argc, (char **)argv);
        }
        else if (strcmp("wc", argv[0]) == 0)
        {
            wc(argc, (char **)argv);
        }
        else if (strcmp("phylo", argv[0]) == 0) // falta
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