#include "myio.h"
#include <stdio.h>

int FGetLine(FILE *file, char *string, int length){
    int end = 0;
    int c;
    while ((c = fgetc(file)) != '\n' && c != '\0' && length - end > 2)
    {
        string[end++] = c;
    }
    if(c == EOF){
        return 1;
    }
    string[end] = EOF;
    return 0;
}

int GetLine(char *string, int length){
    int end = 0;
    int c;
    while ((c = getchar()) != '\n' && c != EOF && length - end > 2)
    {
        string[end++] = c;
    }
    if(c == EOF){
        return 1;
    }
    string[end] = EOF;
    return 0;
}
