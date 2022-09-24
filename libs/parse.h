#ifndef __PARSE__
#define __PARSE__
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

int ParseFromFile(FILE *filePtr, int alphabetLength, int modesQuantity, Instruction ***instructionsPtr);
int ParseFromTape(int tapeLength, int **tapePtr, int alphabetLength, int *cursorIndexPtr);

#endif