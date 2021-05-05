#include <stdio.h>
#include <limits.h>

int main(void) {
	unsigned x = UINT_MAX;
	printf("%u\n", x << 2);
	return(0);
}
