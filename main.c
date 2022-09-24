// Created by Steve Dneprov for Moscow Aviation Institute
// In 2022
// steve.dneprov@gmail.com
#include <stdio.h>
#include <stdlib.h>
#include "libs/myio.h"
#include "libs/structs.h"
#include "libs/parse.h"
#include "libs/logic.h"
#include "libs/tapescreen.h"
#define MOVE_RIGHT 1
#define MOV_LEFT 0
#define DO_NOTHING 2
#define STOP 3

#define ALPHABET_LENGTH 256
#define TAPE_LENGTH 80
#define MODES_QUANTITY 100

int main(int argc, char **argv){
    if(argc < 2){
        printf("No file to intereptate\n");
        return 0;
    }
    int debug = 0;
    char *fileName, *flag, format[] = ".tu4";
    if(argc == 3){
        if(argv[1][0] == '-'){
            flag = argv[1];
            fileName = argv[2];
        }
        else if(argv[2][0] == '-'){
            flag = argv[2];
            fileName = argv[1];
        }
        else{
            printf("Error\n");
            return 0;
        }
        if(flag[1] == 'd' && flag[2] == 0){
            debug = 1;
        }
        else if(flag[1] == 'b' && flag[2] == 0){
            debug = 2;
        }
        else{
            printf("Unknown flag %s\n", flag);
        }
    }
    else if(argc == 2){
        fileName = argv[1];
    }
    else{
        printf("Wrong use\n");
        return 0;
    }
    
    FILE *filePtr = fopen(fileName, "r");
    if(filePtr == NULL){
        printf("No such file or directory \"%s\"\n", fileName);
        return 0;
    }
    
    
    
    int cursorIndex, maxUsed, mode = 0;
    int *tape;
    Instruction **instructions;
    if(!ParseFromFile(filePtr, ALPHABET_LENGTH, MODES_QUANTITY, &instructions)){
        return 0;
    }
    if(!ParseFromTape(TAPE_LENGTH, &tape, ALPHABET_LENGTH, &cursorIndex)){
        return 0;
    }
    if(debug){
        printf("cursor index: %d, mode: %d\n", cursorIndex, mode);
        PrintTape(TAPE_LENGTH, tape, cursorIndex, maxUsed, 1);
        printf("\n");
        if(debug == 2){
            int c = getchar();
            printf("%c\n", c);
            if(c == 'd'){
                debug = 1;
            }
            else if(c == 'f'){
                debug = 0;
            }
        }
    }
    maxUsed = cursorIndex;
    int res;
    while((res = Execute(tape, TAPE_LENGTH, &cursorIndex, &maxUsed, ALPHABET_LENGTH, MODES_QUANTITY, instructions, &mode)) > 0){
        if(debug){
            printf("cursor index: %d, mode: %d\n", cursorIndex, mode);
            PrintTape(TAPE_LENGTH, tape, cursorIndex, maxUsed, 1);
            printf("\n");
            if(debug == 2){
                int c = getchar();
                if(c == 'd'){
                    debug = 1;
                }
            }
        }
    }
    if(res < 0){
        return 0;
    }
    if(debug){
        printf("cursor index: %d, mode: %d\n", cursorIndex, mode);
    }
    PrintTape(TAPE_LENGTH, tape, cursorIndex, maxUsed, debug);
    for(int i = 0; i < MODES_QUANTITY; i++){
        free(instructions[i]);
    }
    free(instructions);
    free(tape);
    return 0;
}
