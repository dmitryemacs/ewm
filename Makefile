main: main.c
	clang -O2 -Wall -Wextra -I/usr/local/include main.c -o main -L/usr/local/lib -lX11

run:
	clang -O2 -Wall -Wextra -I/usr/local/include main.c -o main -L/usr/local/lib -lX11
	./main
