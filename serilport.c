
#include<stdio.h>
#include<windows.h>
 
int main()
{
	FILE *fp;
	if ((fp = fopen("com5", "r")) == NULL)
	{
		printf("cannot open com!\n");
	}
	else
		printf("open com successful!\n");
 
	char str;
 
	while (1)
	{
		fscanf(fp, "%c", &str);
		printf("%c ", str);
 
		Sleep(100);
	}
 
	return 0;
}