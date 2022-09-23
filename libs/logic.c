#include "logic.h"
#include <stdio.h>

int Execute(int *tape, int tapeLength, int *cursorIndexPtr, int *maxUsedPtr, int alphabetLength, char *alphabet, int modesQuantity, Instruction **instructions, int *instrucionsLengths, int *modePtr){
    int cursorIndex = *cursorIndexPtr;
    int maxUsed = *maxUsedPtr;
    int mode = *modePtr;
    if(tape[cursorIndex] >= instrucionsLengths[mode]){
        printf("\'%c\' symbol is not declared for mode %d\n", alphabet[tape[cursorIndex]], mode);
        return -1;
    }
    Instruction curInstruction = instructions[mode][tape[cursorIndex]];
    if(curInstruction.action != STOP){
        mode = curInstruction.mode;
    }
    tape[cursorIndex] = curInstruction.symbol;
    switch (curInstruction.action)
    {
    case MOVE_RIGHT:
        cursorIndex += 1;
        cursorIndex %= tapeLength;
        break;
    case MOVE_LEFT:
        cursorIndex -= 1;
        if(cursorIndex < 0){
            cursorIndex = tapeLength - 1;
        }
        break;
    case STOP:
        return 0;
    case UNDEFINED:
        printf("\'%c\' symbol is not declared for mode %d\n", alphabet[tape[cursorIndex]], mode);
        return -1;
    default:
        break;
    }
    if(cursorIndex > maxUsed){
        maxUsed = cursorIndex;
    }
    *cursorIndexPtr = cursorIndex;
    *maxUsedPtr = maxUsed;
    *modePtr = mode;
    
    return 1;
}