//l9_5_main.c + l9_5_modul.c 
#include <stdio.h>
// declarare functie asm
int asm_calcul(int a, int b, int c);
// declarare functie c
void citire_abc(int* a, int* b, int* c);
int main()
{
    int a, b, c;
    int rez;

    citire_abc(&a, &b, &c);   // trimitem adresele

    rez = asm_calcul(a, b, c);

    printf("%d\n", rez);
    return 0;
}
void citire_abc(int* a, int* b, int* c)
{
    printf("Introduceti numarul a: ");
    scanf("%d", a);

    printf("Introduceti numarul b: ");
    scanf("%d", b);

    printf("Introduceti numarul c: ");
    scanf("%d", c);
}
