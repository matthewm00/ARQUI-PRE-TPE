#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <idtLoader.h>
#include <clock.h>
#include <keyboard.h>
#include <time.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void *const sampleCodeModuleAddress = (void *)0x400000;
static void *const sampleDataModuleAddress = (void *)0x500000;

typedef int (*EntryPoint)();

void clearBSS(void *bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void *getStackBase()
{
	return (void *)((uint64_t)&endOfKernel + PageSize * 8 // The size of the stack itself, 32KiB
					- sizeof(uint64_t)					  // Begin at the top of the stack
	);
}

void *initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void *moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

int main()
{
	// ncPrint("[Kernel Main]");
	// ncNewline();
	// ncPrint("  Sample code module at 0x");
	// ncPrintHex((uint64_t)sampleCodeModuleAddress);
	// ncNewline();
	// ncPrint("  Calling the sample code module returned: ");
	// ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	// ncNewline();
	// ncNewline();

	// ncPrint("  Sample data module at 0x");
	// ncPrintHex((uint64_t)sampleDataModuleAddress);
	// ncNewline();
	// ncPrint("  Sample data module contents: ");
	// ncPrint((char *)sampleDataModuleAddress);
	// ncNewline();

	ncClear();

	// ej 1 y 2
	ncNewline();
	ncPrintString(0xFA, "Arquitectura de las computadoras"); // green on white

	// ej 3
	ncNewline();
	char *time;
	char *date;
	timeToStr(time);
	ncPrint(time);
	ncNewline();
	dateToStr(date);
	ncPrint(date);

	// ej 4
	ncNewline();
	ncNewline();
	ncPrint("Esperando tecla...");
	char i = getKey();
	char teclahex = i;
	ncNewline();
	ncPrint("Tecla recibida");
	ncNewline();
	ncPrintHex(teclahex);
	char teclahexant;

	for (int j = 1; j < 10; j++)
	{
		i = getKey();
		teclahex = i;
		if (teclahex != teclahexant)
		{
			ncPrintHex(teclahex);
			teclahexant = teclahex;
		}
	}

	ncNewline();
	// ej 5
	load_idt();

	uint8_t changeDetected = 0;
	int t = 0;
	while (t < 100)
	{
		if (!changeDetected && ticks_elapsed() % 6 == 0)
		{
			changeDetected = 1;
			ncPrint("6");
			if (ticks_elapsed() % 18 == 0)
			{
				ncPrint("T");
			}
		}

		if (changeDetected && ticks_elapsed() % 6 != 0)
		{
			changeDetected = 0;
		}

		t++;
	}

	ncNewline();
	ncPrint("[Finished]");
	return 0;
}
