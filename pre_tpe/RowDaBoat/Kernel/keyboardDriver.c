#include <keyboard.h>

char readKeyboard();
int hasKeyboardKey();

#define BUFF_SIZE 100
typedef struct Buffer {
    char buffer[BUFF_SIZE];
    int start;
    int size;
} Buffer;

// https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html pagina de los scancodes
static const char keyCodes[KEYS][2] = {
    {0, 0}, {ESC, ESC}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'}, {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'}, {CTRL, CTRL}, {'a', 'A'}, {'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'}, {L_SHIFT, L_SHIFT}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, {'/', '?'}, {R_SHIFT, R_SHIFT}, {0, 0}, {0, 0}, {SPACE_BAR, SPACE_BAR}, {CAPS_LCK, CAPS_LCK}};

char Buffer buffer[BUFF_SIZE] = {0};
buffer.size = 0;
buffer.start = 0;
// char *getKeyboardBuffer()
// {
//     return buffer;
// }

int shift = 0;
int capsLock = 0;

void keyboardHandler()
{
    if (hasKeyboardKey())
    {
        unsigned char key = readKeyboard();
        // Key is pressed
        if (key >= ESC && key <= CAPS_LCK)
        {
            if (key == L_SHIFT || key == R_SHIFT)
            {
                shift = 1;
            }
            else if (key == CAPS_LCK)
            {
                capsLock = 1;
            }

            if ((shift || capsLock != 0) && (!(R_SHIFT == key || L_SHIFT == key || R_SHIFT_RELEASED == key || L_SHIFT_RELEASED == key)))
            {
                buffer[buff_dim++] = keyCodes[key][1];
            }
            else
            {
                buffer[buff_dim++] = keyCodes[key][0];
            }
        }
        // Key is released
        else if (key >= ESC_RELEASED)
        {
            if (key == L_SHIFT_RELEASED || key == R_SHIFT_RELEASED)
            {
                shift = 0;
            }
            else if (keyCodes[key][0] == 0)
            {
                return;
            }
        }
        else
            return;
    }
}

int putChar(char c) {    
    //Resets buffer position to the start of the array if it's full.
    if(buffer.size >= BUFFER_SIZE)
        buffer.start++;

    int offset = (buffer.start + buffer.size) % BUFFER_SIZE;
	buffer.buffer[offset] = c;

    if(buffer.size < BUFFER_SIZE)
        buffer.size++;
    
    return 0;
}

char getChar(int index) {
    if(buffer.size == 0)
        return 0;

    char toReturn = buffer[index];

    // Removes read character and increments start position
    buffer.buffer[index] = 0;
    buffer.start++;
    buffers.size--;

    if(buffer.start >= BUFFER_SIZE)
        buffer.start = 0;
    
    return toReturn;
}

void clearBuffer(int index) {
    buffer.start = 0;
    buffer.size = 0;

    for(int i=0; i<BUFFER_SIZE; i++) {
        buffer.buffer[i] = 0; 
    }
}