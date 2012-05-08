#include <stdio.h>

#define PS()	putchar('>')
#define PS(a)	printf("%s", a)

int main()
{
	char *a = "Good";
	PS();
	PS(a);
	return 0;
}
