#include <stdio.h>
#include <stdlib.h>
#include "myio.h"
#include "parse.h"


int ParseFromFile(FILE *filePtr, int alphabetLength, int modesQuantity, Instruction ***instructionsPtr){
    int end = 0;
    char *buff = (char *)malloc(sizeof(char) * BUFF_LENGTH);
    char c;
    int *instructionsLengths = (int *)malloc(sizeof(int) * modesQuantity);
    Instruction **instructions = (Instruction **)malloc(sizeof(Instruction *) * modesQuantity);
    for(int i = 0; i < modesQuantity; i++){
        instructionsLengths[i] = alphabetLength;
        instructions[i] = (Instruction *)malloc(sizeof(Instruction) * alphabetLength);
        for(int j = 0; j < alphabetLength; j++){
            Instruction stop;
            stop.symbol = j;
            stop.action = UNDEFINED;
            instructions[i][j] = stop;
        }
    }
    int lineCount = 4;
    while(!FGetLine(filePtr, buff, BUFF_LENGTH)){
        int curMode, newMode;
        char curSymbol, newSymbol, action;
        int result = sscanf(buff, "%d, %c, %c, %d", &curMode, &curSymbol, &action, &newMode);
        if(result < 4){
            
            printf("line %d: \"%s\"parsing error, not enough params\n", lineCount, buff);
            return 0;
        }
        if(curMode < 0 || curMode > 99){
            printf("line %d: error, mode number should be in range from 0 to 99\n", lineCount);
            return 0;
        }
        if(action == '<' || action == '>' || action == '=' || action == '#'){
            newSymbol = curSymbol;
        }
        else{
            newSymbol = action;
            action = '=';
        }
        int curSymbolIndex = (int)curSymbol, newSymbolIndex = (int)newSymbol;
        instructions[curMode][curSymbolIndex].symbol = newSymbolIndex;  
        instructions[curMode][curSymbolIndex].mode = newMode;
        switch (action)
        {
        case '>':
            instructions[curMode][curSymbolIndex].action = MOVE_RIGHT;
            break;
        
        case '<':
            instructions[curMode][curSymbolIndex].action = MOVE_LEFT;
            break;

        case '=':
            instructions[curMode][curSymbolIndex].action = DO_NOTHING;
            break;
        
        case '#':
            instructions[curMode][curSymbolIndex].action = STOP;
            break;

        default:
            printf("line %d: error, unknown action \'%c\'\n", lineCount, action);
            return 0;
        }
        lineCount++;
        
    }
    
    fclose(filePtr);
    free(buff);

    *instructionsPtr = instructions;
    return 1;
}

int ParseFromTape(int tapeLength, int **tapePtr, int alphabetLength, int *cursorIndexPtr){
    int cursorIndex = 0, flag = 1;
    int *tape = (int *)malloc(sizeof(int) * tapeLength);
    char c;
    int index = -1;
    for(int i = 0; i < tapeLength; i++){
        if(flag){
            c = getchar();
            if(c == ' '){
                c = '_';
            }
            if (c == '\n' || c == EOF){
                flag = 0;
                c = '_';
            }
            if(c != '_'){
                cursorIndex = i + 1;
            }
            index = (int)c;
        }
        tape[i] = index; 
    }
    *tapePtr = tape;
    *cursorIndexPtr = cursorIndex;
    return 1;
}