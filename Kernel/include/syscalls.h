#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include <colors.h>
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <pipes.h>
#include <processManager.h>

#define REGISTER_AMOUNT 17

// #define SYS_RTC_ID 1
// #define SYS_READ_ID 2
// #define SYS_WRITE_ID 3
// #define SYS_INFOREG_ID 4
// #define SYS_PRINTMEM_ID 5
// #define SYS_CLEAR_ID 6
// #define SYS_EXIT_ID 7
// #define SYS_GAMES_ID 8
// #define SYS_TIME_ID 9

// #define SYS_CURSOR_ID 10
// #define SYS_CURSORSTATE_ID 11
// #define SYS_STOPWATCH_ID 12
// #define SYS_STOPWATCHTICKS_ID 13

typedef enum
{
    SYS_RTC_ID,
    SYS_READ_ID,
    SYS_WRITE_ID,
    SYS_INFOREG_ID,
    SYS_PRINTMEM_ID,
    SYS_CLEAR_ID,
    SYS_EXIT_ID,

    SYS_GAMES_ID,
    SYS_TIME_ID,

    SYS_CURSOR_ID,
    SYS_CURSORSTATE_ID,
    SYS_STOPWATCH_ID,
    SYS_STOPWATCHTICKS_ID,

    SYS_MALLOC_ID,
    SYS_FREE_ID,
    SYS_MEMORY_STATUS_ID,
    SYS_NEW_PROCESS_ID,
    SYS_KILL_PROCESS_ID,
    SYS_PROCESS_PID_ID,
    SYS_PROCESS_STATUS_ID,
    SYS_BLOCK_PROCESS_ID,
    SYS_CHANGE_PROCESS_STATE_ID,
    SYS_YIELD_ID,
    SYS_SET_PRIORITY_ID,
    SYS_UNBLOCK_PROCESS_ID,
    SYS_SEM_OPEN_ID,
    SYS_SEM_POST_ID,
    SYS_SEM_WAIT_ID,
    SYS_SEM_CLOSE_ID,
    SYS_SEM_STATUS_ID,
    SYS_SEC_ELAPSED_ID,
    SYS_PIPE_STATUS_ID,
    SYS_PIPE_OPEN_ID,
    SYS_PIPE_CLOSE_ID,
    SYS_PIPE_WRITE_ID,
    SYS_PIPE_READ_ID,
    SYS_WAIT_ID
} t_syscall_id;

uint8_t getCurrentTime(uint64_t rtcID);
uint8_t _getRTCInfo(uint64_t rtcID);
void sys_write(char *str, uint8_t len, t_color bgColor, t_color ftColor);
uint64_t sys_read();
void getMem(uint64_t direc, uint8_t *buffer, uint64_t bytes);
uint8_t _getMem(uint64_t direc);
void _exit();
uint64_t *getRegisters();
void saveRegisters(uint64_t *rsp);
uint8_t getHour();
uint8_t getMins();
uint8_t getSeconds();
uint8_t getDecimalTime(uint64_t type);

#endif