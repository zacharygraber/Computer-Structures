CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra

all:
		$(CC) hello.c -o hello $(CFLAGS)
		$(CC) exit_test.c -o exit_test $(CFLAGS)
		$(CC) cmd_args.c -o cmd_args $(CFLAGS)
	$(CC) std_io.c -o std_io $(CFLAGS)

clean:
	rm -f hello exit_test cmd_args std_io
