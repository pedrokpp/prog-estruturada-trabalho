#pragma once
#include "big_int.h"

BIG_INT* soma(BIG_INT* bi1, BIG_INT* bi2) {
    BIG_INT* res = malloc(sizeof(BIG_INT));
    BIG_INT* bigger = bi1->length >= bi2->length ? bi1 : bi2;
    BIG_INT* smaller = bi2->length <= bi1->length ? bi2 : bi1;

    DIGIT* c_big = bigger->tail;
    DIGIT* c_small = smaller->tail;
    int carry = 0;
    
    do {
        if (!c_small) {
            if (carry > 0) {
                int result = c_big->value + carry;  
                carry = 0;
                if (result >= 10) {
                    carry = floor(result / 10);
                    result = result % 10;
                }
                insert(res, result);
                if (!c_big->prev && carry != 0)
                    insert(res, carry);
            } else {
                if (c_big->value != 0)
                    insert(res, c_big->value);
            }
        } else {
            int result = c_big->value + c_small->value + carry;
            carry = 0;
            if (result >= 10) {
                carry = floor(result / 10);
                result = result % 10;
            }
            insert(res, result);
            if (!c_small->prev && !c_big->prev && carry != 0)
                insert(res, carry);
        }
        
        if (c_small)
            c_small = c_small->prev;
        c_big = c_big->prev;
    } while(c_big);
        

    /*
    printNumber(bigger);
    printf("+\n");
    printNumber(smaller);
    printf("---------\n");
    printNumber(res);
    printf("bigger length: %d\n", bigger->length);
    printf("smaller length: %d\n", smaller->length);
    printf("res length: %d\n", res->length);
    //printf("bigger addr: %p\n", bigger);
    //printf("smaller addr: %p\n", smaller);
    printf("\n\n");
    */

    /* // debug
    if(bi1->tail == NULL) {
        printf("SOMA: %d + NULL! = | bi1->tail address: %p | bi2->tail address: %p\n", bi2->tail->value, bi1->tail, bi2->tail);
    } else {
        printf("SOMA: %d + %d = | bi1->tail address: %p | bi2->tail address: %p\n", bi1->tail->value, bi2->tail->value, bi1->tail, bi2->tail);
    }
    */

    return res;
}
