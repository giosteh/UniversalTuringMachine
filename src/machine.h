#ifndef MACHINE_H
#define MACHINE_H

#include <stdio.h>


enum Direction {
    NONE, INERT, RIGHT, LEFT
};


struct Machine* instantiateMachine(FILE* obj);


void prepare(struct Machine* machine);

int isSameState(struct Machine* machine, struct Tape* tapex, struct Tape* tapey);

int isSameSymbol(struct Machine* machine);

void goToNextInstruction(struct Machine* machine);

void writeSymbol(struct Machine* machine);

void changeState(struct Machine* machine);

enum Direction readDirection(struct Machine* machine);

void moveHead(struct Machine* machine, enum Direction direction);

int runMachine(struct Machine* machine);


void seeResultingMachine(struct Machine* machine);


#endif