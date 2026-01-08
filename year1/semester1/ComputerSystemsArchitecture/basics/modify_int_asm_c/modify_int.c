#include <stdio.h>
void citire_sir(int sir[], int *n);
void afisare_sir(int sir[], int n);

extern void asm_modify_int(int sir[], int n);
int main()
{
	int sir[100], n;
	citire_sir(sir, &n);
	asm_modify_int(sir, n);
	afisare_sir(sir, n);
	return 0;
}
void citire_sir(int sir[], int *n)
{
	int x;
	int i = 0;
	while (scanf("%d", &x) == 1)
	{
		sir[i] = x;
		i = i + 1;
	}
	*n = i;
}
void afisare_sir(int sir[], int n)
{
	int	i = 0;
	while (i < n)
	{
		printf("%d ", sir[i]);
		i = i + 1;
	}
}
