#include "big_int.h"

int main(void) {
    BIG_INT* bi = parseString("12312312312312389890123123120381203123123");
    if (!bi) {
        printf("Caractere não numérico enviado como número!\n");
        return -1;
    }
    printf("Lista (%d): ", bi->length);
    printNumber(bi);
}
