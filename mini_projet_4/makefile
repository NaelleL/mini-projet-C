
all : monexecutable
monexecutable: main_4.o mini_projet_4.o
		gcc -o monexecutable main_4.o mini_projet_4.o -lm

main_4.o: main_4.c
		gcc -c main_4.c -o main_4.o -Wall

mini_projet_4.o: mini_projet_4.c
		gcc -c mini_projet_4.c -o mini_projet_4.o -Wall -lm