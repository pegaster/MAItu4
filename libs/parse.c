#include <stdio.h>
#include <stdlib.h>
#include "myio.h"
#include "parse.h"


int ParseFromFile(FILE *filePtr, int *alphabetLengthPtr, char **alphabetPtr, int *modesQuantityPtr, Instruction ***instructionsPtr, int **instructionsLengthsPtr){
    int alphabetLength = 1, modesQuantity, end = 0;
    char *buff = (char *)malloc(sizeof(char) * BUFF_LENGTH);
    char c;
    char *alphabet = (char *)malloc(sizeof(char) * alphabetLength);
    alphabet[0] = '_';
    modesQuantity = 100;
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
        int flag = 3;
        int oldLength = instructionsLengths[curMode];
        int curSymbolIndex, newSymbolIndex;
        for(int i = 0; i < alphabetLength; i++){
            if(alphabet[i] == curSymbol){
                flag -= 2;
                curSymbolIndex = i;
            }
            if(alphabet[i] == newSymbol){
                flag -= 1;
                newSymbolIndex = i;
            }
            if(flag == 0){
                break;
            }
        }
        if(flag){
            
            if(flag == 1 || flag == 3){
                alphabet = (char *)realloc(alphabet, sizeof(char) * (alphabetLength + 1));
                alphabetLength += 1;
                alphabet[alphabetLength - 1] = curSymbol;
                if(curSymbol == newSymbol){
                    newSymbolIndex = alphabetLength - 1;
                    flag = 1;
                }
                curSymbolIndex = alphabetLength - 1;
            }
            if(flag == 2 || flag == 3){
                alphabet = (char *)realloc(alphabet, sizeof(char) * (alphabetLength + 1));
                alphabetLength += 1;
                alphabet[alphabetLength - 1] = newSymbol;
                newSymbolIndex = alphabetLength - 1;
            }
            
        }
        if(curSymbolIndex >= oldLength || newSymbolIndex >= oldLength){
            instructions[curMode] = (Instruction *)realloc(instructions[curMode], alphabetLength);
            for(int i = oldLength; i < alphabetLength; i++){
                Instruction stop;
                stop.symbol = i;
                stop.action = UNDEFINED;
                instructions[curMode][i] = stop;
            }
            instructionsLengths[curMode] = alphabetLength;
            
        }
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
    *instructionsLengthsPtr = instructionsLengths;
    *alphabetLengthPtr = alphabetLength;
    *alphabetPtr = alphabet;
    *modesQuantityPtr = modesQuantity;
    *instructionsPtr = instructions;
    return 1;
}

int ParseFromTape(int *tapeLengthPtr, int **tapePtr, int alphabetLength, char *alphabet, int *cursorIndexPtr){
    int tapeLength = 80, cursorIndex, flag = 1;
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

            for(int j = 0; j < alphabetLength; j++){
                if(alphabet[j] == c){
                    index = j;
                    break;
                }
            }
            if(index < 0){
                printf("symbol \'%c\' is not used in programm\n", c);
                return 0;
            }
        }
        tape[i] = index; 
    }
    scanf("%d", &cursorIndex);
    *tapeLengthPtr = tapeLength;
    *tapePtr = tape;
    *cursorIndexPtr = cursorIndex;
    return 1;
}