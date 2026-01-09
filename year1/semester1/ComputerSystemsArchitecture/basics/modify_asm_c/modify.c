#include <stdio.h>
void citire_sir();
void afisare_sir();

extern void asm_modify(char* sir);

int main()
{
	char sir[100];

	citire_sir(sir);

	asm_modify(sir);

	afisare_sir(sir);
	return 0;
}
void citire_sir(char sir[])
{
	fgets(sir, 100, stdin);
}
void afisare_sir(char sir[])
{
	printf("Sirul modificat: %s", sir);
}
