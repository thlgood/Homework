#include "Tshell.h"

int main()
{
	char buf[BUF_LEN];
	INPUT(buf, stdin);
	printf("%s", buf);
	return 0;
}
