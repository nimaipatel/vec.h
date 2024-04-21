main: main.c vec.h
	# gcc -g -Wall -Wpedantic -Wextra ./main.c -o ./main
	# -std=c23
	gcc -Wall -Wextra -Wpedantic -fsanitize=address -static-libsan -g -fverbose-asm ./main.c -o main
