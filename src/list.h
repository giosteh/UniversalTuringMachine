#ifndef LIST_H
#define LIST_H


struct Node* createList(int len, char val);


int isListEmpty(struct Node* head);

int getListLength(struct Node* head);

char getFromList(struct Node* head, int index);

void addToList(struct Node* head, int index, char val);

void removeFromList(struct Node* head, int index);

void setInList(struct Node* head, int index, char val);

void appendInList(struct Node* head, char val);


void appendTwoList(struct Node* head1, struct Node* head2);


void printList(struct Node* head);



#endif