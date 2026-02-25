all : monexecutable
monexecutable: main_3.o mini_projet_3.o
		gcc -o monexecutable main_3.o mini_projet_3.o -lm

main_3.o: main_3.c
		gcc -c main_3.c -o main_3.o -Wall

mini_projet_3.o: mini_projet_3.c
		gcc -c mini_projet_3.c -o mini_projet_3.o -Wall -lm