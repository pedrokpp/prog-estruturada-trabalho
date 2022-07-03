
#define DEBUG 0 
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

char * convertNumberIntoArray(unsigned int number) {
    unsigned int length = (int)(log10((float)number)) + 1;
    char * arr = (char *) malloc(length * sizeof(char)), * curr = arr;
    do {
        *curr++ = number % 10;
        number /= 10;
    } while (number != 0);
    return arr;
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
    res = parseString("");

    do {
        lowFactor = thisMultRes = current1->value * current2->value;

        if(upFactor > 0) {
            //printf("Usando o upFactor...\n");
            thisMultRes += upFactor;
            lowFactor += upFactor;
            upFactor = 0;
        }

        if(thisMultRes >= 10) {
            if(current1 == big1->head) {
                printf("Ja estamos no ultimo elemento, devo por TUDO\n");
                lowFactor = thisMultRes;
            } else {
                upFactor = floor(thisMultRes / 10);
                lowFactor = thisMultRes % 10;
            }
        }

        resultCache[resultCacheIdx] = lowFactor * casaLevel * iteratedLevel; /* metodo antigo: nao aplicavel a big int's */
        //printf("ON-EXEC: _array[%d] = %d * %d * %d\n", resultCacheIdx, lowFactor, casaLevel, iteratedLevel);

        //printf(">> insert %d\n", lowFactor);

        // bug fix
        char *numArray = convertNumberIntoArray(lowFactor);
        //printf("Numarray[0]: %d | Numarray[1]: %d | Numarray len: %d\n", numArray[0], numArray[1], strlen(numArray));
        if(strlen(numArray) > 0) {
            for(int i = 0; i < strlen(numArray); i++) {
                insert(tempRes, numArray[i]);
            }
        } else {
            insert(tempRes, lowFactor);
        }

        for(int i = 0; i < iteratedLevel2; i++) {
            //printf(">>?? append 0, iteratedLevel2: %d\n", iteratedLevel2);
            append(tempRes, 0);
        }

        casaLevel *= 10;
        resultCacheIdx++;
        for(int i = 0; i < casaLevel2; i++) {
            //printf(">> append 0, casaLevel2: %d\n", casaLevel2);
            append(tempRes, 0);
        }

        printf("%d * %d = %d | lowFactor = %d | upFactor = %d | Inserindo %d na resposta\n", current1->value, current2->value, thisMultRes, lowFactor, upFactor, lowFactor);
        current1 = current1->prev;
        //printf("current1: %lx | big1->tail: %lx | current2: %lx | big2->tail: %lx | current2->prev: %lx\n", current1, big1->tail, current2, big2->tail, current2->prev);
        if( current1 == NULL && (current2 == NULL/* || current2->prev == NULL*/) ) {
            printf("break 1\n");
            break;
        }
        if(current1 == NULL) { // iterou o elemento 1 inteiro
            //printf("***** ZEROING OUT CASALEVEL2\n");
            casaLevel = 1; casaLevel2 = -1; // -1 por resolucao de bugs
            //printf("+++++++ INC. ITERATEDLEVEL2\n");
            iteratedLevel *= 10; iteratedLevel2 += 1;
            current1 = big1->tail;
            current2 = current2->prev;
            if(current2 == NULL) {
                printf("--- SOMA FINAL ---\n");
                printf("tempRes: ");
                printNumber(tempRes);
                printf("\n");
                res = soma(res, tempRes);
                break;
            }
        }

        //printf("+++++ INC. CASALEVEL2\n");
        casaLevel2 += 1;

        // RESET TEMPRES
        //printf("OUT: res->tail: %p | tempRes->tail: %p\n", res->tail, tempRes->tail);
        printf("tempRes: ");
        printNumber(tempRes);
        printf("\n");
        res = soma(res, tempRes);

        memset(tempRes, 0, sizeof(BIG_INT));
        //tempRes = parseString("");

    } while(1);

    //insert(res, intArraySum(resultCache, resultCacheIdx));

    printf("RESULTADO BIGINT: ");
    printNumber(res);
    printf("\n");

    printf("Final res: %d\n", intArraySum(resultCache, resultCacheIdx));
}