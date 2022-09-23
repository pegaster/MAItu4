#ifndef __STRUCTS__
#define __STRUCTS__

#define MOVE_RIGHT 1
#define MOVE_LEFT 0
#define DO_NOTHING 2
#define STOP 3
#define UNDEFINED 4
#define BUFF_LENGTH 200

typedef struct Instruction
{
    int symbol;
    int action;
    int mode;
} Instruction;

#endif