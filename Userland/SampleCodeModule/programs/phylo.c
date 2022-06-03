#include <commands.h>
#include <libc.h>
#include <phylo.h>
#include <userSyscalls.h>

typedef enum
{
        THINKING,
        HUNGRY,
        EATING
} t_philo_state;

typedef struct t_philosofer
{
        int pid;
        int sem;
        int ID;
        t_philo_state state;
} t_philosofer;

t_philosofer *philosophers[MAX_PHYLOS];
static int philosopherCount = 0;
static int mutex;
static int tableOpen;

#define LEFT(i) (((i) + philosopherCount - 1) % philosopherCount)
#define RIGHT(i) (((i) + 1) % philosopherCount)

void phyloProblem(int argc, char **argv)
{
        if (checkArgcWrapper(argc, 1) == -1)
        {
                return;
        }
        philosopherCount = 0;
        tableOpen = 1;
        semOpen(MUTEX_SEM_ID, 1);

        int i = 0;
        while (i < INITIAL_PHYLOS)
        {
                addPhylo();
                i++;
        }

        printf("\nVamos a dejar comer a los filosofos iniciales por %d segundos.\n\n",
               FRONTEND_WAIT_SECONDS);

        char *args[] = {"Phylo Table"};
        int tablePID = newProcess(&printTable, 1, args, BACKGROUND, NULL);

        sleep(FRONTEND_WAIT_SECONDS);

        printf("\nYa puede agregar o retirar comensales y terminar la cena.\n\n");

        while (tableOpen)
        {
                char key = getChar();
                switch (key)
                {
                case 'a':
                        if (addPhylo() == -1)
                        {
                                printf("\nNo hay mas lugar en la mesa.\n\n");
                        }
                        else
                        {
                                printf("\nSe agrego un comensal.\n\n");
                        }
                        break;
                case 'r':
                        if (removePhylo() == -1)
                        {
                                printf("\nPor favor no se vaya.\n\n");
                        }
                        else
                        {
                                printf("\nSe retiro un comensal.\n\n");
                        }
                        break;
                case 'q':
                        printf(
                            "\nMesa cerrada.\n\n");
                        tableOpen = 0;
                        break;
                default:
                        break;
                }
        }

        for (int i = 0; i < philosopherCount; i++)
        {
                semClose(philosophers[i]->sem);
                killProcess(philosophers[i]->pid);
                free(philosophers[i]);
        }
        killProcess(tablePID);
        semClose(MUTEX_SEM_ID);
}

int addPhylo()
{
        if (philosopherCount == MAX_PHYLOS)
        {
                return -1;
        }

        semWait(mutex);
        t_philosofer *philosopher = malloc(sizeof(t_philosofer));
        if (philosopher == NULL)
        {
                return -1;
        }
        philosopher->sem = semOpen(PHYLO_SEM_ID + philosopherCount, 1);
        philosopher->state = THINKING;
        philosopher->ID = philosopherCount;

        char index[3];
        intToStr(philosopherCount, index, 10);

        char *argv[] = {"philosopher", index};
        philosopher->pid = newProcess(&phyloMain, 2, argv, BACKGROUND, NULL);

        philosophers[philosopherCount++] = philosopher;

        semPost(mutex);
        return 0;
}

int removePhylo()
{
        if (philosopherCount == INITIAL_PHYLOS)
        {
                return -1;
        }

        semWait(mutex);

        t_philosofer *philosopher = philosophers[--philosopherCount];
        semClose(philosopher->sem);
        killProcess(philosopher->pid);
        free(philosopher);

        semPost(mutex);
        return 0;
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
        philosophers[i]->state = HUNGRY;
        test(i);
        semPost(mutex);
        semWait(philosophers[i]->sem);
}

void putForks(int i)
{
        semWait(mutex);
        philosophers[i]->state = THINKING;
        test(LEFT(i));
        test(RIGHT(i));
        semPost(mutex);
}

void test(int i)
{
        if (philosophers[i]->state == HUNGRY &&
            philosophers[LEFT(i)]->state != EATING &&
            philosophers[RIGHT(i)]->state != EATING)
        {
                philosophers[i]->state = EATING;
                semPost(philosophers[i]->sem);
        }
}

void thinkOrEat() { sleep(THINK_EAT_WAIT_SECONDS); }

void printTable(int argc, char **argv)
{
        while (tableOpen)
        {
                semWait(mutex);
                int i;
                for (i = 0; i < philosopherCount; i++)
                {
                        if (philosophers[i]->state == EATING)
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