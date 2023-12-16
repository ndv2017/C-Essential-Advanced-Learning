step1:
	gcc -E hello.c -o hello.i

step2:
	gcc -S hello.i -o hello.S

step3:
	gcc -c hello.S -o hello.o

step4:
	gcc -o hello hello.o

all:
	gcc hello.c -o hello

clean:
	rm -rf hello.i hello.S  hello.o hello
