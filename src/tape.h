#ifndef TAPE_H
#define TAPE_H


struct Tape* createTape(int len);


char read(struct Tape* tape);

void write(struct Tape* tape, char val);

void moveLeft(struct Tape* tape);

void moveRight(struct Tape* tape);

void windbackTape(struct Tape* tape);

void rewindTape(struct Tape* tape, int fixed);

int getHeadPosition(struct Tape* tape);


void printTape(struct Tape* tape);


#endif