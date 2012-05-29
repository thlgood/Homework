#include "Tshell.h"

void init_arg(int argc, char *argv[])
{
	switch(argc) {
		case 1:
			break;
		case 2:
			if (!strcmp("-v", argv[1])) {
				run_mode = IS_DEBUG_MODE;
			}
			else {
				freopen(argv[1], "r", stdin);
			}
			break;
		case 3:
			run_mode = IS_DEBUG_MODE;
			if (strcmp("-v", argv[1])){
				freopen(argv[1], "r", stdin);
			}
			else {
				freopen(argv[2], "r", stdin);
			}
			break;
		default:
			fputs("Too much argument!", stderr);
			exit(EXIT_FAILURE);
	}
}
