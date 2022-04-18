CFLAGS=-Wall -pg -pedantic -Werror -Wextra -Wconversion -std=gnu11 -O0

lab3: lab3.c
	gcc $(CFLAGS) lab3.c -o lab3
	./lab3
	gprof -b lab3