all: matrix
matrix: matrix_test.o
	mpicc matrix_test.o -o matrix -lm
matrix_test.o: matrix_test.c
	mpicc -c matrix_test.c
clean:
	rm -f *.o matrix
