all: paint.out

paint.out: main.c canvas.c commands.c files.c canvas.h commands.h files.h
	gcc -Wall -Wextra -Werror main.c canvas.c commands.c files.c -o paint.out

clean:
	rm -f paint.out