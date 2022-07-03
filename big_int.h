#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node {
    int value;
    struct node* next;
    struct node* prev;
} DIGIT;

DIGIT* newDigit(int value) {
    DIGIT* d = malloc(sizeof(DIGIT));
    d->value = value;
    return d;
}

typedef struct BIG_INT {
    int length;
    DIGIT* head;
    DIGIT* tail;
} BIG_INT;

// Coloca um elemento no final da lista
void append(BIG_INT* bi, int value) {
    DIGIT* d = newDigit(value);
    d->prev = bi->tail;
    if (bi->tail != NULL)
        bi->tail->next = d;
    bi->tail = d;

    if (bi->length == 0)
        bi->head = bi->tail;

    bi->length++;
}

// Coloca um elemento no início da lista
void insert(BIG_INT* bi, int value) {
    //printf("[DEBUG] inserindo %d na lista\n", value);
    DIGIT* d = newDigit(value);
    d->next = bi->head;
    if (bi->head != NULL) 
        bi->head->prev = d;
    bi->head = d;

    if (bi->length == 0)
        bi->tail = bi->head;

    bi->length++;
}

BIG_INT* parseString(char* number) {
    BIG_INT* bi = malloc(sizeof(BIG_INT));
    for (int i = 0; i < (int)strlen(number); i++) {
        if (!(number[i] >= '0' && number[i] <= '9'))
            return NULL;
        int num = number[i] - '0';
        append(bi, num);
    }
    return bi;
}

void printNumber(BIG_INT* bi) {
    DIGIT* current = bi->head;
    if (!current) {
        printf("Número vazio\n");
        return;
    }

    do {
       printf("%d", current->value); 
       current = current->next;
    } while (current);
    printf("\n");
}

void freeNumber(BIG_INT* bi) {
    if (bi) {
        DIGIT* current = bi->head;
        do {
            DIGIT* tmp = current;
            current = current->next;
            free(tmp);
        } while (current);
        free(bi);
    }
}
