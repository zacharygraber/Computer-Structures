#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	int PID = fork();
	if (PID == 0) {
		execl("/bin/date", "date", "+%F", NULL);
		printf("THIS SHOULDNT PRINT\n");
	}
}
