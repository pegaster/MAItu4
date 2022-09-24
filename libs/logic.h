#ifndef __LOGIC__
#define __LOGIC__
#include "structs.h"

int Execute(int *tape, int tapeLength, int *cursorIndexPtr, int *maxUsedPtr, int alphabetLength, int modesQuantity, Instruction **instructions, int *modePtr);

#endif