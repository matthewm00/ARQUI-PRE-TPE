#ifndef TEST_PRIORITY_H
#define TEST_PRIORITY_H

#include <test_util.h>

#define MINOR_WAIT 1000000 // TODO: Change this value to prevent a process from flooding the screen
#define WAIT 10000000      // TODO: Change this value to make the wait long enough to see theese processes beeing run at least twice

#define TOTAL_PROCESSES 3

void test_priority();
#endif