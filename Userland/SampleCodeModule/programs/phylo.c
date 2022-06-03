#include <commands.h>
#include <libc.h>
#include <phylo.h>
#include <userSyscalls.h>

typedef enum
{
<<<<<<< HEAD
  THINKING,
  HUNGRY,
  EATING
=======
        THINKING,
        HUNGRY,
        EATING
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
} t_philo_state;

typedef struct t_philosofer
{
<<<<<<< HEAD
  int pid;
  int sem;
  int ID;
  t_philo_state state;
} t_philosofer;

t_philosofer *philosophers[MAX_PHILOS];
=======
        int pid;
        int sem;
        int ID;
        t_philo_state state;
} t_philosofer;

t_philosofer *philosophers[MAX_PHYLOS];
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
static int philosopherCount = 0;
static int mutex;
static int tableOpen;

#define LEFT(i) (((i) + philosopherCount - 1) % philosopherCount)
#define RIGHT(i) (((i) + 1) % philosopherCount)

<<<<<<< HEAD
static void thinkOrEat();
static void philoMain(int argc, char **argv);
static void takeForks(int i);
static void putForks(int i);
static void test(int i);
static int addPhilo();
static int removePhilo();
static void printTable(int argc, char **argv);

void philoProblem(int argc, char **argv)
{
  if (checkArgcWrapper(argc, 1) == -1)
  {
    return;
  }
  philosopherCount = 0;
  tableOpen = 1;
  semOpen(MUTEX_SEM_ID, 1);

  int i = 0;
  while (i < INITIAL_PHILOS)
  {
    addPhilo();
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
      if (addPhilo() == -1)
      {
        printc(RED, "\nNo hay mas lugar en la mesa.\n\n");
      }
      else
      {
        printc(GREEN, "\nSe agrego un comensal.\n\n");
      }
      break;
    case 'r':
      if (removePhilo() == -1)
      {
        printc(BLUE, "\nPor favor no se vaya.\n\n");
      }
      else
      {
        printc(RED, "\nSe retiro un comensal.\n\n");
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

static int addPhilo()
{
  if (philosopherCount == MAX_PHILOS)
  {
    return -1;
  }

  semWait(mutex);
  t_philosofer *philosopher = malloc(sizeof(t_philosofer));
  if (philosopher == NULL)
  {
    return -1;
  }
  philosopher->sem = semOpen(FILO_SEM_ID + philosopherCount, 1);
  philosopher->state = THINKING;
  philosopher->ID = philosopherCount;

  char index[3];
  intToStr(philosopherCount, index, 10);

  char *argv[] = {"philosopher", index};
  philosopher->pid = newProcess(&philoMain, 2, argv, BACKGROUND, NULL);

  philosophers[philosopherCount++] = philosopher;

  semPost(mutex);
  return 0;
}

static int removePhilo()
{
  if (philosopherCount == INITIAL_PHILOS)
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

static void philoMain(int argc, char **argv)
{
  int i = strToInt(argv[1], 0);
  while (1)
  {
    takeForks(i);
    thinkOrEat();
    putForks(i);
    thinkOrEat();
  }
=======
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
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
}

static void takeForks(int i)
{
<<<<<<< HEAD
  semWait(mutex);
  philosophers[i]->state = HUNGRY;
  test(i);
  semPost(mutex);
  semWait(philosophers[i]->sem);
}

static void putForks(int i)
{
  semWait(mutex);
  philosophers[i]->state = THINKING;
  test(LEFT(i));
  test(RIGHT(i));
  semPost(mutex);
}

static void test(int i)
{
  if (philosophers[i]->state == HUNGRY &&
      philosophers[LEFT(i)]->state != EATING &&
      philosophers[RIGHT(i)]->state != EATING)
  {
    philosophers[i]->state = EATING;
    semPost(philosophers[i]->sem);
  }
}

static void thinkOrEat() { sleep(THINK_EAT_WAIT_SECONDS); }

static void printTable(int argc, char **argv)
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
=======
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
>>>>>>> 4952e0d119666c812b43ed3d08c647ea077f623a
