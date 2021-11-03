#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include <colors.h>

#define SYS_RTC_ID 1
#define SYS_READ_ID 2
#define SYS_WRITE_ID 3
#define SYS_INFOREG_ID 4
#define SYS_PRINTMEM_ID 5
#define SYS_CLEAR_ID 6
#define SYS_EXIT_ID 7
#define SYS_GAMES_ID 8

uint8_t getCurrentTime(uint64_t rtcID);
uint8_t _getRTCInfo(uint64_t rtcID);
void sys_write(char *str, uint8_t len, t_color bgColor, t_color ftColor, int usrLen);
uint64_t sys_read();
void getMem(uint64_t direc, uint8_t *buffer, uint64_t bytes);
uint8_t _getMem(uint64_t direc);
void _exit(int n);
uint64_t *getRegisters();
void saveRegisters(uint64_t *rsp);
void _saveRegisters(void);
#endif