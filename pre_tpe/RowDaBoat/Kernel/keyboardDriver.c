#include <keyboard.h>

char readKeyboard();
int hasKeyboardKey();

#define BUFF_SIZE 100
// https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html pagina de los scancodes
static const char keyCodes[KEYS][2] = {
    {0, 0}, {ESC, ESC}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'}, {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'}, {CTRL, CTRL}, {'a', 'A'}, {'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'}, {L_SHIFT, L_SHIFT}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, {'/', '?'}, {R_SHIFT, R_SHIFT}, {0, 0}, {0, 0}, {SPACE_BAR, SPACE_BAR}, {CAPS_LCK, CAPS_LCK}};

char buffer[BUFF_SIZE] = {0};
int buff_dim = 0;
// char *getKeyboardBuffer()
// {
//     return buffer;
// }

int shift = 0;
int capsLock = 0;

void keyboardBuffer()
{
    if (hasKeyboardKey())
    {
        int key = readKeyboard();
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