#include <stdio.h>
#include <stdlib.h>

#include "tape.h"
#include "machine.h"


struct Machine {
    struct Tape* tape1;
    struct Tape* tape2;
    struct Tape* tape3;
    struct Tape* tape4;
    int wordLength;
};


struct Machine* instantiateMachine(FILE* obj) {
    if (obj == NULL) {
        return NULL;
    }
    
    struct Tape* tape1 = createTape(8*128);
    struct Tape* tape2 = createTape(8*64);
    struct Tape* tape3 = createTape(8*2);
    struct Tape* tape4 = createTape(8*2);
    int curr;
    char val;
    
    while ((curr = fgetc(obj)) != 'f') {
        val = (char)curr;
        write(tape1, val);
        moveRight(tape1);
    }
    while ((curr = fgetc(obj)) != EOF) {
        val = (char)curr;
        write(tape2, val);
        moveRight(tape2);
    }
    
    windbackTape(tape1);
    windbackTape(tape2);
    fclose(obj);
    
    struct Machine* machine = (struct Machine*)malloc(sizeof(struct Machine));
    machine->tape1 = tape1;
    machine->tape2 = tape2;
    machine->tape3 = tape3;
    machine->tape4 = tape4;
    machine->wordLength = 8;
    
    return machine;
}

void prepare(struct Machine* machine) {
    char val;
    while ((val = read(machine->tape1)) != '-') {
        write(machine->tape3, val);
        moveRight(machine->tape1);
        moveRight(machine->tape3);
    }
    moveRight(machine->tape1);
    
    while ((val = read(machine->tape1)) != '+') {
        write(machine->tape4, val);
        moveRight(machine->tape1);
        moveRight(machine->tape4);
    }
    
    moveRight(machine->tape1);
    windbackTape(machine->tape3);
    windbackTape(machine->tape4);
}

/* isSameState: check if the state on tapex is the same as the one on tapey */
int isSameState(struct Machine* machine, struct Tape* tapex, struct Tape* tapey) {
    int valid = 1;
    windbackTape(tapey);
    
    for (int i = 0; (i < machine->wordLength) && valid; i++) {
        if (read(tapex) != read(tapey)) {
            valid = 0;
        }
        moveRight(tapex);
        moveRight(tapey);
    }
    
    windbackTape(tapey);
    return valid;
}

/* isSameSymbol: check if the symbol read on tape2 is the same as the one in the current inspected instruction */
int isSameSymbol(struct Machine* machine) {
    int valid = 1, pos;
    for (int i = 0; i < machine->wordLength; i++) {
        if (read(machine->tape1) != read(machine->tape2)) {
            valid = 0;
        }
        moveRight(machine->tape1);
        moveRight(machine->tape2);
    }
    
    pos = getHeadPosition(machine->tape2);
    rewindTape(machine->tape2, pos - machine->wordLength);
    return valid;
}

/* goToNextInstruction: move tape1 on to the next instruction to inspect */
void goToNextInstruction(struct Machine* machine) {
    while (read(machine->tape1) != '+') {
        moveRight(machine->tape1);
    }
    moveRight(machine->tape1);
}

/* writeSymbol: copy the symbol read in the correct instruction on tape2 */
void writeSymbol(struct Machine* machine) {
    int pos;
    for (int i = 0; i < machine->wordLength; i++) {
        write(machine->tape2, read(machine->tape1));
        moveRight(machine->tape1);
        moveRight(machine->tape2);
    }
    
    moveRight(machine->tape1);
    pos = getHeadPosition(machine->tape2);
    rewindTape(machine->tape2, pos - machine->wordLength);
}

/* changeState: update the current state copying the one read in the corrent instruction on tape3 */
void changeState(struct Machine* machine) {
    windbackTape(machine->tape3);
    for (int i = 0; i < machine->wordLength; i++) {
        write(machine->tape3, read(machine->tape1));
        moveRight(machine->tape1);
        moveRight(machine->tape3);
    }
    moveRight(machine->tape1);
}

/* readDirection: read and interpret the direction where to move the head of tape2 */
enum Direction readDirection(struct Machine* machine) {
    int direction = 0;
    for (int i = 0; i < machine->wordLength; i++) {
        if (read(machine->tape1) == '1') {
            direction++;
        }
        moveRight(machine->tape1);
    }
    return direction;
}

/* moveHead: move the head of tape2 considering the direction */
void moveHead(struct Machine* machine, enum Direction direction) {
    if (direction == INERT) {
        return;
    }
    
    int pos = getHeadPosition(machine->tape2);
    if (direction == RIGHT) {
        rewindTape(machine->tape2, pos + machine->wordLength);
    } else {
        rewindTape(machine->tape2, pos - machine->wordLength);
    }
}

/* isLastInstruction: check if symbol on tape1 is blank */
int isLastInstruction(struct Machine* machine) {
    int valid = 1, pos;
    for (int i = 0; i < machine->wordLength; i++) {
        if (read(machine->tape1) != '0') {
            valid = 0;
        }
        moveRight(machine->tape1);
    }
    
    pos = getHeadPosition(machine->tape1);
    rewindTape(machine->tape1, pos - machine->wordLength);
    return valid;
}

/* runMachine: does execute the given machine */
int runMachine(struct Machine* machine) {
    int status = 0;
    prepare(machine);
    
    while (1) {
        if (!isSameState(machine, machine->tape1, machine->tape3)) {
            goToNextInstruction(machine);
            if (isLastInstruction(machine)) {
                status = isSameState(machine, machine->tape3, machine->tape4);
                break;
            }
            continue;
        }
        
        moveRight(machine->tape1);
        if (!isSameSymbol(machine)) {
            goToNextInstruction(machine);
            if (isLastInstruction(machine)) {
                break;
            }
            continue;
        }
        
        moveRight(machine->tape1);
        writeSymbol(machine);
        changeState(machine);
        moveHead(machine, readDirection(machine));
        rewindTape(machine->tape1, machine->wordLength * 2 + 2);
    }
    return status;
}


void seeResultingMachine(struct Machine* machine) {
    printf("Machine state:\n");
    printf("\nOutput>\n");
    printTape(machine->tape2);
}
