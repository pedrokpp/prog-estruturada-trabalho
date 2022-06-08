#include "big_int.h"

int main(void) {
    BIG_INT* bi1 = parseString("1000001");
    printNumber(bi1);
    BIG_INT* bi2 = parseString("101");
    printf("-");
    printNumber(bi2);
    BIG_INT* res = sub(bi1, bi2);
    printNumber(res);
}
