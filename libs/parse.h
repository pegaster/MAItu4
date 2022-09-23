#ifndef __PARSE__
#define __PARSE__
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

int ParseFromFile(FILE *filePtr, int *alphabetLengthPtr, char **alphabetPtr, int *modesQuantityPtr, Instruction ***instructionsPtr, int **instructionsLengthsPtr);
int ParseFromTape(int *tapeLengthPtr, int **tapePtr, int alphabetLength, char *alphabet, int *cursorIndexPtr);

#endif