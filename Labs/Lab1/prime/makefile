all: prime
prime: prime.o
	mpicc prime.o -o prime
prime.o: prime.c
	mpicc -c prime.c
clean:
	rm -f *o prime
