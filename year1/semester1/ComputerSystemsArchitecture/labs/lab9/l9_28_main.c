#include <stdio.h>

void citire_sir(char sir[]);
void afisare_sir(char sir[]);

extern void asm_create(const char* source, char* sir1, char* sir2);

int main()
{
    char str[100];
    char sir1[100], sir2[100];
    citire_sir(str);

    asm_create(str, sir1, sir2);

    afisare_sir(str);

    afisare_sir(sir1);

    afisare_sir(sir2);

    return 0;
}

void citire_sir(char sir[])
{
    scanf("%s", sir);
}

void afisare_sir(char sir[])
{
    printf("%s\n", sir);
}
