// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <defs.h>
#include <idtLoader.h>
#include <interrupts.h>
#include <stdint.h>

#pragma pack(push) /* Push de la alineación actual */
#pragma pack(1)    /* Alinear las siguiente estructuras a 1 byte */

/* Descriptor de interrupcion */
typedef struct {
  uint16_t offset_l, selector;
  uint8_t cero, access;
  uint16_t offset_m;
  uint32_t offset_h, other_cero;
} DESCR_INT;

#pragma pack(pop) /* Reestablece la alinceación actual */

DESCR_INT *idt = (DESCR_INT *)0;  // IDT de 255 entradas

static void setupIdtEntry(int index, uint64_t offset);

void loadIdt() {
  _cli();

  setupIdtEntry(0x21, (uint64_t)&_irq01Handler);
  setupIdtEntry(0x80, (uint64_t)&_syscallHandler);
  setupIdtEntry(0x00, (uint64_t)&_exception0Handler);
  setupIdtEntry(0x06, (uint64_t)&_exception6Handler);

  // Teclado y timer habilitados
  picMasterMask(0xFC);
  picSlaveMask(0xFF);

  setupIdtEntry(0x20, (uint64_t)&_irq00Handler);
  _sti();
}

static void setupIdtEntry(int index, uint64_t offset) {
  idt[index].selector = 0x08;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset >> 16) & 0xFFFF;
  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
  idt[index].access = ACS_INT;
  idt[index].cero = 0;
  idt[index].other_cero = (uint64_t)0;
}
