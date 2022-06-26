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
    printf("cc");
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

int intArraySum(int _array[]) {
    int ret = 0;
    for(int i = 0; i < sizeof(_array)/4; i++) {
        printf(">>>> %d\n", _array[i]);
        ret += _array[i];
    }
    return ret;
}

BIG_INT* getHigher(BIG_INT *b1, BIG_INT *b2) {
    if(b1->length > b2->length) {
        return b1;
    }
    if(b2->length > b1->length) {
        return b2;
    }

    // equal
    DIGIT *c1 = b1->head;
    DIGIT *c2 = b2->head;
    
    for(int i = 0; i < b1->length ; i++) {
        if(c1->value > c2->value) {
            return b1;
        }
        if(c1->value < c2->value) {
            return b2;
        }

        c1 = c1->next;
        c2 = c2->next;
    }
}

BIG_INT* getLower(BIG_INT *b1, BIG_INT *b2) {
    if(b1->length > b2->length) {
        return b1;
    }
    if(b2->length > b1->length) {
        return b2;
    }

    // equal
    DIGIT *c1 = b1->head;
    DIGIT *c2 = b2->head;
    
    for(int i = 0; i < b1->length ; i++) {
        if(c1->value > c2->value) {
            return b2;
        }
        if(c1->value < c2->value) {
            return b1;
        }

        c1 = c1->next;
        c2 = c2->next;
    }
}

void mult(BIG_INT* big1, BIG_INT* big2) {
    DIGIT* current1 = big1->tail;
    DIGIT* current2 = big2->tail;
    printf("aa\n");
    int lowFactor = 0; int upFactor = 0;
    int thisMultRes = 0;

    int partialResultCache[1024];
    int resultCache[1024];
    int resultCacheIdx = 0;
    int partialResultCacheIdx = 0;
    int iteratedLevel = 0;
    char tempStringBuffer0[1024];
    char tempStringBuffer1[1024];

    do {
        lowFactor = thisMultRes = current1->value * current2->value;

        if(upFactor > 0) {
            thisMultRes += upFactor;
            lowFactor += upFactor;
            upFactor = 0;
        }

        if(thisMultRes >= 10) {
            upFactor = floor(thisMultRes / 10);
            //lowfactor = current1 == big1->head ? thisMultRes : thisMultRes % 10;
            lowFactor = thisMultRes % 10;
            //printf("current: %d | big1->head: %d\n\n", current1, big1->head);
            if(current1 == big1->head) {
                lowFactor = thisMultRes;
            } else {
                lowFactor = thisMultRes % 10;
            }
        }

        partialResultCache[partialResultCacheIdx] = lowFactor;
        partialResultCacheIdx++;

        printf("%d * %d = %d | lowFactor = %d | upFactor = %d | Inserindo %d na resposta\n", current1->value, current2->value, thisMultRes, lowFactor, upFactor, lowFactor);
        current1 = current1->prev;
        if(current1 == big1->tail) { // iterou o elemento 1 inteiro
            int sizeOrder = 1;
            
            if(partialResultCacheIdx == 0) { // caso so tenha 1 item no partialResultCache
                resultCache[resultCacheIdx] = partialResultCache[partialResultCacheIdx] * sizeOrder;
            } else {
                memset(tempStringBuffer0, 0, sizeof(tempStringBuffer0));

                //printf("partialResultCache = [%d, %d, %d] | partialResultCacheIdx = %d\n", partialResultCache[0], partialResultCache[1], partialResultCache[2], partialResultCacheIdx);
                for(int i = partialResultCacheIdx - 1; i >= 0; i--) {
                    //printf("tempRes += %d * %d * %d\n", partialResultCache[i], sizeOrder);

                    sprintf(tempStringBuffer1,"%d",partialResultCache[i]);
                    strcat(tempStringBuffer0, tempStringBuffer1);
                    memset(tempStringBuffer1, 0, sizeof(tempStringBuffer1)); // cleaning buffer after usage
                    
                    sizeOrder *= 10;
                }

                resultCache[resultCacheIdx] = atoi(tempStringBuffer0) * pow(10, iteratedLevel);
            }

            partialResultCacheIdx = 0;
            resultCacheIdx += 1;
            iteratedLevel += 1;

            current2 = current2->next; // avance para o proximo
        }
        if(current1 == big1->tail && current2 == big2->tail) {
            break;
        }
    } while(1);

    //printf("%d %d\n", resultCache[0], resultCache[1]);

    printf("Final res: %d\n", intArraySum(resultCache));
}
