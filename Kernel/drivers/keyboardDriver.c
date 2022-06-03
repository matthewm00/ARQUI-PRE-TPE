// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <colors.h>
#include <interrupts.h>
#include <keyboardDriver.h>
#include <processManager.h>
#include <semaphores.h>
#include <syscalls.h>
#include <videoDriver.h>

#define PRESS 1
#define RELEASE 2
#define ERROR -1
#define BUFF_LEN 30
#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define CAPS_LOCK 0x3A
#define CTRL 0x1D
#define KEYBOARD_SEM_ID 10

static char buffer[BUFF_LEN] = {0};

static int buffSize = 0; // cantidad de elementos del buffer
static int ridx = 0;     // posicion de escritura
static int widx = 0;     // posicion de lectura

static int shift = 0;
static int ctrl = 0;
static int capsLock = 0;

// https://www.qbasic.net/en/reference/general/scan-codes.htm
static char charTable[58][2] = {
    {0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'}, {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'}, {0, 0}, {'a', 'A'}, {'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'}, {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, {'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {' ', ' '}};

uint8_t getAction(uint8_t scanCode)
{
  if (scanCode >= 0x01 && scanCode <= 0x3A)
  {
    return PRESS;
  }
  else if (scanCode >= 0x81 && scanCode <= 0xBA)
  {
    return RELEASE;
  }
  return ERROR;
}

void cleanKeyboardBuffer()
{
  buffSize = 0;
  widx = 0;
  ridx = 0;
}
int bufferSize() { return buffSize; }
void keyboardHandler(uint64_t rsp)
{
  if (_hasKey())
  {
    uint8_t scanCode = _getKey();
    uint8_t currentAction = getAction(scanCode);
    if (currentAction == PRESS)
    {
      if (scanCode == LEFT_SHIFT || scanCode == RIGHT_SHIFT)
      {
        shift = 1;
      }
      else if (scanCode == CAPS_LOCK)
      {
        capsLock = capsLock == 1 ? 0 : 1;
      }
      else if (scanCode == CTRL)
      {
        ctrl = 1;
      }
      else if (scanCode >= 58 || scanCode & 0x80 ||
               (scanCode == 15 && ctrl == 0))
      {
        return; // NO ASCII
      }
      else
      {
        if (charTable[scanCode][0] != 0)
        {
          if (ctrl && charTable[scanCode][0] == 's')
          {
            updateRegisters((uint64_t *)rsp);
          }
          else if (ctrl && charTable[scanCode][0] == 'c')
          {
            killCurrentFGProcess();
          }
          else if (ctrl && charTable[scanCode][0] == 'd')
          {
            putCharInBuffer(96);
          }
          else if ((shift && !capsLock) ||
                   (shift && capsLock &&
                    !(charTable[scanCode][0] >= 'a' &&
                      charTable[scanCode][0] <= 'z')) ||
                   (!shift && capsLock && charTable[scanCode][0] >= 'a' &&
                    charTable[scanCode][0] <= 'z'))
          {
            putCharInBuffer(charTable[scanCode][1]);
          }
          else
          {
            if (charTable[scanCode][0] == 96)
            {
              return;
            }
            putCharInBuffer(charTable[scanCode][0]);
          }
        }
      }
    }
    else if (currentAction == RELEASE)
    {
      if (scanCode == LEFT_SHIFT + 0x80 || scanCode == RIGHT_SHIFT + 0x80)
      {
        shift = 0;
      }
      else if (scanCode == CTRL + 0x80)
      {
        ctrl = 0;
      }
    }
  }
}
void putCharInBuffer(char c)
{
  semPost(KEYBOARD_SEM_ID);
  if (c != 0)
  {
    buffer[widx] = c;

    widx++;
    if (widx == BUFF_LEN)
    {
      widx = 0;
    }
    if (buffSize < BUFF_LEN)
    {
      buffSize++;
    }
    else
    {
      ridx++;
      if (ridx == BUFF_LEN)
      {
        ridx = 0;
      }
    }
  }
}

char getChar()
{
  // semWait(KEYBOARD_SEM_ID);
  if (isCursorOn()) // si no esta en games
  {
    semWait(KEYBOARD_SEM_ID);
    char c = 0;
    c = removeCharFromBuffer();
    if (c == '\b')
    {
      removeCharFromBuffer();
    }
    while (c == -1)
    {
      cursor();
      _hlt();
      c = removeCharFromBuffer();
    }
    stopCursor();
    return c;
  }
  stopCursor();
  return removeCharFromBuffer();
}

char removeCharFromBuffer()
{
  if (buffSize <= 0)
  {
    return -1;
  }

  int c = buffer[ridx];
  ridx = (ridx + 1) % BUFF_LEN;

  buffSize--;
  return c;
}
uint64_t dumpBuffer(char *dest, int size)
{
  int i = 0;
  if (size <= 0 || buffSize <= 0)
  {
    return -1;
  }

  while (i < size - 1 && buffSize)
  {
    dest[i++] = removeCharFromBuffer();
  }
  dest[i] = 0;
  return i;
}

int initializeKeyboard()
{
  if (semOpen(KEYBOARD_SEM_ID, 0) == -1)
  {
    return -1;
  }
  return 0;
}
