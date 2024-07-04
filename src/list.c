#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct Node {
    char val;
    struct Node *prev;
    struct Node *next;
};

struct Node *createList(int length, char fillValue) {
    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    head->prev = NULL;
    
    if (length == 0) {
        head->next = NULL;
        return head;
    }
    
    if (length > 0) {
        struct Node *node = (struct Node *)malloc(sizeof(struct Node));
        head->next = node;
        node->prev = head;
        node->val = fillValue;
        
        if (length > 1) {
            for (int i = 0; i < length; i++) {
                struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
                newnode->val = fillValue;
                newnode->prev = node;
                node->next = newnode;
                node = newnode;
            }
        }
        node->next = NULL;
        return head;
    }
    return NULL;
}

int isListEmpty(struct Node *head) {
    return (head->next == NULL);
}

int getListLength(struct Node *head) {
    int length = 0;
    struct Node *node = head;
    
    while (node->next != NULL) {
        length++;
        node = node->next;
    }
    return length;
}

char getFromList(struct Node *head, int index) {
    if (index >= getListLength(head)) {
        return '\n';
    }
    
    struct Node *node = head->next;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->val;
}

void addToList(struct Node *head, int index, char value) {
    int length = getListLength(head);
    if (index > length) {
        return;
    }
    
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    struct Node *prev = head;
    struct Node *next = prev->next;
    newnode->val = value;
    
    for (int i = 0; i < index; i++) {
        prev = next;
        next = prev->next;
    }
    if (index < length) {
        next->prev = newnode;
    }
    prev->next = newnode;
    newnode->prev = prev;
    newnode->next = next;
}

void removeFromList(struct Node *head, int index) {
    int length = getListLength(head) - 1;
    if (index > length) {
        return;
    }
    
    struct Node *prev = head;
    struct Node *node = prev->next;
    struct Node *next = node->next;
    
    if (index > 0) {
        for (int i = 0; i < index; i++) {
            prev = node;
            node = next;
            next = node->next;
        }
    }
    if (index < length) {
        next->prev = prev;
    }
    prev->next = next;
    free(node);
}

void setInList(struct Node *head, int index, char value) {
    int length = getListLength(head) - 1;
    if (index > length) {
        return;
    }
    
    struct Node *node = head->next;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    node->val = value;
}

void appendInList(struct Node *head, char value) {
    int length = getListLength(head);
    addToList(head, length, value);
}

void appendTwoList(struct Node *head1, struct Node *head2) {
    struct Node *node1 = head1->next;
    while (node1->next != NULL) {
        node1 = node1->next;
    }
    struct Node *node2 = head2->next;
    node1->next = node2;
    node2->prev = node1;
}

void printList(struct Node *head) {
    struct Node *node = head->next;
    while (node != NULL) {
        printf("%c", node->val);
        node = node->next;
    }
    printf("\n");
}
