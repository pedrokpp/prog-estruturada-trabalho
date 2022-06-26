#include "big_int.h"
#include "soma.h"
#include "subt.h"

int main(void){
  while (1) {
    char str1[1000], str2[1000], op;
    printf("Digite o numero a operacao e o outro numero ... ");
    scanf("%s", str1);
    scanf(" %c", &op);
    scanf("%s", str2);
    if ((op != '+') && (op != '-') && (op != '*') && (op != '/') && (op != '%')) {
      printf("ERRO: operador invalido!\n");
      printf("Quer continuar (digite 0 para sair)? "); 
      scanf(" %c", &op);
      if(op == '0') return 0;
      continue;
    }
    BIG_INT *num1 = parseString(str1), *num2 = parseString(str2), *resp;
    if (op == '+') resp = soma(num1, num2);
    else if (op == '-') resp = subt(num1, num2);
    // else if(op == '*') resp = mult(num1, num2);
    // else if(op == '/') resp = div(num1, num2);
    // else resp = mod(num1, num2);

    printf("%s %c %s = ", str1, op, str2);
    printNumber(resp);

    freeNumber(num1);
    freeNumber(num2);
    freeNumber(resp);

    printf("Quer continuar (digite 0 para sair)? "); 
    scanf(" %c", &op);
    if(op == '0') return 0;
  }
}
