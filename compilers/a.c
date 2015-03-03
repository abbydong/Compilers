#include <stdio.h>
#include <string.h>

int main()
{
	char a[2] = "~";
	char b[2] = "~";

	if(strcmp(a,b) == 0 )	
		printf("Suc:%s,%s\n" ,a, b);
	else
		printf("fail:%s,%s\n",a,b);

	return 0;
}
