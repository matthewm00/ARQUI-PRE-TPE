#include <libC.h>
#include <stdarg.h>

int fontColor[1] = {0};
int backgroundColor[1] = {0};


static int buffSize = 0;
static char buffer[BUFF_LEN]={0};


void setFontColor(int color)
{
    *fontColor = color;
}
void setBackGroundColor(int color)
{
    *backgroundColor = color;
}

void putChar(char c)
{
    printf("%c", c);
}

char getChar()
{
    uint64_t c = 0;
    while (c == 0)
    {
        syscall(READ, c, 1, 0, 0, 0);
    }
    return (char)c;
}

// Ayuda sacada de: https://iq.opengenus.org/how-printf-and-scanf-function-works-in-c-internally/
/*
void printf(const char *format, ...) //... ya que los parametros son variables
{
    char toRet[SCREEN_WIDTH];

    va_list valist; // lista de parametros
    va_start(valist, format);

    int index = 0;

    for (int i = 0; format[i] != 0; i++)
    {
        if (format[i] == '%')
        {
            i++;
            int aux_dim = 10;
            char aux[aux_dim]; // como maximo puede tener 10 digitos el integer (arbitratio)

            int counter; // me transforma el int a un string

            char *string2;

            int j = 0;
            switch (format[i])
            {
            case 'c':
                toRet[index++] = (char)(va_arg(valist, int));
                break;

            case 'd':
                counter = numToStr(aux, va_arg(valist, int));
                if (counter > aux_dim)
                {
                    //  should throw exception //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                }
                for (int j = 0; j < counter; j++)
                {
                    toRet[index++] = aux[j];
                }
                break;

            case 's':
                string2 = (char *)va_arg(valist, char *);

                while (string2[j] != 0) // busco que termine el string a copiar
                {

                    toRet[index++] = string2[j++];
                }

                break;

            default:
                //  should throw exception //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                // changeLetterColor(0xFF0000);
                printf("Expresion %s is unsupported \n", format[i]);
                // changeLetterColor(DEFAULT_LETTER_COLOR);
                // expression not suported
                break;
            }
        }
        else // just copy the string
        {
            toRet[index++] = format[i];
        }
    }
    va_end(valist);
    toRet[index] = 0;

    syscall(WRITE, (uint64_t)toRet, index, BLACK, WHITE, 0);
}

int scanf(const char *format, ...)
{
    char usrInput[SCREEN_WIDTH];

    int index = 0;

    char in = getChar();

    while (in != '\n')
    {
        usrInput[index++] = in;
        putChar(in);

        // printf("%s|| %d",usrInput,index);
        in = getChar(); // Y espera al proximo caracter
    }
    putChar('\n');

    usrInput[index] = 0; // Pongo el 0 final del string
    index = 0;           // Reseteo el indice

    va_list valist;
    va_start(valist, format);
    int number_of_vars = 0;

    for (int i = 0; format[i] != 0; i++)
    {

        if (format[i] == '%') // es que viene un fomrato
        {
            i++;
            number_of_vars++;

            int aux_dim = 10; // chequear
            char aux[aux_dim];
            int aux_index = 0;

            char *output;
            int output_index = 0;

            switch (format[i])
            {
            case 'c':
            { // caso char
                *(char *)va_arg(valist, char *) = usrInput[index++];
                break;
            }

            case 'd':
            { // caso integer
                while (usrInput[index] == ' ')
                {
                    index++;
                }

                while (usrInput[index] != 0 && usrInput[index] != ' ')
                {

                    aux[aux_index++] = usrInput[index++]; // Me armo un arreglo de chars con el input
                }
                aux[aux_index++] = 0;

                *(int *)va_arg(valist, int *) = strToInt(aux);
                // Como "d" es un integer, paso el str a int.

                break;
            }
            case 's':
            { // caso string
                output = (char *)va_arg(valist, char *);
                while (usrInput[index] == ' ')
                {
                    index++;
                }

                while (usrInput[index] != ' ' && usrInput[index] != 0)
                {
                    output[output_index++] = usrInput[index++];
                }
                output[output_index] = 0;

                break;
            }

            default:
                // should throw exception
                // changeLetterColor(0xFF0000);
                printf("Expresion %s is unsupported \n", format[i]);
                // changeLetterColor(DEFAULT_LETTER_COLOR);
                // expression not suported
                va_end(valist); // a chequear
                return -1;
            }
        }
    }
    va_end(valist);
    return number_of_vars;
}
*/


//https://stackoverflow.com/questions/54352400/implementation-of-printf-function
void printf(char *str, ...){
    va_list args;
    
    char buff[BUFF_LEN] = {0};
    int strIdx = 0, buffIdx = 0;
    char *str_arg;
    char aux[20];
    va_start(args, str);

    while (str && str[strIdx]) {
        if (str[strIdx] == '%')
        {
            strIdx++;
            switch (str[strIdx])
            {
                case 'c':
                {
                    buff[buffIdx] = (char)va_arg(args, int);
                    buffIdx++;
                    break;
                }
                case 'd':
                {
                    intToStr(va_arg(args, int),aux,10);
                    strcpy(&buff[buffIdx], aux);
                    buffIdx += strlen(aux);
                    break;
                }
                case 'x':
                {
                    intToStr(va_arg(args, int),aux,16);
                    strcpy(&buff[buffIdx], aux);
                    buffIdx += strlen(aux);
                    break;
                }
                case 's':
                {
                    str_arg = (char *)va_arg(args, char *);
                    strcpy(&buff[buffIdx], str_arg);
                    buffIdx += strlen(str_arg);
                    break;
                }
                case '%':
                {
                    strcpy(&buff[buffIdx], "%");
                    buffIdx++;
                    break;
                }
            }
         } else {
            buff[buffIdx] = str[strIdx];
            buffIdx++;
        }
        strIdx++;
    }

    // _syscall(SYS_WRITE_ID, (uint64_t)buff, buffIdx, currentBGC, currentFTC, 0);
    syscall(WRITE, (uint64_t)buff, buffIdx, BLACK, WHITE, 0);
    va_end(args);
    return ;
}

//funcion encargada a actualizar el buffer de la shell y de imprimir en pantalla el char en cuestion
int readText(){
    int c;
    while((c=getChar()) !='\n'){
        
        if(c!=-1){
            if(buffSize < BUFF_LEN-1){
                buffer[buffSize++]=c;
            }else{
                if(c=='\b'){
                    buffSize-=2;
                }
                putChar(c);
            }
        }
    }
    putChar('\n');
    buffer[buffSize++]='\0';
    return buffSize++;
}

//https://www.geeksforgeeks.org/write-your-own-atoi/
int strToInt2(char* str, int * size)
{
    *size = 0;
    // Initialize result
    int res = 0;
 
    // Initialize sign as positive
    int sign = 1;
 
    // Initialize index of first digit
    int i = 0;
 
    // If number is negative,
    // then update sign
    if (str[0] == '-') {
        sign = -1;
        *size += 1;
        // Also update index of first digit
        i++;
    }
 
    // Iterate through all digits
    // and update the result
    for (; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9')
             return res;
        res = res * 10 + str[i] - '0';
        *size += 1;
    }
        
 
    // Return result with sign
    return sign * res;
}

// inspirado en https://iq.opengenus.org/how-printf-and-scanf-function-works-in-c-internally/
int scanf(char * str, ...)
{
    buffSize = 0;
    va_list vl;
    int i = 0, j = 0;
    int sizeNum = 0;
 	va_start( vl, str );
    char *str_arg;
    readText();

 	while (str && str[i] && buffer[j])
 	{
 	    if (str[i] == '%') 
 	    {
 	       i++;
 	       switch (str[i]) 
 	       {
 	            case 'c': 
 	            {
	 	            *(char *)va_arg( vl, char* ) = buffer[j];
	 	            j++;
	 	            break;
 	            }
 	            case 'd': 
 	            {
	 	            *(int *)va_arg( vl, int* ) = strToInt2(&buffer[j], &sizeNum);
	 	            j+=sizeNum;
	 	            break;
 	            }
                case 's':
                { 
                    str_arg = (char *)va_arg(vl, char *);
                    strcpy(str_arg, &buffer[j]);
                    j += strlen(str_arg);      
                    break;
                }
                
 	        }
 	    } 
 	    else 
 	    {
 	        buffer[j] =str[i];
            j++;
        }
        i++;
    }
    va_end(vl);
    return j;
}