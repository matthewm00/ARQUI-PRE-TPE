// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <idtLoader.h>
#include <keyboardDriver.h>
#include <lib.h>
#include <memoryManager.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <processManager.h>
#include <stdint.h>
#include <videoDriver.h>

#define HEAP_MEMORY_SIZE 1024 * 1024 * 64 // 64MB

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void *const sampleCodeModuleAddress = (void *)0x400000;
static void *const sampleDataModuleAddress = (void *)0x500000;
static void *const sampleCodeModuleHeapAddress = (void *)0x600000;

typedef int (*EntryPoint)();

void clearBSS(void *bssAddress, uint64_t bssSize)
{
  memset(bssAddress, 0, bssSize);
}

void *getStackBase()
{
  return (void *)((uint64_t)&endOfKernel +
                  PageSize * 8       // The size of the stack itself, 32KiB
                  - sizeof(uint64_t) // Begin at the top of the stack
  );
}

void *initializeKernelBinary()
{
<<<<<<< HEAD
  void *moduleAddresses[] = {sampleCodeModuleAddress, sampleDataModuleAddress};

  loadModules(&endOfKernelBinary, moduleAddresses);

  clearBSS(&bss, &endOfKernel - &bss);

  return getStackBase();
=======
	void *moduleAddresses[] = {sampleCodeModuleAddress, sampleDataModuleAddress};
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

int main()
{
<<<<<<< HEAD
  initializeMemoryManager((char *)sampleCodeModuleHeapAddress,
                          HEAP_MEMORY_SIZE);
  initializeVideo();
  initializeKeyboard();
  initializeProcessManager();
  char *userland[] = {"Userland Init"};
  newProcess(sampleCodeModuleAddress, 1, userland, FOREGROUND, 0);
  loadIdt();
  _hlt();
  printf("\nFATAL FAILURE\n");
  return 0;
=======
	initializeMemoryManager((char *)sampleCodeModuleHeapAddress, HEAP_MEMORY_SIZE);
	initializeVideo();
	initializeKeyboard();
	initializeProcessManager();
	char *userland[] = {"Userland Init"};
	newProcess(sampleCodeModuleAddress, 1, userland, FOREGROUND, 0);
	load_idt();
	_hlt();
	return 0;
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}