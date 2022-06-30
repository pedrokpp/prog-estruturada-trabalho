
#include "big_int.h"
#include "soma.h"

int intArraySum(int _array[], int _arrayMax) {
    int ret = 0;
    for(int i = 0; i < _arrayMax; i++) {
        printf("_array[%d] = %d\n", i, _array[i]);
        ret += _array[i];
    }
    return ret;
}

int bigIntArraySum(BIG_INT *_array[]) {
    int ret = 0;
    for(int i = 0; i < sizeof(_array); i++) {
        ret += _array[i];
    }
    return ret;
}

void dumpBigIntArray(BIG_INT *_array) {
    for(int i = 0; i < sizeof(_array); i++) {
        DIGIT *tmp = _array[i].head;
        printf("_array[%d].head = %s\n", i, tmp->value);
    }
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

char *itoa(int num) {
    char strRet[1024];
    sprintf(strRet, "%d", num);
    return strRet;
}

void mult(BIG_INT* big1, BIG_INT* big2) {
    DIGIT* current1 = big1->tail;
    DIGIT* current2 = big2->tail;
    BIG_INT *res = malloc(sizeof(BIG_INT));
    BIG_INT *tempRes = malloc(sizeof(BIG_INT));
    int lowFactor = 0; int upFactor = 0;
    int thisMultRes = 0;

    int resultCache[1024];
    int resultCacheIdx = 0;
    int iteratedLevel = 1; int iteratedLevel2 = 0;
    int casaLevel = 1;
    int casaLevel2 = 0;

    do {
        //printf("c1->value: %d |\n", current1->value);
        //printf("c2->value: %d |\n", current2->value);
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

        resultCache[resultCacheIdx] = lowFactor * casaLevel * iteratedLevel; /* metodo antigo: nao aplicavel a big int's */
        printf("ON-EXEC: _array[%d] = %d * %d * %d\n", resultCacheIdx, lowFactor, casaLevel, iteratedLevel);

        printf(">> insert %d\n", lowFactor);
        insert(tempRes, lowFactor);

        for(int i = 0; i < iteratedLevel2; i++) {
            printf(">> append 0, iteratedLevel2: %d\n", iteratedLevel2);
            append(tempRes, 0);
        }

        casaLevel *= 10;
        resultCacheIdx++;

        //printf("%d * %d = %d | lowFactor = %d | upFactor = %d | Inserindo %d na resposta\n", current1->value, current2->value, thisMultRes, lowFactor, upFactor, lowFactor);
        current1 = current1->prev;
        //printf("current1: %lx | big1->tail: %lx | current2: %lx | big2->tail: %lx | current2->prev: %lx\n", current1, big1->tail, current2, big2->tail, current2->prev);
        if( current1 == NULL && (current2 == NULL/* || current2->prev == NULL*/) ) {
            printf("break 1\n");
            break;
        }
        if(current1 == NULL) { // iterou o elemento 1 inteiro
            for(int i = 0; i < casaLevel2; i++) {
                printf(">> append 0, casaLevel2: %d\n", casaLevel2);
                append(tempRes, 0);
            }
            printf("***** ZEROING OUT CASALEVEL2\n");
            casaLevel = 1; casaLevel2 = -1; // -1 por resolucao de bugs
            iteratedLevel *= 10; iteratedLevel2 += 1;
            current1 = big1->tail;
            current2 = current2->prev;
            if(current2 == NULL) {
                printNumber(tempRes);
                res = soma(res, tempRes);
                break;
            }
        }

        printf("+++++ INC. CASALEVEL2\n");
        casaLevel2 += 1;

        // RESET TEMPRES
        printNumber(tempRes);
        res = soma(res, tempRes);
        memset(tempRes, 0, sizeof(BIG_INT));

    } while(1);

    //insert(res, intArraySum(resultCache, resultCacheIdx));

    printf("ABAIXO:\n");
    printNumber(res);

    printf("Final res: %d\n", intArraySum(resultCache, resultCacheIdx));
}