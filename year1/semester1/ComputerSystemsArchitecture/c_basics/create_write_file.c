#include <stdio.h>
int main()
{
	FILE *f = fopen("output.txt", "w");
	if (f == NULL)
	{
		printf("Error.\n");
		return 1;
	}
	fprintf(f, "Hello World!\n");
	fclose(f);
	return 0;
}
