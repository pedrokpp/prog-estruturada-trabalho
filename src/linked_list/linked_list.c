#include "linked_list.h"

NODE* newNode(int value) {
    NODE* node = malloc(sizeof(NODE));
    node->value = value;
    node->next = NULL;
    return node;
}

void insertLast(LLIST* ll, int value) {
    NODE* current = ll->head;
    NODE* last = NULL;
    NODE* node = newNode(value);
    while (current) {
        last = current;
        current = current->next;
    }
    last->next = node;
}

void insertFirst(LLIST* ll, int value) {
    NODE* node = newNode(value);
    node->next = ll->head;
    ll->head = node;
}

int pop(LLIST* ll, int value) {
    int res = 0;
    NODE* last = NULL;
    NODE* current = ll->head;
    while (current) { // TODO checar ocorrências?
        if (current->value == value) {
            if (last)
                last->next = current->next;
            else
                ll->head = current->next;
            res++;
        }
        last = current;
        current = current->next;
    }
    return res;
}

NODE* find(LLIST* ll, int value) {
    NODE* current = ll->head;
    while (current) { // TODO checar ocorrências?
        if (current->value == value)
            return current;
        current = current->next;
    }
    return NULL;
}

void printLL(LLIST* ll) {
    NODE* current = ll->head;
    while (current) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}
