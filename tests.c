#include "big_int.h"

int main(void) {
    /*
    TODO: se int(big1) < int(big2) > err, resposta errada
    */
    BIG_INT* big1 = parseString("251");
    BIG_INT* big2 = parseString("100");

    //BIG_INT* higher = getHigher(big1, big2);
    //printf("dd");
    //printNumber(higher);
    //BIG_INT *lower = getLower(big1, big2);
    //printNumber(lower);

    //mult(higher, lower);

    mult(big1, big2);
}
