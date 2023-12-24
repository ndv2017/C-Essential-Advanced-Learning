all:
	gcc -c -o main.o main.c
	gcc -c -o classictriangle.o classictriangle.c
	gcc -c -o floydtriangle.o floydtriangle.c

create1:
	gcc -o classictriangle classictriangle.o main.o
	
create2:
	gcc -o floydtriangle floydtriangle.o main.o

clean:
	rm -rf *.o classictriangle floydtriangle