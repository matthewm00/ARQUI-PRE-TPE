#include <hangman.h>

int lives = 3;
char word[WORD_LENGTH] = "COMPUTADORA";
char playerWord[WORD_LENGTH];
static int playerWordDim = 0;
static int finished = 0;
static int firstPosX = 700;
static int firstPosY = 550;

static void getLetterPosition(int index, int *x)
{
    *x = (index * CHAR_WIDTH * 2) + firstPosX;
}

static void printLetter(int index, char letter)
{
    int x;
    getLetterPosition(index, &x);
    setCursor(x, firstPosY);
    printf("%c ", letter);
    // changeCursorState(0);
    return;
}

void startHangman()
{
    for (int i = 0; i < WORD_LENGTH; i++)
        playerWord[i] = '_';
    lives = 3;
    finished = 0;

    setCursor(530, 435);
    printf("Juegue al ahorcado y complete la palabra para ganar!");
    // changeCursorState(0);
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        printLetter(i, '_');
    }
    return;
}

int repeatedLetter(char c)
{
    int found = 0;
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        if (playerWord[i] == c)
        {
            found = 1;
        }
    }

    return found;
}

void hangman(char c)
{
    if (finished)
        return;

    int size = 1;
    int guessed = 0;
    int repeated = repeatedLetter(c);
    for (int i = 0; i < WORD_LENGTH && !repeated; i++)
    {
        if (word[i] == c)
        {
            guessed = 1;
            playerWord[i] = c;
            playerWordDim++;
        }
    }
    if (!guessed)
    {
        lives--;
    }

    printPlayerWord();

    if (playerWordDim == WORD_LENGTH || lives == 0)
    {
        gameOver();
    }
    return;
}

void printPlayerWord()
{
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        printLetter(i, playerWord[i]);
    }
    setCursor(firstPosX + CHAR_WIDTH * 6, firstPosY + CHAR_HEIGHT * 5);
    printf("VIDAS: %d", lives);
    // changeCursorState(0);
    return;
}

void gameOver()
{
    finished = 1;
    setCursor(530, 720);
    if (lives == 0)
        printf("GAME OVER, te quedaste sin vidas!");
    else
        printf("GANASTE, felicitaciones!");
    // changeCursorState(0);
    return;
}