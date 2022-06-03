#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <colors.h>
#include <stdint.h>

uint8_t getCurrentTime(uint64_t rtcID);
uint8_t _getRTCInfo(uint64_t rtcID);
void sysWrite(char *str, uint8_t len, t_color bgColor, t_color ftColor, int usrLen);
uint64_t sysRead();
void getMem(uint64_t direc, uint8_t *buffer, uint64_t bytes);
uint8_t _getMem(uint64_t direc);
void _exit(void);
uint64_t *getRegisters();
void updateRegisters(uint64_t *rsp);
void *malloc(uint64_t nbytes);
void free(void *block);
void memoryDump();
#endif