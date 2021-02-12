#include <stdio.h>
#include <stdlib.h>

int main (void) {
	fprintf(stderr, "%s", "We want this program to fail\n");
	exit(EXIT_FAILURE);
}
