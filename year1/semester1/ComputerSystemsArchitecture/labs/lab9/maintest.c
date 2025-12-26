#include <stdio.h>

void citire_sir(char sir[]);
void afisare_sir(char sir[]);

extern void asm_concat(char* rez, const char* s1, const char* s2);

int main()
{
    char str1[100], str2[100], str3[100];
    char str4[200], str5[300];

    citire_sir(str1);
    citire_sir(str2);
    citire_sir(str3);

    // str1 + str2 în str4
    asm_concat(str4, str1, str2);

    // str4 + str3 în str5
    asm_concat(str5, str4, str3);

    afisare_sir(str5);

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
