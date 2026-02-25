all : monexecutable
monexecutable: main_2.o mini_projet_2.o
		gcc -o monexecutable main_2.o mini_projet_2.o -lm

main_2.o: main_2.c
		gcc -c main_2.c -o main_2.o -Wall

mini_projet_2.o: mini_projet_2.c
		gcc -c mini_projet_2.c -o mini_projet_2.o -Wall -lm