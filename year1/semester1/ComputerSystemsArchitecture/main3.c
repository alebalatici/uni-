#include <stdio.h>

extern int bin_to_hex(char* bin);

int main()
{
    char bin[33];   // max 32 biți + '\0'
    int hex;

    printf("Introdu numere binare (CTRL+D pentru stop):\n");

    while (scanf("%s", bin) == 1)
    {
        hex = bin_to_hex(bin);
        printf("0x%X\n", hex);
    }

    return 0;
}
