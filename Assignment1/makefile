all: count

count:  main.o List.o
	gcc -o all main.o List.o

main.o: main.c List.h
	gcc -c  main.c
List.o: List.c List.h
	gcc -c List.c
clean:
	rm  main.o List.o

