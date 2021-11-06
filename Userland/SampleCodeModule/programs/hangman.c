#include <hangman.h>

int lives = WORD_LENGTH;
char word[WORD_LENGTH] = "PEJELAGARTO";
char playerWord[WORD_LENGTH] = "___________";

static int firstPosX = 600;
static int firstPosY = 600;

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
    changeCursorState(0);
}

void startHangman()
{
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        printLetter(i, '_');
    }
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
    if (lives == 0 || strcmp(word, playerWord) == 0){
        gameOver();
        return;
    }

    int size = 1;
    int guessed = 0;
    int repeated = repeatedLetter(c);
    for (int i = 0; i < WORD_LENGTH && !repeated; i++)
    {
        if (word[i] == c)
        {
            guessed = 1;
            playerWord[i] = c;
        }
    }
    if (!guessed)
    {
        lives--;
    }
}

void printPlayerWord()
{
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        printLetter(i, playerWord[i]);
    }
    setCursor(firstPosX, firstPosY + CHAR_HEIGHT * 2);
    printf("VIDAS: %d", lives);
    changeCursorState(0);
}

void gameOver(){
    if(lives == 0){
        printf("GAME OVER, ¡te quedaste sin vidas!");
    } else {
        printf("GANASTE, ¡Felicitaciones!");
    }
}