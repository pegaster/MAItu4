#ifndef __LOGIC__
#define __LOGIC__
#include "structs.h"

int Execute(int *tape, int tapeLength, int *cursorIndexPtr, int *maxUsedPtr, int alphabetLength, char *alphabet, int modesQuantity, Instruction **instructions, int *instrucionsLengths, int *modePtr);

#endif