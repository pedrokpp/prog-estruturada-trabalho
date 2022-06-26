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

BIG_INT* add(BIG_INT* bi1, BIG_INT* bi2) {
    BIG_INT* res = malloc(sizeof(BIG_INT));
    BIG_INT* bigger = bi1->length >= bi2->length ? bi1 : bi2;
    BIG_INT* smaller = bi2->length <= bi1->length ? bi2 : bi1;

    DIGIT* c_big = bigger->tail;
    DIGIT* c_small = smaller->tail;
    int carry = 0;

    do {
        if (!c_small) {
            insert(res, c_big->value);
        } else {
            int result = c_big->value + c_small->value + carry;
            carry = 0;
            if (result >= 10) {
                carry = floor(result / 10);
                result = result % 10;
            }
            
            insert(res, result);
            if (c_small == smaller->head)
                insert(res, carry);
        }
        
        if (c_small)
            c_small = c_small->prev == smaller->tail ? NULL : c_small->prev;
        c_big = c_big->prev;
    } while(c_big != bigger->tail);

    return res;
}

BIG_INT* sub(BIG_INT* bi1, BIG_INT* bi2) {
    BIG_INT* res = malloc(sizeof(BIG_INT));
    BIG_INT* bigger = bi1->length >= bi2->length ? bi1 : bi2;
    BIG_INT* smaller = bi2->length <= bi1->length ? bi2 : bi1;

    DIGIT* c_big = bigger->tail;
    DIGIT* c_small = smaller->tail;
    int carry = 0;

    do {
        if (!c_small) {
            if (c_big->value > 0)
                insert(res, c_big->value);
        } else {
            if (c_big->value < c_small->value) {
                DIGIT* tmp = c_big->prev;
                while (tmp != bigger->tail) {
                    if (tmp->value > 0) {
                        tmp->value--;
                        break;
                    }
                    tmp->value = 9;
                    tmp = tmp->prev;
                }
                insert(res, (10 + c_big->value) - c_small->value);
            } else {
                insert(res, c_big->value - c_small->value);
            }
        }
        
        if (c_small)
            c_small = c_small->prev == smaller->tail ? NULL : c_small->prev;
        c_big = c_big->prev;
    } while(c_big != bigger->tail);
    
    return res;
}
