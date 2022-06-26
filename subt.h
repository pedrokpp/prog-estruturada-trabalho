#pragma once
#include "big_int.h"

BIG_INT* subt(BIG_INT* bi1, BIG_INT* bi2) {
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
                free(tmp);
                insert(res, (10 + c_big->value) - c_small->value);
            } else {
                insert(res, c_big->value - c_small->value);
            }
        }
        
        if (c_small)
            c_small = c_small->prev == smaller->tail ? NULL : c_small->prev;
        c_big = c_big->prev;
    } while(c_big != bigger->tail);
    
    freeNumber(bigger);
    freeNumber(smaller);

    return res;
}
