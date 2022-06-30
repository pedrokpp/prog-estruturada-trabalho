#pragma once
#include "big_int.h"

BIG_INT* soma(BIG_INT* bi1, BIG_INT* bi2) {
    BIG_INT* res = malloc(sizeof(BIG_INT));
    BIG_INT* bigger = bi1->length >= bi2->length ? bi1 : bi2;
    BIG_INT* smaller = bi2->length <= bi1->length ? bi2 : bi1;

    DIGIT* c_big = bigger->tail;
    DIGIT* c_small = smaller->tail;
    int carry = 0;

    if (bigger->head->value == 0) {
        return smaller;
    }
    else if (smaller->head->value == 0) {
        return bigger;
    }
    

    do {
        if (!c_small) {
            if (c_big->value != 0)
                insert(res, c_big->value);
        } else {
            int result = c_big->value + c_small->value + carry;
            carry = 0;
            if (result >= 10) {
                carry = floor(result / 10);
                result = result % 10;
            }
            
            insert(res, result);
            if (c_small == smaller->head && c_small->value != 0 && carry != 0)
                insert(res, carry);
        }
        
        if (c_small)
            c_small = c_small->prev;
        c_big = c_big->prev;
    } while(c_big);

    return res;
}
