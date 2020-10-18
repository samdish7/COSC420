all: gauss
gauss: gauss_jordan.c
	mpicc -o gauss gauss_jordan.c -lm
clean:
	rm -f *.o gauss
