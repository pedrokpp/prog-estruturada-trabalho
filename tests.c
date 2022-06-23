#include "big_int.h"

int main(void) {
    /*
    TODO: se int(big1) < int(big2) > err, resposta errada
    */
    BIG_INT* big1 = parseString("30");
    BIG_INT* big2 = parseString("15");
    
    MULT(big1, big2);
}
