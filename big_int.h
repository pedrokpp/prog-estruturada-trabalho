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
    if (bi->length == 0) {
        d->next = d;
        d->prev = d;
        bi->head = d;
        bi->tail = d;
    } else {
        bi->tail->next = d;
        d->prev = bi->tail;
        d->next = bi->head;
        bi->tail = d;
        bi->head->prev = bi->tail;
    }
    bi->length++;
}

// Coloca um elemento no início da lista
void insert(BIG_INT* bi, int value) {
    DIGIT* d = newDigit(value);
    if (bi->length == 0) {
        d->next = d;
        d->prev = d;
        bi->head = d;
        bi->tail = d;
    } else {
        bi->tail->next = d;
        d->prev = bi->tail;
        d->next = bi->head;
        bi->head = d;
        bi->head->prev = bi->tail;
    }
    bi->length++;
}

BIG_INT* parseString(char* number) {
    BIG_INT* bi = malloc(sizeof(BIG_INT));
    for (int i = 0; i < strlen(number); i++) {
        if (!(number[i] >= '0' && number[i] <= '9'))
            return NULL;
        int num = number[i] - '0';
        append(bi, num);
        bi->length++;
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
    } while (current != bi->head);
    printf("\n");
}

void freeNumber(BIG_INT* bi) {
    if (bi) {
        DIGIT* current = bi->head;
        do {
            DIGIT* tmp = current;
            current = current->next;
            free(tmp);
        } while (current != bi->tail);
        free(bi);
    }
}
