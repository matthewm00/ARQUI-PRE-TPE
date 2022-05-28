#include <commands.h>

#define YEAR 20			  // Debe escribir aca los digitos de su año (excepto los ultimos dos)
#define BYTES 32		  // Cantidad de bytes para el mem dump
#define FLOAT_PRECISION 8 // Precision para los puntos flotantes
//#define LAST_MEM_POSITION 536870911 //512MB mem que se le pasa en run.sh

static char *registerNames[] = {
	"R15: ", "R14: ", "R13: ", "R12: ", "R11: ", "R10: ", "R9: ",
	"R8: ", "RSI: ", "RDI: ", "RBP: ", "RDX: ", "RCX: ", "RBX: ",
	"RAX: ", "RIP: ", "CS: ", "FLAGS: ", "RSP: "};

// returns current date and time
void getCurrentDayTime(int argc, char **argv)
{
	if (argc != 1)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	printf("\nFecha de hoy: ");
	uint64_t result = syscall(SYS_RTC_ID, DAY_RTC_ID, 0, 0, 0);
	printf("%d", result);
	putChar('/');

	result = syscall(SYS_RTC_ID, MONTH_RTC_ID, 0, 0, 0);
	printf("%d", result);
	putChar('/');

	result = syscall(SYS_RTC_ID, YEAR_RTC_ID, 0, 0, 0);
	printf("%d", YEAR);
	printf("%d\n", result);

	printf("\nHora: ");
	result = syscall(SYS_RTC_ID, HOUR_RTC_ID, 0, 0, 0);
	printf("%d", result);
	putChar(':');

	result = syscall(SYS_RTC_ID, MINUTE_RTC_ID, 0, 0, 0);
	if (result < 10)
	{
		putChar('0');
	}
	printf("%d", result);
	putChar(':');

	result = syscall(SYS_RTC_ID, SECOND_RTC_ID, 0, 0, 0);
	if (result < 10)
	{
		putChar('0');
	}
	printf("%d\n\n", result);
}

void getInfoReg(int argc, char **argv)
{
	if (argc != 1)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	uint64_t *registers = (uint64_t *)syscall(SYS_INFOREG_ID, 0, 0, 0, 0);
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
	if (argc != 2)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	uint64_t memDir = strToHex(argv[1]);
	if (memDir == -1 /* || memDir + 32 > LAST_MEM_POSITION */)
	{
		printf("\nEl argumento ingresado es invalido. Use help.\n\n");
		return;
	}

	printf("\nDump de 32 bytes a partir de la direccion: %s\n\n", argv[1]);
	uint8_t buffer[BYTES];
	char print[10];
	syscall(SYS_PRINTMEM_ID, memDir, (uint64_t)buffer, BYTES, 0);
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
	if (argc != 1)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	// int x = 1;
	// int y = 0;
	// x = x / y;
	_divZeroExp();
}

// https://mudongliang.github.io/x86/html/file_module_x86_id_318.html
void opCode(int argc, char **argv)
{
	if (argc != 1)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	_opcodeExp();
}

void clear(int argc, char **argv)
{
	if (argc != 1)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	syscall(SYS_CLEAR_ID, 0, 0, 0, 0);
}
void exit(int argc, char **argv)
{
	if (argc != 1)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	printf("\nSaliendo del TPE\n\n");
	syscall(SYS_EXIT_ID, 0, 0, 0, 0);
}

void help(int argc, char **argv)
{
	if (argc != 1)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	printf("\nListado de comandos: \n");
	printf("\nhelp : Listado de comandos\n");
	printf("\nclear : Limpia la pantalla actual\n");
	printf("\ninforeg : Estado de todos los resgitros. Pulse ctrl + s para guardar los valores actuales de los registros\n");
	printf("\ndate : Fecha y hora actual\n");
	printf("\nprintmem : Volcado de memoria de 32 bytes a partir de la direccion de memoria en hexa ingresada como argumento\n");
	printf("\ndivzero : Excepcion division por cero\n");
	printf("\nopcode : Excepcion opcode invalido\n");
	printf("\ngames : 4 ventanas que cuentan con los juegos sudoku y ahorcado, un cronometro y un timer\n");

	printf("\nmem : Imprime el estado de la memoria\n");
	printf("\nsem : Imprime el estado de los semaforos\n");
	printf("\nps : Imprime el estado de los procesos\n");
	printf("\nnice : Cambia la prioridad de un proceso\n");
	printf("\nkill : Mata un proceso\n");
	printf("\nblock : Bloquea un proceso\n");
	printf("\nunblock : Desbloquea un proceso\n");
	printf("\ncat : Imprime el texto ingresado luego de ejecutar el comando\n");
	printf("\nloop : Imprime un saludo cada 3 segundos\n");
	printf("\npipe : Imprime el estado de los pipes\n");
	printf("\nfilter : Filtra las vocales del texto ingresadoluego de ejecutar el comando\n");
	printf("\nwc : Cantidad de lineas del texto ingresadoluego de ejecutar el comando\n");
	printf("\nphylo : Problema de filosofos comensales\n");

	printf("\nexit : Finaliza la ejecucion\n\n");
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

int checkArgCount(int argc, int argsAllowed)
{
	if (argc != argsAllowed)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return -1;
	}
	return 0;
}

void callMemStatus(int argc, char **argv)
{
	if (checkArgCount(argc, 1) == -1)
	{
		return;
	}
	memStatus();
}

void callSemStatus(int argc, char **argv)
{
	if (checkArgCount(argc, 1) == -1)
	{
		return;
	}
	semStatus();
}

void callProcessStatus(int argc, char **argv)
{
	if (checkArgCount(argc, 1) == -1)
	{
		return;
	}
	processStatus();
}

void callKillProcess(int argc, char **argv)
{
	if (checkArgCount(argc, 2) == -1)
	{
		return;
	}
	int pid = strToInt(argv[1], 0);
	killProcess(pid);
}

void callSetPriority(int argc, char **argv)
{
	if (checkArgCount(argc, 3) == -1)
	{
		return;
	}
	int pid = strToInt(argv[1], 0);
	int priority = strToInt(argv[2], 0);
	setPriority(pid, priority);
}

void callBlockProcess(int argc, char **argv)
{
	if (checkArgCount(argc, 2) == -1)
	{
		return;
	}
	int pid = strToInt(argv[1], 0);
	blockProcess(pid);
}

void callUnblockProcess(int argc, char **argv)
{
	if (checkArgCount(argc, 2) == -1)
	{
		return;
	}
	int pid = strToInt(argv[1], 0);
	unblockProcess(pid);
}

static int isVowel(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
	}
	return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void filter(int argc, char **argv)
{
	if (checkArgCount(argc, 1) == -1)
	{
		return;
	}
	char c;
	while ((c = getChar()) != EOF)
	{
		if (!isVowel(c))
		{
			putChar(c);
		}
	}
}
void cat(int argc, char **argv)
{
	if (checkArgCount(argc, 1) == -1)
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
	// while ((c = getChar()) != EOF)
	// {
	// 	putChar(c);
	// }
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

static void sleep(int sec)
{
	int wait = getSecondsElapsed() + sec;
	while (getSecondsElapsed() < wait)
	{
		;
	}
}

void loop(int argc, char **argv)
{
	if (checkArgCount(argc, 1) == -1)
	{
		return;
	}
	int pid = getProcessPID();
	while (1)
	{
		printf("Soy el proceso %d\n", pid, 4);
		sleep(4);
	}
}