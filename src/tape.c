#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "tape.h"


struct Tape {
    struct Node* tape;
    int head;
    int length;
};


struct Tape* createTape(int length) {
    struct Tape* tape = (struct Tape*)malloc(sizeof(struct Tape));
    tape->length = length;
    tape->head = 0;
    tape->tape = createList(length, '0');
    
    return tape;
}

char read(struct Tape* tape) {
    return getFromList(tape->tape, tape->head);
}

void write(struct Tape* tape, char val) {
    setInList(tape->tape, tape->head, val);
}

void moveLeft(struct Tape* tape) {
    if (tape->head > 0) {
        tape->head--;
    }
}

void moveRight(struct Tape* tape) {
    if (tape->head >= tape->length) {
        struct Node* newtape = createList(tape->length, '0');
        appendTwoList(tape->tape, newtape);
    }
    tape->head++;
}

void windbackTape(struct Tape* tape) {
    tape->head = 0;
}

void rewindTape(struct Tape* tape, int fixed) {
    tape->head = fixed;
}

int getHeadPosition(struct Tape* tape) {
    return tape->head;
}


void printTape(struct Tape* tape) {
    printList(tape->tape);
}
