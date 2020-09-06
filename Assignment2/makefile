client:    client.o List.o
	gcc -pthread -o  c client.o List.o
	
server:   server.o List.o
	gcc -pthread -o  x server.o List.o

client.o: client.c List.h  
	gcc -pthread -Wall -c  client.c
	
server.o: server.c List.h
	gcc -pthread -Wall  -c  server.c

List.o: List.c List.h
	gcc -c List.c
	

clean:
	rm  client.o List.o server.o c ss

