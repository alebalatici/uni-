//l9_5_main.c + l9_5_modul.asm 
#include <stdio.h>
extern void adaugare_asm(int x, int sir[], int* len);
void afisare_sir(int sir[], int len);

int main()
{
	int sir[100];
	int len = 0;
	int x;
	while (scanf("%d", &x) == 1)
	{
		adaugare_asm(x, sir, &len);
	}
	afisare_sir(sir, len);
	return 0;
}
void afisare_sir(int sir[], int len)
{	
	printf("Sirul citit:\n");
		for (int i = 0; i < len; i++)
		{
			printf("%d ", sir[i]);
	}
	printf("\n");
}

