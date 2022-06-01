// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <commands.h>
#include <libc.h>
#include <phylo.h>
#include <userSyscalls.h>

#define LEFT(i) (((i) + phylosCounter - 1) % phylosCounter)
#define RIGHT(i) (((i) + 1) % phylosCounter)

typedef enum
{
        THINKING,
        HUNGRY,
        EATING
} t_phylo_state;

typedef struct t_phylo_state
{

        int pid;
        int sem;
        int ID;
        t_phylo_state state;

} t_phylosofer;

t_phylosofer *phylos[MAX_PHYLOS];
static int phylosCounter = 0;
static int mutex;
static int tableOpen;

// static void thinkOrEat();
// static void phyloMain(int argc, char **argv);
// static void takeForks(int i);
// static void putForks(int i);
// static void test(int i);
// static int addPhylo();
// static int removePhilo();
// static void printTable(int argc, char **argv);

void thinkOrEat()
{
        // sleep(THINK_EAT_WAIT_SECONDS);
}

void phyloMain(int argc, char **argv)
{
        int i = strToInt(argv[1], 0);
        while (1)
        {
                takeForks(i);
                thinkOrEat();
                putForks(i);
                thinkOrEat();
        }
}

void takeForks(int i)
{
        semWait(mutex);
        phylos[i]->state = HUNGRY;
        test(i);
        semPost(mutex);
        semWait(phylos[i]->sem);
}

void putForks(int i)
{
        semWait(mutex);
        phylos[i]->state = THINKING;
        test(LEFT(i));
        test(RIGHT(i));
        semPost(mutex);
}

void test(int i)
{
        if (phylos[i]->state == HUNGRY &&
            phylos[LEFT(i)]->state != EATING &&
            phylos[RIGHT(i)]->state != EATING)
        {
                phylos[i]->state = EATING;
                semPost(phylos[i]->sem);
        }
}

int addPhylo()
{
        if (phylosCounter == MAX_PHYLOS)
        {
                return -1;
        }

        semWait(mutex);
        t_phylosofer *phylosopher = malloc(sizeof(t_phylosofer));
        if (phylosopher == NULL)
        {
                return -1;
        }
        phylosopher->sem = semOpen(PHYLO_SEM_ID + phylosCounter, 1);
        phylosopher->state = THINKING;
        phylosopher->ID = phylosCounter;

        char index[3];
        intToStr(phylosCounter, index, 10);

        char *argv[] = {"phylosopher", index};
        phylosopher->pid = newProcess(&phyloMain, 2, argv, BACKGROUND, NULL);

        phylos[phylosCounter++] = phylosopher;

        semPost(mutex);
        return 0;
}

int removePhilo()
{
        if (phylosCounter == INITIAL_PHYLOS)
        {
                return -1;
        }

        semWait(mutex);

        t_phylosofer *phylosopher = phylos[--phylosCounter];
        semClose(phylosopher->sem);
        killProcess(phylosopher->pid);
        free(phylosopher);

        semPost(mutex);
        return 0;
}

void printTable(int argc, char **argv)
{
        while (tableOpen)
        {
                semWait(mutex);
                int i;
                for (i = 0; i < phylosCounter; i++)
                {
                        if (phylos[i]->state == EATING)
                        {
                                putChar('E');
                        }
                        else
                        {
                                putChar('-');
                        }
                        putChar(' ');
                }
                putChar('\n');
                semPost(mutex);
                yield();
        }
}

void phyloProblem(int argc, char **argv)
{
        if(checkArgCount(argc, 1) == -1){
                return;
        }

        phylosCounter = 0;
        tableOpen = 1;
        semOpen(MUTEX_SEM_ID, 1);

        int i = 0;
        while (i < INITIAL_PHYLOS){
                addPhylo();
                i++;
        }

        printf("\nDejamos comer a los filosofos iniciales por %d segundos.\n\n\n",
                FRONTEND_WAIT_SECONDS);

        char *args[] = {"Phylo Table"};
        int tablePID = newProcess(&printTable, 1, args, BACKGROUND, NULL);

        sleep(FRONTEND_WAIT_SECONDS);

        printf("\nYa pueden entrar o salir comensales\n\n");

        while(tableOpen){
                char key = getChar();
                switch (key)
                {
                case 'a':
                        if(addPhylo() == -1)
                                printf("\nNo hay mas lugar en la mesa.\n\n");
                        else 
                                printf("\nSe agrego un comensal.\n\n");
                        
                        break;
                case 'r':
                        if(removePhilo() == -1)
                                printf("\nNo se puede retirar\n\n");
                        else
                                printf("\nSe retiro un comensal.\n\n");
                        break;
                case 'q':
                        printf("\nSe finalizo con exito\n\n");
                        tableOpen = 0;
                        break;
                default:
                        break;
                }
        }
        
        int i;
        for(i = 0; i < phylosCounter; i++){
                semClose(phylos[i]->sem);
                killProcess(phylos[i]->pid);
                free(phylos[i]);
        }
        killProcess(tablePID);
        semClose(MUTEX_SEM_ID);
}