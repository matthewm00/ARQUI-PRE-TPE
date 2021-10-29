#include <commands.h>
#include <stdint.h>
#include <libC.h>
#include <syscall.h>
#include <RTCID.h>
#include <infoReg.h>

#define YEAR 20			  // Debe escribir aca los digitos de su año (excepto los ultimos dos)
#define BYTES 32		  // Cantidad de bytes para el mem dump
#define FLOAT_PRECISION 8 // Precision para los puntos flotantes
//#define LAST_MEM_POSITION 536870911 //512MB mem que se le pasa en run.sh

// returns current date and time
void getCurrentDayTime(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	printf("\nFecha de hoy: ");
	uint64_t result = syscall(RTC_TIME, DAY_RTC_ID, 0, 0, 0, 0);
	printf("%d", result);
	putChar('/');

	result = syscall(RTC_TIME, MONTH_RTC_ID, 0, 0, 0, 0);
	printf("%d", result);
	putChar('/');

	result = syscall(RTC_TIME, YEAR_RTC_ID, 0, 0, 0, 0);
	printf("%d", YEAR);
	printf("%d\n", result);

	printf("\nHora: ");
	result = syscall(RTC_TIME, HOUR_RTC_ID, 0, 0, 0, 0);
	printf("%d", result);
	putChar(':');

	result = syscall(RTC_TIME, MINUTE_RTC_ID, 0, 0, 0, 0);
	if (result < 10)
	{
		putChar('0');
	}
	printf("%d", result);
	putChar(':');

	result = syscall(RTC_TIME, SECOND_RTC_ID, 0, 0, 0, 0);
	if (result < 10)
	{
		putChar('0');
	}
	printf("%d\n\n", result);
}

void getInfoReg(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	uint64_t *registers = (uint64_t *)syscall(INFOREG, 0, 0, 0, 0, 0);
	putChar('\n');
	for (int i = 0; i < REGISTER_AMOUNT; i++)
	{
		printf("%s", registerNames[i]);
		printf("%x\n\n", registers[i]);
	}
	putChar('\n');
}

void getMem(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 1)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	uint64_t memDir = strToHex(argv[0]);
	if (memDir == -1 /* || memDir + 32 > LAST_MEM_POSITION */)
	{
		printf("\nEl argumento ingresado es invalido. Use /help.\n\n");
		return;
	}

	printf("\nDump de 32 bytes a partir de la direccion: %s\n\n", argv[0]);
	uint8_t buffer[BYTES];
	char print[10];
	syscall(PRINTMEM, memDir, (uint64_t)buffer, BYTES, 0, 0);
	for (int i = 0; i < BYTES; i++)
	{
		if (i == 16)
		{
			putChar('\n');
		}
		intToStr(buffer[i], print, 16);
		printf("%s ", print);
	}
	putChar('\n');
	putChar('\n');
}

// Con estas funciones se activan las excepciones correspondientes
// En kernel hay funciones que tratan estas excepciones y deben
// imprimir los registros

void divZero(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	int x = 3;
	int y = 0;
	x = x / y;
}

// https://mudongliang.github.io/x86/html/file_module_x86_id_318.html
void opCode(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	opcodeExp();
}

void clear(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	syscall(CLEAR, 0, 0, 0, 0, 0);
}
void exit(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	printf("\nSaliendo del TP\n");
	syscall(EXIT, 0, 0, 0, 0, 0);
}

void help(int argc, char argv[MAX_ARGUMENTS][BUFFER_SIZE])
{
	if (argc != 0)
	{
		printf("\nCantidad invalida de argumentos.\n\n");
		return;
	}
	printf("\nUse ctrl + tab para cambiar de pantalla.\n");
	printf("\nTabla de colores: \n");
	printf("\nBLANCO | NEGRO | ROJO | VERDE | AZUL\n");
	printf("  1    |   2   |  3   |   4   |  5\n");

	printf("\nLista de comandos: \n");

	printf("\n/help : Listado de comandos\n");

	printf("\n/clear : Limpia la pantalla actual\n");

	printf("\n/inforeg : Estado de todos los resgitros.\nUse ctrl + r para capturar los mismos.\n");

	printf("\n/date&time : Fecha y hora actual\n");
	printf("\n/printmem : Volcado de memoria de 32 bytes a partir de\ndireccion de memoria en hexa ingresada como argumento.\n");
	// printf("La direccion debe estar comprendida en el rango: 0 - %x\n", LAST_MEM_POSITION - 32); CHEQUEO MAXMEM
	printf("\n/divzero : Excepcion division por cero\n");
	printf("\n/opcode : Excepcion opcode invalido\n");

	printf("\n/exit : Finaliza la ejecucion.\n\n");
}
