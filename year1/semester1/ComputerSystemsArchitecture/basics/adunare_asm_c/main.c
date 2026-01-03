#include <stdio.h>
int aduna(int a, int b);
int main()
{
	int a, b, rez;
	printf("a = ");
	scanf("%d", &a);
	printf("b = ");
	scanf("%d", &b);
	rez = aduna(a, b);
	printf("a + b = %d\n", rez);
	return 0;
}
