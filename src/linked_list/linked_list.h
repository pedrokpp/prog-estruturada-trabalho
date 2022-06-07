#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
} NODE;

NODE* newNode(int value);

typedef struct llist {
    int length;
    NODE* head;
} LLIST;

void insertLast(LLIST* ll, int value);
void insertFirst(LLIST* ll, int value);
int pop(LLIST* ll, int value);
NODE* find(LLIST* ll, int value);
void printLL(LLIST* ll);
