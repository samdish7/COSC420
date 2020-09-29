all: pSum
pSum: palin.o
	mpicc -o pSum palin.o -lm
palin.o: palin.c
	mpicc -c palin.c
clean:
	rm -r *o pSum
