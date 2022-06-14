#include <memoryManager.h>
#include <sharedMemory.h>

#define MEM_SIZE 1024
#define SHM_SIZE 50

typedef struct sharedM
{
    uint64_t id;
    void *memP;
} sharedM;

static sharedM sharedMArray[SHM_SIZE];
int processCounter = 0;

void *sharedMem(uint64_t id)
{
    int i;
    for (i = 0; i < processCounter; i++)
    {
        if (sharedMArray[i].id == id)
        {
            return sharedMArray[i].memP;
        }
    }
    void *memP = malloc(MEM_SIZE);
    sharedMArray[i].id = id;
    sharedMArray[i].memP = memP;
    processCounter++;

    return memP;
}
