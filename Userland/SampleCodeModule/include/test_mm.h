#ifndef TEST_MM_H
#define TEST_MM_H

#include <test_util.h>

#define MAX_BLOCKS 128

typedef struct MM_rq
{
  void *address;
  uint32_t size;
} mm_rq;

uint64_t test_mm(uint64_t argc, char *argv[]);

#endif