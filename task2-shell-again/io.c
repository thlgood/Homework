#include "Tshell.h"

char *IN_STD(char *a) {
	printf("%s", PS2);
	return fgets(a, BUF_LEN, stdin);
}
