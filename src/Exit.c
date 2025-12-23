#include "Exit.h"
#include <stdio.h>
#include <stdlib.h>

void gameExit(enum ExitReason const p_reason) {
	switch (p_reason) {

		default: return;

		case EXIT_REASON_SUCCESS: {

			printf("Exiting just fine this time :)!");

		} break;

		case EXIT_REASON_FAILURE: {

			printf("Exiting for no good reason! Check meee!");

		} break;

		case EXIT_REASON_REALLOC: {

			printf("Exiting because some `realloc()` call failed.");

		} break;

		case EXIT_REASON_MALLOC: {

			printf("Exiting because `malloc()` call failed. Again.");

		} break;

		case EXIT_REASON_CALLOC: {

			printf("Exiting because `calloc()` call failed. Again.");

		} break;

	}

	putchar('\n');
	exit(p_reason);
}
