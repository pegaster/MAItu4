#include "tapescreen.h"
#include <stdio.h>

void PrintTape(int tapeLength, int *tape, int cursorIndex, int maxUsed, int flag){
    int end = maxUsed;
    if(flag){
        end = tapeLength;
    }
     for(int i = 0; i < end; i++){
        
        if(i == cursorIndex && flag){
            printf("\x1B[42m%c\033[0m", (char)tape[i]);
        }
        else{
            printf("%c", (char)tape[i]);
        }
    }
    printf("\n");
}