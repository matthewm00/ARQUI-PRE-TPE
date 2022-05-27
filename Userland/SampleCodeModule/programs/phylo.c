// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <commands.h>
#include <libc.h>
#include <phylo.h>
#include <syscalls.h>

typedef enum { THINKING , HUNGRY , EATING } t_phylo_state;

typedef struct t_phylo_state {

        int pid;
        int sem;
        int ID;
        t_phylo_state state;

}t_phylosofer;

t_phylosofer *phylosophers[MAX_PHYLOS];
static int phylosophersCount = 0;
static int mutex;

// #define LEFT(i) (((i) + phylosophersCount - 1) % phylosophersCount)
// #define RIGHT(i) (((i) + 1) % phylosophersCount)

// static void thinkOrEat();
// static void phyloMain(int argc, char **argv);
// static void takeForks(int i);
// static void putForks(int i);
// static void test(int i);
// static int addPhylo();

// CHEQUEAR EL TEMA DE LOS NOMBRES DE LAS VARS (SINGULARES Y PLURALES)

void thinkOrEat(){
        sleep(THINK_EAT_WAIT_SECONDS);
}

void phyloMain(int argc, char **argv){
        int i = strToInt(argv[1], 0);
        while (1)
        {
                takeForks(i);
                thinkOrEat();
                putForks(i);
                thinkOrEat();
        }
}

void takeForks(int i){
        semWait(mutex);
        phylosophers[i]->state = HUNGRY;
        test(i);
        semPost(mutex);
        semWait(phylosophers[i]->sem);
}

void putForks(int i){
        semWait(mutex);
        phylosophers[i]->state = THINKING;
        test(LEFT(i));
        test(RIGHT(i));
        semPost(mutex);
}

void test(int i){
        if (phylosophers[i]->state == HUNGRY &&
        phylosophers[LEFT(i)]->state != EATING &&
        phylosophers[RIGHT(i)]->state != EATING){
                phylosophers[i]->state = EATING;
                semPost(phylosophers[i]->sem);
        }
        
}

int addPhylo(){
        if (phylosophersCount == MAX_PHYLOS){
                return -1;
        }
        
        semWait(mutex);
        t_phylosofer * phylosopher = malloc(sizeof(t_phylosofer));
        if (phylosopher == NULL){
                return -1;
        }
        phylosopher->sem = semOpen(PHYLO_SEM_ID + phylosophersCount, 1);
        phylosopher->state = THINKING;
        phylosopher->ID = phylosophersCount;

        char index[3];
        intToStr(phylosophersCount, index, 10);

        char *argv[] = {"phylosopher", index};
        phylosopher->pid = newProcess(&phyloMain, 2, argv, BACKGROUND, NULL);

        phylosophers[phylosophersCount++] = phylosopher;

        semPost(mutex);
        return 0;
}