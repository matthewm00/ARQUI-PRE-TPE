#ifndef TEST_SYNC_H
#define TEST_SYNC_H

#include <test_util.h>

#define SEM_ID 55
#define TOTAL_PAIR_PROCESSES 2

uint64_t test_sync(uint64_t argc, char *argv[]);
uint64_t test_no_sync(uint64_t argc, char *argv[]);

#endif