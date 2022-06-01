#include <shell.h>

void initialize(int argc, char **argv)
{
    printf("\n  Utilice el comando help para obtener el manual de usuario.\n\n\n\n");
    killProcess(USERLAND_INIT_PID);
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
static int getPipeIdx(int argc, char **argv)
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

static void initPipe(int index, int argc, char **argv)
{
    if (index == 0 || index == argc - 1)
    {
        return;
    }
    int pipe = handlePipe(index, argc, argv);
    if (pipe == -1)
    {
        printf("\nComando invalido\n\n");
        return;
    }
}

static int handlePipe(int pipeIdx, int argc, char **argv)
{
    char *currentArgv[MAX_ARGUMENTS];
    int currentArgc = 0;
    int pids[2];

    int pipe = pipeOpen(pipeId++);
    if (pipe == -1)
    {
        printf("\nError creating pipe.\n");
        return -2;
    }

    for (int i = pipeIdx + 1, j = 0; i < argc; i++, j++)
    {
        currentArgv[j] = argv[i];
        currentArgc++;
    }

    pids[0] = runPipeCommand(currentArgc, currentArgv, pipe, 1, BACKGROUND);
    if (pids[0] == -1)
    {
        pipeClose(pipe);
        return -1;
    }

    currentArgc = 0;
    for (int i = 0; i < pipeIdx; i++)
    {
        currentArgv[i] = argv[i];
        currentArgc++;
    }

    pids[1] = runPipeCommand(currentArgc, currentArgv, 0, pipe, FOREGROUND);
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

static int runPipeCommand(int argc, char **argv, int fdin, int fdout, int foreground)
{
    int fd[2];
    fd[0] = fdin;
    fd[1] = fdout;
    return runCommand(argc, argv, foreground, fd);
}

void shellExecute()
{
    char *argv[MAX_ARGUMENTS] = {0};
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

        runCommand(argc, (char **)argv, foreground, NULL);
    }
    return;
}

static int runCommand(int argc, char **argv, int foreground, int *fd)
{
    if (strcmp("help", argv[0]) == 0)
    {
        help(argc, argv);
        // return newProcess(&help, argc, argv, foreground, fd);
    }
    else if (strcmp("inforeg", argv[0]) == 0)
    {
        // getInfoReg(argc, argv);
        return newProcess(&getInfoReg, argc, argv, foreground, fd);
    }
    else if (strcmp("clear", argv[0]) == 0)
    {
        clear(argc, argv);
        // return newProcess(&clear, argc, argv, foreground, fd);
    }
    else if (strcmp("exit", argv[0]) == 0)
    {
        exit(argc, argv);
        // return newProcess(&exit, argc, argv, foreground, fd);
    }
    else if (strcmp("opcode", argv[0]) == 0)
    {
        opCode(argc, argv);
        // return newProcess(&opCode, argc, argv, foreground, fd);
    }
    else if (strcmp("date", argv[0]) == 0)
    {
        getCurrentDayTime(argc, argv);
        // return newProcess(&getCurrentDayTime, argc, argv, foreground, fd);
    }
    else if (strcmp("printmem", argv[0]) == 0)
    {
        getMem(argc, argv);
        // return newProcess(&getMem, argc, argv, foreground, fd);
    }
    else if (strcmp("divzero", argv[0]) == 0)
    {
        divZero(argc, argv);
        // return newProcess(&divZero, argc, argv, foreground, fd);
    }
    else if (strcmp("games", argv[0]) == 0)
    {
        games(argc, argv);
        // return newProcess(&games, argc, argv, foreground, fd);
    }
    else if (strcmp("mem", argv[0]) == 0)
    {
        callMemStatus(argc, argv);
        // return newProcess(&callMemStatus, argc, argv, foreground, fd);
    }
    else if (strcmp("sem", argv[0]) == 0)
    {
        callSemStatus(argc, argv);
        // return newProcess(&callSemStatus, argc, argv, foreground, fd);
    }
    else if (strcmp("ps", argv[0]) == 0)
    {
        callProcessStatus(argc, argv);
        // return newProcess(&callProcessStatus, argc, argv, foreground, fd);
    }
    else if (strcmp("nice", argv[0]) == 0)
    {
        callSetPriority(argc, argv);
        // return newProcess(&callSetPriority, argc, argv, foreground, fd);
    }
    else if (strcmp("kill", argv[0]) == 0)
    {
        callKillProcess(argc, argv);
        // return newProcess(&callKillProcess, argc, argv, foreground, fd);
    }
    else if (strcmp("block", argv[0]) == 0)
    {
        callBlockProcess(argc, argv);
        // return newProcess(&callBlockProcess, argc, argv, foreground, fd);
    }
    else if (strcmp("unblock", argv[0]) == 0)
    {
        callUnblockProcess(argc, argv);
        // return newProcess(&callUnblockProcess, argc, argv, foreground, fd);
    }
    else if (strcmp("cat", argv[0]) == 0)
    {
        cat(argc, argv);
        // return newProcess(&cat, argc, argv, foreground, fd);
    }
    else if (strcmp("loop", argv[0]) == 0)
    {
        loop(argc, argv);
        // return newProcess(&loop, argc, argv, foreground, fd);
    }
    else if (strcmp("pipe", argv[0]) == 0) // falta
    {
        // callPipeStatus(argc, argv);
        // return newProcess(&callPipeStatus, argc, argv, foreground, fd);
    }
    else if (strcmp("filter", argv[0]) == 0)
    {
        filter(argc, argv);
        // return newProcess(&filter, argc, argv, foreground, fd);
    }
    else if (strcmp("wc", argv[0]) == 0)
    {
        wc(argc, argv);
        // return newProcess(&wc, argc, argv, foreground, fd);
    }
    else if (strcmp("phylo", argv[0]) == 0) // falta
    {
        // phylo(argc, argv);
        // return newProcess(&phylo, argc, argv, foreground, fd);
    }
    else if (strcmp("test_mm", argv[0]) == 0) // falta
    {
        test_mm(argc, argv);
        // return newProcess(&test_mm, argc, argv, foreground, fd);
    }
    else if (strcmp("test_priority", argv[0]) == 0) // falta
    {
        test_priority(argc, argv);
        // return newProcess(&test_priority, argc, argv, foreground, fd);
    }
    else if (strcmp("test_processes", argv[0]) == 0) // falta
    {
        test_processes(argc, argv);
        // return newProcess(&test_processes, argc, argv, foreground, fd);
    }
    else if (strcmp("test_sync", argv[0]) == 0) // falta
    {
        test_sync(argc, argv);
        // return newProcess(&test_sync, argc, argv, foreground, fd);
    }
    else
    {
        printf("\nComando invalido: use help\n\n");
    }
    return 0;
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