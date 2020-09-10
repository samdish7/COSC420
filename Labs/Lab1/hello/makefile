all: hello
hello: hello.o
	mpicc hello.o -o hello
hello.o: hello.c
	mpicc -c hello.c

clean:
	rm -f *o hello
