all: prime
prime: prime.o
	mpicc prime.o -o prime -lm
prime.o: prime.c
	mpicc -c prime.c
clean:
	rm -f *o prime
